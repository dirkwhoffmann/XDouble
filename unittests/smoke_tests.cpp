#include "main.h"
#include <numbers>

TEST_CASE("Basic smoke tests") {

    SUBCASE("Constructors") {

        doubledouble x = 2.25;

        CHECK(doubledouble().to_double() == 0.0);
        CHECK(doubledouble(0.5).to_double() == 0.5);
        CHECK(doubledouble(0.5,0.125).to_double() == 0.625);
        CHECK(doubledouble(x).to_double() == 2.25);
        CHECK(doubledouble("3.5").to_double() == 3.5);
        CHECK(doubledouble("-3.5").to_double() == -3.5);
        CHECK(doubledouble(std::numeric_limits<double>::infinity()) == doubledouble::inf());
        CHECK(doubledouble(-std::numeric_limits<double>::infinity()) == -doubledouble::inf());
        CHECK(doubledouble(std::numeric_limits<double>::quiet_NaN()).isnan());
    }

    SUBCASE("Conversion functions") {

        CHECK(doubledouble(0.5).to_int() == 0);
        CHECK(doubledouble(3.14).to_int() == 3);
        CHECK(doubledouble(-3.14).to_int() == -3);
        CHECK(doubledouble::inf().to_int() == INT_MAX);
        CHECK((-doubledouble::inf()).to_int() == INT_MIN);
        CHECK(doubledouble::nan().to_int() == 0);

        CHECK(doubledouble(0.5).to_long() == 0);
        CHECK(doubledouble(3.14).to_long() == 3);
        CHECK(doubledouble(-3.14).to_long() == -3);
        CHECK(doubledouble::inf().to_long() == LONG_MAX);
        CHECK((-doubledouble::inf()).to_long() == LONG_MIN);
        CHECK(doubledouble::nan().to_long() == 0);

        CHECK(doubledouble(0.5).to_long_long() == 0);
        CHECK(doubledouble(3.14).to_long_long() == 3);
        CHECK(doubledouble(-3.14).to_long_long() == -3);
        CHECK(doubledouble::inf().to_long_long() == LLONG_MAX);
        CHECK((-doubledouble::inf()).to_long_long() == LLONG_MIN);
        CHECK(doubledouble::nan().to_long_long() == 0);

        CHECK(doubledouble(0).to_float() == 0.0f);
        CHECK(doubledouble(0.5).to_float() == 0.5f);
        CHECK(doubledouble(-0.5).to_float() == -0.5);
        CHECK(doubledouble(0.5,0.125).to_float() == 0.625f);
        CHECK(doubledouble(-0.5,-0.125).to_float() == -0.625);
        CHECK(doubledouble::inf().to_float() == std::numeric_limits<float>::infinity());
        CHECK((-doubledouble::inf()).to_float() == -std::numeric_limits<float>::infinity());
        CHECK(std::isnan(doubledouble::nan().to_float()));

        CHECK(doubledouble(0).to_double() == 0.0);
        CHECK(doubledouble(0.5).to_double() == 0.5);
        CHECK(doubledouble(-0.5).to_double() == -0.5);
        CHECK(doubledouble(0.5,0.125).to_double() == 0.625);
        CHECK(doubledouble(-0.5,-0.125).to_double() == -0.625);
        CHECK(doubledouble::inf().to_double() == std::numeric_limits<double>::infinity());
        CHECK((-doubledouble::inf()).to_double() == -std::numeric_limits<double>::infinity());
        CHECK(std::isnan(doubledouble::nan().to_double()));

        CHECK(doubledouble(0).to_long_double() == 0.0L);
        CHECK(doubledouble(0.5).to_long_double() == 0.5L);
        CHECK(doubledouble(-0.5).to_long_double() == -0.5L);
        CHECK(doubledouble(0.5,0.125).to_long_double() == 0.625L);
        CHECK(doubledouble(-0.5,-0.125).to_long_double() == -0.625L);
        CHECK(doubledouble::inf().to_long_double() == std::numeric_limits<long double>::infinity());
        CHECK((-doubledouble::inf()).to_long_double() == -std::numeric_limits<long double>::infinity());
        CHECK(std::isnan(doubledouble::nan().to_long_double()));
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
