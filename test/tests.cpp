#include <catch2/catch.hpp>

#include <sstream>

#include "decimal.h"

using namespace decimal;

TEST_CASE("Values with 0 digits can be constucted", "[construction]") {
    auto zero = decimal<0>(0);
    auto one = decimal<0>(1);
    auto negone = decimal<0>(-1);

    CHECK(zero.scalar() == 1);
    CHECK(one.scalar() == 1);
    CHECK(negone.scalar() == 1);

    CHECK(zero.scaled() == 0);
    CHECK(one.scaled() == 1);
    CHECK(negone.scaled() == -1);
}

TEST_CASE("Values with multiple digits can be constructed", "[construction]") {
    auto zero0 = decimal<0>(0);
    auto zero1 = decimal<1>(0);
    auto zero2 = decimal<2>(0);

    auto one0 = decimal<0>(1);
    auto one1 = decimal<1>(1);
    auto one2 = decimal<2>(1);

    auto negone0 = decimal<0>(-1);
    auto negone1 = decimal<1>(-1);
    auto negone2 = decimal<2>(-1);

    CHECK(zero0.scalar() == 1);
    CHECK(zero1.scalar() == 10);
    CHECK(zero2.scalar() == 100);

    CHECK(one0.scalar() == 1);
    CHECK(one1.scalar() == 10);
    CHECK(one2.scalar() == 100);

    CHECK(negone0.scalar() == 1);
    CHECK(negone1.scalar() == 10);
    CHECK(negone2.scalar() == 100);

    CHECK(zero0.scaled() == 0);
    CHECK(zero1.scaled() == 0);
    CHECK(zero2.scaled() == 0);

    CHECK(one0.scaled() == 1);
    CHECK(one1.scaled() == 10);
    CHECK(one2.scaled() == 100);

    CHECK(negone0.scaled() == -1);
    CHECK(negone1.scaled() == -10);
    CHECK(negone2.scaled() == -100);
}

TEST_CASE("Values can be constructed from floating point", "[construction]") {
    CHECK(decimal<2>{1.23}.scaled() == 123);
    CHECK(decimal<3>{1.23}.scaled() == 1230);
    CHECK(decimal<4>{1.23}.scaled() == 12300);

    CHECK(decimal<2>{-1.23}.scaled() == -123);

    CHECK(decimal<2>{1.234567}.scaled() == 123);
    CHECK(decimal<2>{1.239999}.scaled() == 124);
}

TEST_CASE("Values can be constructed from other decimal values with fewer digits",
          "[construction]") {
    CHECK(decimal<4>{decimal<3>{1.23}}.scaled() == 12300);
    CHECK(decimal<4>{decimal<2>{1.23}}.scaled() == 12300);
    CHECK(decimal<4>{decimal<1>{1.23}}.scaled() == 12000);
}

TEST_CASE("Values can be converted to integer types", "[construction]") {
    CHECK(static_cast<int>(decimal<2>{5}) == 5);
    CHECK(static_cast<int>(decimal<2>{5.43}) == 5);
    CHECK(static_cast<int>(decimal<2>{-5.43}) == -5);
    CHECK(static_cast<int>(decimal<2>{0}) == 0);
    CHECK(static_cast<int>(decimal<2>{0.000}) == 0);

    CHECK(static_cast<unsigned>(decimal<2>{5}) == 5);
    CHECK(static_cast<unsigned>(decimal<2>{5.43}) == 5);
}

TEST_CASE("Values can be converted to floating point types", "[construction]") {
    CHECK(static_cast<double>(decimal<2>{5}) == 5.0);
    CHECK(static_cast<double>(decimal<2>{5.43}) == 5.43);
    CHECK(static_cast<double>(decimal<2>{-5.43}) == -5.43);
    CHECK(static_cast<double>(decimal<2>{5.4321}) == 5.43);
    CHECK(static_cast<double>(decimal<2>{5.4399}) == 5.44);
    CHECK(static_cast<double>(decimal<2>{0}) == 0.0);
    CHECK(static_cast<double>(decimal<2>{0.000}) == 0.0);

    CHECK(static_cast<float>(decimal<2>{5}) == 5.0f);
    CHECK(static_cast<float>(decimal<2>{5.43}) == 5.43f);
    CHECK(static_cast<float>(decimal<2>{-5.43}) == -5.43f);
    CHECK(static_cast<float>(decimal<2>{5.4321}) == 5.43f);
    CHECK(static_cast<float>(decimal<2>{5.4399}) == 5.44f);
    CHECK(static_cast<float>(decimal<2>{0}) == 0.0f);
    CHECK(static_cast<float>(decimal<2>{0.000}) == 0.0f);
}

TEST_CASE("Values can be equality compared", "[comparison]") {
    CHECK(decimal<2>{3} == decimal<2>{3});
    CHECK(decimal<2>{3} == decimal<2>{3.00});
    CHECK(decimal<2>{3.00f} == decimal<2>{3.00});
    CHECK(decimal<2>{2.999} == decimal<2>{3.001});
    CHECK(decimal<2>{0} == decimal<2>{0});
    CHECK(decimal<2>{-1} == decimal<2>{-1});

    CHECK_FALSE(decimal<2>{2} == decimal<2>{3});
    CHECK_FALSE(decimal<2>{3} == decimal<2>{3.01});
    CHECK_FALSE(decimal<2>{4.00f} == decimal<2>{3.00});
    CHECK_FALSE(decimal<2>{2.99} == decimal<2>{3.01});
    CHECK_FALSE(decimal<2>{1} == decimal<2>{0});
    CHECK_FALSE(decimal<2>{-2} == decimal<2>{-1});
}

TEST_CASE("Values can be inequality compared", "[comparison]") {
    CHECK_FALSE(decimal<2>{3} != decimal<2>{3});
    CHECK_FALSE(decimal<2>{3} != decimal<2>{3.00});
    CHECK_FALSE(decimal<2>{3.00f} != decimal<2>{3.00});
    CHECK_FALSE(decimal<2>{2.999} != decimal<2>{3.001});
    CHECK_FALSE(decimal<2>{0} != decimal<2>{0});
    CHECK_FALSE(decimal<2>{-1} != decimal<2>{-1});

    CHECK(decimal<2>{2} != decimal<2>{3});
    CHECK(decimal<2>{3} != decimal<2>{3.01});
    CHECK(decimal<2>{4.00f} != decimal<2>{3.00});
    CHECK(decimal<2>{2.99} != decimal<2>{3.01});
    CHECK(decimal<2>{1} != decimal<2>{0});
    CHECK(decimal<2>{-2} != decimal<2>{-1});
}

TEST_CASE("Values can be less-than compared", "[comparison]") {
    CHECK(decimal<2>{3} < decimal<2>{4.57});
    CHECK(decimal<2>{0} < decimal<2>{5});
    CHECK(decimal<2>{-1} < decimal<2>{0});
    CHECK_FALSE(decimal<2>{4.57} < decimal<2>{4.57});
    CHECK_FALSE(decimal<2>{3} < decimal<2>{3});
    CHECK_FALSE(decimal<2>{5} < decimal<2>{3});
}

TEST_CASE("Values can be less-than-equal-to compared", "[comparison]") {
    CHECK(decimal<2>{3} <= decimal<2>{4.57});
    CHECK(decimal<2>{0} <= decimal<2>{5});
    CHECK(decimal<2>{-1} <= decimal<2>{0});
    CHECK(decimal<2>{4.57} <= decimal<2>{4.57});
    CHECK(decimal<2>{3} <= decimal<2>{3});
    CHECK_FALSE(decimal<2>{5} <= decimal<2>{3});
}

TEST_CASE("Values can be greater-than compared", "[comparison]") {
    CHECK(decimal<2>{4.57} > decimal<2>{3});
    CHECK(decimal<2>{5} > decimal<2>{0});
    CHECK(decimal<2>{0} > decimal<2>{-1});
    CHECK_FALSE(decimal<2>{4.57} > decimal<2>{4.57});
    CHECK_FALSE(decimal<2>{3} > decimal<2>{3});
    CHECK_FALSE(decimal<2>{3} > decimal<2>{5});
}

TEST_CASE("Values can be greater-than-equal-to compared", "[comparison]") {
    CHECK(decimal<2>{4.57} >= decimal<2>{3});
    CHECK(decimal<2>{5} >= decimal<2>{0});
    CHECK(decimal<2>{0} >= decimal<2>{-1});
    CHECK(decimal<2>{4.57} >= decimal<2>{4.57});
    CHECK(decimal<2>{3} >= decimal<2>{3});
    CHECK_FALSE(decimal<2>{3} >= decimal<2>{5});
}

TEST_CASE("Values with the same digits can be added together", "[arithmetic]") {
    auto a = decimal<2>{1.23};
    auto b = decimal<2>{4};
    auto c = decimal<2>{-1.2};

    CHECK(a + b == decimal<2>{5.23});
    CHECK(b + a == decimal<2>{5.23});
    CHECK(a + c == decimal<2>{0.03});
    CHECK(c + a == decimal<2>{0.03});
    CHECK(a + b + c == decimal<2>{4.03});
    CHECK(c + b + a == decimal<2>{4.03});

    a += b;

    REQUIRE(a == decimal<2>{5.23});
    REQUIRE(b == decimal<2>{4});

    a += c;

    REQUIRE(a == decimal<2>{4.03});
    REQUIRE(c == decimal<2>{-1.2});
}

TEST_CASE("Values with the same digits can be subtracted from each other", "[arithmetic]") {
    auto a = decimal<2>{1.23};
    auto b = decimal<2>{4};
    auto c = decimal<2>{-1.2};

    CHECK(a - b == decimal<2>{-2.77});
    CHECK(b - a == decimal<2>{2.77});
    CHECK(a - c == decimal<2>{2.43});
    CHECK(c - a == decimal<2>{-2.43});
    CHECK(a - b - c == decimal<2>{-1.57});
    CHECK(c - b - a == decimal<2>{-6.43});

    a -= b;

    REQUIRE(a == decimal<2>{-2.77});
    REQUIRE(b == decimal<2>{4});

    a -= c;

    REQUIRE(a == decimal<2>{-1.57});
    REQUIRE(c == decimal<2>{-1.2});
}

TEST_CASE("Values with the same digits can be multiplied together", "[arithmetic]") {
    auto a = decimal<2>{1.23};
    auto b = decimal<2>{4};
    auto c = decimal<2>{-1.2};

    CHECK(a * b == decimal<2>{4.92});
    CHECK(b * a == decimal<2>{4.92});
    CHECK(a * c == decimal<2>{-1.47});
    CHECK(c * a == decimal<2>{-1.47});
    CHECK(a * b * c == decimal<2>{-5.90});
    CHECK(c * b * a == decimal<2>{-5.90});

    a *= b;

    REQUIRE(a == decimal<2>{4.92});
    REQUIRE(b == decimal<2>{4});

    a *= c;

    REQUIRE(a == decimal<2>{-5.90});
    REQUIRE(c == decimal<2>{-1.2});
}

TEST_CASE("Values with the same digits can be divided by each other", "[arithmetic]") {
    auto a = decimal<2>{1.23};
    auto b = decimal<2>{4};
    auto c = decimal<2>{-1.2};

    CHECK(a / b == decimal<2>{0.30});
    CHECK(b / a == decimal<2>{3.25});
    CHECK(a / c == decimal<2>{-1.02});
    CHECK(c / a == decimal<2>{-0.97});
    CHECK(a / b / c == decimal<2>{-0.25});
    CHECK(c / b / a == decimal<2>{-0.24});

    a /= b;

    REQUIRE(a == decimal<2>{0.30});
    REQUIRE(b == decimal<2>{4});

    a /= c;

    REQUIRE(a == decimal<2>{-0.25});
    REQUIRE(c == decimal<2>{-1.2});
}

TEST_CASE("Values can be negated", "[arithmetic]") {
    auto a = decimal<2>{1.23};
    auto b = decimal<2>{4};
    auto c = decimal<2>{-1.2};

    CHECK(-a == decimal<2>{-1.23});
    CHECK(-b == decimal<2>{-4});
    CHECK(-c == decimal<2>{1.2});
}

TEST_CASE("Values can be inserted into streams", "[misc]") {
    std::ostringstream ss{};
    ss << decimal<0>{5.2} << " " << decimal<1>{7.0} << " " << decimal<2>{4.06} << " "
       << decimal<3>{4.06} << " " << decimal<5>{0} << " " << decimal<2>{-3.45} << " "
       << decimal<2>{-0.2};
    REQUIRE(ss.str() == "5 7.0 4.06 4.060 0.00000 -3.45 -0.20");
}

TEMPLATE_TEST_CASE("Numeric limits are appropriately set",
                   "[misc]",
                   int,
                   unsigned,
                   long,
                   unsigned long) {
    using d = decimal<2, TestType>;
    using nl = std::numeric_limits<d>;
    using nlBase = std::numeric_limits<TestType>;
    CHECK(nl::min() == nl::lowest());
    CHECK(nl::min() == nlBase::min() / d::scalar());
    CHECK(nl::max() == nlBase::max() / d::scalar());
    CHECK(nl::is_signed == nlBase::is_signed);
    CHECK(nl::is_modulo == nlBase::is_modulo);
}
