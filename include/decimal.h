#ifndef DECIMAL_H
#define DECIMAL_H

#include <cmath>
#include <iomanip>
#include <limits>
#include <ostream>
#include <type_traits>

namespace decimal {
    template <int Digits, typename T = int, int Base = 10>
    class decimal {
        static_assert(std::is_integral_v<T>);
        static_assert(Digits >= 0);

    private:
        [[nodiscard]] static constexpr T compute_scalar() {
            T val = 1;
            for (int i = 0; i < Digits; i++) {
                val *= Base;
            }
            return val;
        }

        static constexpr T const scalar_ = compute_scalar();
        T scaled_;

    public:
        constexpr decimal()
            : scaled_{0} {}

        template <typename Integer, std::enable_if_t<std::is_integral<Integer>::value, int> = 0>
        constexpr decimal(Integer value)
            : scaled_{static_cast<T>(value * scalar_)} {}

        template <typename Floating,
                  std::enable_if_t<std::is_floating_point<Floating>::value, int> = 0>
        constexpr decimal(Floating value)
            : scaled_{static_cast<T>(std::round(value * scalar_))} {}

        template <typename T_>
        constexpr decimal(decimal<Digits, T_, Base> value)
            : scaled_{static_cast<T>(value.scaled())} {}

        template <int Digits_, typename T_, typename = std::enable_if_t<(Digits_ < Digits)>>
        constexpr decimal(decimal<Digits_, T_, Base> value)
            : scaled_{static_cast<T>(value.scaled() * scalar_ / value.scalar())} {}

        template <typename Numeric, typename = std::enable_if_t<std::is_arithmetic<Numeric>::value>>
        explicit constexpr operator Numeric() const {
            return static_cast<Numeric>(scaled_) / scalar_;
        }

        [[nodiscard]] static constexpr T scalar() { return scalar_; }

        [[nodiscard]] constexpr T scaled() const { return scaled_; }

        constexpr decimal& operator+=(decimal rhs) {
            scaled_ += rhs.scaled_;
            return *this;
        }

        constexpr decimal& operator-=(decimal rhs) {
            scaled_ -= rhs.scaled_;
            return *this;
        }

        constexpr decimal& operator*=(decimal rhs) {
            scaled_ *= rhs.scaled_;
            scaled_ /= scalar_;
            return *this;
        }

        constexpr decimal& operator/=(decimal rhs) {
            scaled_ *= scalar_;
            scaled_ /= rhs.scaled_;
            return *this;
        }

        [[nodiscard]] friend constexpr decimal operator+(decimal lhs, decimal rhs) {
            return lhs += rhs;
        }

        [[nodiscard]] friend constexpr decimal operator-(decimal lhs, decimal rhs) {
            return lhs -= rhs;
        }

        [[nodiscard]] friend constexpr decimal operator*(decimal lhs, decimal rhs) {
            return lhs *= rhs;
        }

        [[nodiscard]] friend constexpr decimal operator/(decimal lhs, decimal rhs) {
            return lhs /= rhs;
        }

        [[nodiscard]] friend constexpr decimal operator-(decimal value) {
            return decimal{0} - value;
        }

        [[nodiscard]] friend constexpr bool operator==(decimal lhs, decimal rhs) {
            return lhs.scaled_ == rhs.scaled_;
        }

        [[nodiscard]] friend constexpr bool operator!=(decimal lhs, decimal rhs) {
            return !(lhs == rhs);
        }

        [[nodiscard]] friend constexpr bool operator<(decimal lhs, decimal rhs) {
            return lhs.scaled_ < rhs.scaled_;
        }

        [[nodiscard]] friend constexpr bool operator>(decimal lhs, decimal rhs) {
            return rhs < lhs;
        }

        [[nodiscard]] friend constexpr bool operator<=(decimal lhs, decimal rhs) {
            return !(lhs > rhs);
        }

        [[nodiscard]] friend constexpr bool operator>=(decimal lhs, decimal rhs) {
            return !(lhs < rhs);
        }

        friend std::ostream& operator<<(std::ostream& os, decimal value) {
            if constexpr (Digits == 0) {
                return os << value.scaled();
            } else {
                if (value.scaled() < 0) {
                    os << "-";
                }
                return os << std::abs(value.scaled() / value.scalar()) << "." << std::setw(Digits)
                          << std::setfill('0') << std::abs(value.scaled() % value.scalar());
            }
        }
    };
} // namespace decimal

namespace std {
    template <int Digits, typename T, int Base>
    class numeric_limits<decimal::decimal<Digits, T, Base>> {
    public:
        static constexpr bool is_specialised = true;
        static constexpr bool is_signed = std::numeric_limits<T>::is_signed;
        static constexpr bool is_integer = Digits <= 0 ? true : false;
        static constexpr bool is_exact = true;
        static constexpr bool has_infinity = false;
        static constexpr bool has_quiet_NaN = false;
        static constexpr bool has_signaling_NaN = false;
        static constexpr std::float_denorm_style has_denorm = std::denorm_absent;
        static constexpr bool has_denorm_loss = false;
        static constexpr std::float_round_style round_style = std::round_toward_zero;
        static constexpr bool is_bounded = std::numeric_limits<T>::is_bounded;
        static constexpr bool is_modulo = std::numeric_limits<T>::is_modulo;
        static constexpr bool digits = std::numeric_limits<T>::digits;
        static constexpr bool digits10 = std::numeric_limits<T>::digits10;
        static constexpr bool radix = std::numeric_limits<T>::radix;
        static constexpr bool traps = std::numeric_limits<T>::traps;
        static constexpr bool tinyness_before = std::numeric_limits<T>::tinyness_before;

        [[nodiscard]] static constexpr T min() noexcept {
            return std::numeric_limits<T>::min() / decimal::decimal<Digits, T, Base>::scalar();
        }

        [[nodiscard]] static constexpr T lowest() noexcept { return min(); }

        [[nodiscard]] static constexpr T max() noexcept {
            return std::numeric_limits<T>::max() / decimal::decimal<Digits, T, Base>::scalar();
        }
    };
} // namespace std

#endif
