#include "main.h"
#include <numbers>

TEST_CASE("Basic smoke tests") {

    SUBCASE("Constructors") {

        doubledouble x = 2.25;

        COMPARE(doubledouble(0.5).to_double(), 0.5);
        COMPARE(doubledouble(0.5,0.125).to_double(), 0.625);
        COMPARE(doubledouble(x).to_double(), 2.25);
        COMPARE(doubledouble("3.5").to_double(), 3.5);
        COMPARE(doubledouble("-3.5").to_double(), -3.5);
        COMPARE(doubledouble(posinf), doubledouble::posinf());
        COMPARE(doubledouble(neginf), doubledouble::neginf());
        COMPARE(doubledouble(std::numeric_limits<double>::quiet_NaN()), posnan);
    }

    SUBCASE("Conversion functions") {

        COMPARE(doubledouble(0.5).to_int(), 0);
        COMPARE(doubledouble(3.14).to_int(), 3);
        COMPARE(doubledouble(-3.14).to_int(), -3);
        COMPARE(doubledouble::posinf().to_int(), INT_MAX);
        COMPARE(doubledouble::neginf().to_int(), INT_MIN);
        COMPARE(doubledouble::nan().to_int(), 0);

        COMPARE(doubledouble(0.5).to_long(), 0);
        COMPARE(doubledouble(3.14).to_long(), 3);
        COMPARE(doubledouble(-3.14).to_long(), -3);
        COMPARE(doubledouble::posinf().to_long(), LONG_MAX);
        COMPARE(doubledouble::neginf().to_long(), LONG_MIN);
        COMPARE(doubledouble::nan().to_long(), 0);

        COMPARE(doubledouble(0.5).to_long_long(), 0);
        COMPARE(doubledouble(3.14).to_long_long(), 3);
        COMPARE(doubledouble(-3.14).to_long_long(), -3);
        COMPARE(doubledouble::posinf().to_long_long(), LLONG_MAX);
        COMPARE(doubledouble::neginf().to_long_long(), LLONG_MIN);
        COMPARE(doubledouble::nan().to_long_long(), 0);

        COMPARE(doubledouble(0).to_float(), 0.0f);
        COMPARE(doubledouble(0.5).to_float(), 0.5f);
        COMPARE(doubledouble(-0.5).to_float(), -0.5);
        COMPARE(doubledouble(0.5,0.125).to_float(), 0.625f);
        COMPARE(doubledouble(-0.5,-0.125).to_float(), -0.625);
        COMPARE(doubledouble::posinf().to_float(), std::numeric_limits<float>::infinity());
        COMPARE(doubledouble::neginf().to_float(), -std::numeric_limits<float>::infinity());
        COMPARE(doubledouble::nan().to_float(), posnan);

        COMPARE(doubledouble(0).to_double(), 0.0);
        COMPARE(doubledouble(0.5).to_double(), 0.5);
        COMPARE(doubledouble(-0.5).to_double(), -0.5);
        COMPARE(doubledouble(0.5,0.125).to_double(), 0.625);
        COMPARE(doubledouble(-0.5,-0.125).to_double(), -0.625);
        COMPARE(doubledouble::posinf().to_double(), std::numeric_limits<double>::infinity());
        COMPARE(doubledouble::neginf().to_double(), -std::numeric_limits<double>::infinity());
        COMPARE(doubledouble::nan().to_double(), posnan);

        COMPARE(doubledouble(0).to_long_double(), 0.0L);
        COMPARE(doubledouble(0.5).to_long_double(), 0.5L);
        COMPARE(doubledouble(-0.5).to_long_double(), -0.5L);
        COMPARE(doubledouble(0.5,0.125).to_long_double(), 0.625L);
        COMPARE(doubledouble(-0.5,-0.125).to_long_double(), -0.625L);
        COMPARE(doubledouble::posinf().to_long_double(), std::numeric_limits<long double>::infinity());
        COMPARE(doubledouble::neginf().to_long_double(), -std::numeric_limits<long double>::infinity());
        COMPARE(doubledouble::nan().to_long_double(), posnan);

        COMPARE(std::signbit(doubledouble(0.0).to_double()), 0);
        COMPARE(std::signbit(doubledouble(-0.0).to_double()), 1);
        COMPARE(std::signbit(doubledouble(0.0).to_long_double()), 0);
        COMPARE(std::signbit(doubledouble(-0.0).to_long_double()), 1);
    }

    SUBCASE("Converting to textual representations") {

        doubledouble pi = 3.14159265;

        CHECK(pi.to_string(0) == "3");
        CHECK(pi.to_string(1) == "3.1");
        CHECK(pi.to_string(2) == "3.14");
        CHECK(pi.to_string(3) == "3.141");
        CHECK(pi.to_string(4) == "3.1415");
        CHECK(pi.to_string(5) == "3.14159");

        pi = doubledouble("3.14159265358979323846264338327950");
        CHECK(pi.to_string(32) == "3.14159265358979323846264338327950");

        doubledouble me = -2.71828182;

        CHECK(me.to_string(0) == "-2");
        CHECK(me.to_string(1) == "-2.7");
        CHECK(me.to_string(2) == "-2.71");
        CHECK(me.to_string(3) == "-2.718");
        CHECK(me.to_string(4) == "-2.7182");
        CHECK(me.to_string(5) == "-2.71828");

        me = doubledouble("-2.71828182845904523536028747135266");
        CHECK(me.to_string(32) == "-2.71828182845904523536028747135266");

        CHECK(doubledouble::nan().to_string(0) == "nan");
        CHECK(doubledouble::inf().to_string(0) == "inf");
        CHECK((-doubledouble::inf()).to_string(0) == "-inf");
    }

    SUBCASE("Constants") {

        CHECK(doubledouble::e.to_float() == (float)std::numbers::e);
        CHECK(doubledouble::log2e.to_float() == (float)std::numbers::log2e);
        CHECK(doubledouble::log10e.to_float() == (float)std::numbers::log10e);
        CHECK(doubledouble::pi.to_float() == (float)std::numbers::pi);
        CHECK(doubledouble::inv_pi.to_float() == (float)std::numbers::inv_pi);
        CHECK(doubledouble::inv_sqrtpi.to_float() == (float)std::numbers::inv_sqrtpi);
        CHECK(doubledouble::ln2.to_float() == (float)std::numbers::ln2);
        CHECK(doubledouble::ln10.to_float() == (float)std::numbers::ln10);
        CHECK(doubledouble::sqrt2.to_float() == (float)std::numbers::sqrt2);
        CHECK(doubledouble::sqrt3.to_float() == (float)std::numbers::sqrt3);
        CHECK(doubledouble::inv_sqrt3.to_float() == (float)std::numbers::inv_sqrt3);
        CHECK(doubledouble::egamma.to_float() == (float)std::numbers::egamma);
        CHECK(doubledouble::phi.to_float() == (float)std::numbers::phi);
    }
}
