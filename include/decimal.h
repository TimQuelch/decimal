#ifndef DECIMAL_H
#define DECIMAL_H

#include <type_traits>

namespace decimal {
    template <int Digits,
              typename T = int,
              int Base = 10,
              typename = std::enable_if_t<std::is_integral<T>::value>>
    class decimal {
    private:
        constexpr static T compute_scalar() {
            T val = 1;
            for (int i = 0; i < Digits; i++) {
                val *= Base;
            }
            return val;
        }

        constexpr static T scalar_ = compute_scalar();
        T scaled_;

    public:
        constexpr decimal()
            : scaled_{0} {}

        template <typename Numeric, typename = std::enable_if_t<std::is_arithmetic<Numeric>::value>>
        constexpr decimal(Numeric value)
            : scaled_{static_cast<T>(value) * scalar_} {}

        template <typename Numeric, typename = std::enable_if_t<std::is_arithmetic<Numeric>::value>>
        explicit constexpr operator Numeric() const {
            return static_cast<Numeric>(scaled_ / scalar_);
        }

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
            return *this;
        }

        constexpr decimal& operator/=(decimal rhs) {
            scaled_ /= rhs.scaled_;
            return *this;
        }

        friend constexpr decimal operator+(decimal lhs, decimal rhs) { return lhs += rhs; }
        friend constexpr decimal operator-(decimal lhs, decimal rhs) { return lhs -= rhs; }
        friend constexpr decimal operator*(decimal lhs, decimal rhs) { return lhs *= rhs; }
        friend constexpr decimal operator/(decimal lhs, decimal rhs) { return lhs /= rhs; }

        friend constexpr bool operator==(decimal lhs, decimal rhs) { return lhs.scaled_ == rhs.scaled_; }
        friend constexpr bool operator!=(decimal lhs, decimal rhs) { return !(lhs == rhs); }
        friend constexpr bool operator<(decimal lhs, decimal rhs) { return lhs.scaled_ < rhs.scaled_; }
        friend constexpr bool operator>(decimal lhs, decimal rhs) { return rhs < lhs; }
        friend constexpr bool operator<=(decimal lhs, decimal rhs) { return !(lhs > rhs); }
        friend constexpr bool operator>=(decimal lhs, decimal rhs) { return !(lhs < rhs); }
    };
} // namespace decimal

#endif
