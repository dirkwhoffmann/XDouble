#include "main.h"
#include <numbers>

TEST_CASE("Basic smoke tests") {

    SUBCASE("Constructors") {

        doubledouble x = 2.25;

        COMPARE(doubledouble().to_double(), 0.0);
        COMPARE(doubledouble(0.0).to_double(), 0.0);
        COMPARE(doubledouble(-0.0).to_double(), -0.0);
        COMPARE(doubledouble(0.5).to_double(), 0.5);
        COMPARE(doubledouble(0.5,0.125).to_double(), 0.625);
        COMPARE(doubledouble(x).to_double(), 2.25);
        COMPARE(doubledouble("3.5").to_double(), 3.5);
        COMPARE(doubledouble("-3.5").to_double(), -3.5);
        COMPARE(doubledouble(posinf).to_double(), posinf);
        COMPARE(doubledouble(neginf).to_double(), neginf);
        COMPARE(doubledouble(posnan).to_double(), posnan);
        COMPARE(doubledouble(negnan).to_double(), negnan);
    }

    SUBCASE("Conversion functions") {

        COMPARE(doubledouble().to_int(), 0);
        COMPARE(doubledouble(0.0).to_int(), 0);
        COMPARE(doubledouble(-0.0).to_int(), 0);
        COMPARE(doubledouble(0.5).to_int(), 0);
        COMPARE(doubledouble(3.14).to_int(), 3);
        COMPARE(doubledouble(-3.14).to_int(), -3);
        COMPARE(doubledouble::posinf().to_int(), INT_MAX);
        COMPARE(doubledouble::neginf().to_int(), INT_MIN);
        COMPARE(doubledouble::posnan().to_int(), 0);
        COMPARE(doubledouble::negnan().to_int(), 0);

        COMPARE(doubledouble().to_long(), 0);
        COMPARE(doubledouble(0.0).to_long(), 0);
        COMPARE(doubledouble(-0.0).to_long(), 0);
        COMPARE(doubledouble(0.5).to_long(), 0);
        COMPARE(doubledouble(3.14).to_long(), 3);
        COMPARE(doubledouble(-3.14).to_long(), -3);
        COMPARE(doubledouble::posinf().to_long(), LONG_MAX);
        COMPARE(doubledouble::neginf().to_long(), LONG_MIN);
        COMPARE(doubledouble::posnan().to_long(), 0);
        COMPARE(doubledouble::negnan().to_long(), 0);

        COMPARE(doubledouble().to_long_long(), 0);
        COMPARE(doubledouble(0.0).to_long_long(), 0);
        COMPARE(doubledouble(-0.0).to_long_long(), 0);
        COMPARE(doubledouble(0.5).to_long_long(), 0);
        COMPARE(doubledouble(3.14).to_long_long(), 3);
        COMPARE(doubledouble(-3.14).to_long_long(), -3);
        COMPARE(doubledouble::posinf().to_long_long(), LLONG_MAX);
        COMPARE(doubledouble::neginf().to_long_long(), LLONG_MIN);
        COMPARE(doubledouble::posnan().to_long_long(), 0);
        COMPARE(doubledouble::negnan().to_long_long(), 0);

        COMPARE(doubledouble().to_float(), 0.0f);
        COMPARE(doubledouble(0.0).to_float(), 0.0f);
        COMPARE(doubledouble(-0.0).to_float(), -0.0f);
        COMPARE(doubledouble(0).to_float(), 0.0f);
        COMPARE(doubledouble(0.5).to_float(), 0.5f);
        COMPARE(doubledouble(-0.5).to_float(), -0.5);
        COMPARE(doubledouble(0.5,0.125).to_float(), 0.625f);
        COMPARE(doubledouble(-0.5,-0.125).to_float(), -0.625);
        COMPARE(doubledouble::posinf().to_float(), (float)posinf);
        COMPARE(doubledouble::neginf().to_float(), (float)neginf);
        COMPARE(doubledouble::posnan().to_float(), posnan);
        COMPARE(doubledouble::negnan().to_float(), negnan);

        COMPARE(doubledouble().to_double(), 0.0);
        COMPARE(doubledouble(0.0).to_double(), 0.0);
        COMPARE(doubledouble(-0.0).to_double(), -0.0);
        COMPARE(doubledouble(0.5).to_double(), 0.5);
        COMPARE(doubledouble(-0.5).to_double(), -0.5);
        COMPARE(doubledouble(0.5,0.125).to_double(), 0.625);
        COMPARE(doubledouble(-0.5,-0.125).to_double(), -0.625);
        COMPARE(doubledouble::posinf().to_double(), (double)posinf);
        COMPARE(doubledouble::neginf().to_double(), (double)neginf);
        COMPARE(doubledouble::nan().to_double(), posnan);

        COMPARE(doubledouble().to_long_double(), 0.0L);
        COMPARE(doubledouble(0.0).to_long_double(), 0.0L);
        COMPARE(doubledouble(-0.0).to_long_double(), -0.0L);
        COMPARE(doubledouble(0).to_long_double(), 0.0L);
        COMPARE(doubledouble(0.5).to_long_double(), 0.5L);
        COMPARE(doubledouble(-0.5).to_long_double(), -0.5L);
        COMPARE(doubledouble(0.5,0.125).to_long_double(), 0.625L);
        COMPARE(doubledouble(-0.5,-0.125).to_long_double(), -0.625L);
        COMPARE(doubledouble::posinf().to_long_double(), (long double)posinf);
        COMPARE(doubledouble::neginf().to_long_double(), (long double)neginf);
        COMPARE(doubledouble::nan().to_long_double(), posnan);
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

        COMPARE(doubledouble::e.to_float(), (float)std::numbers::e);
        COMPARE(doubledouble::log2e.to_float(), (float)std::numbers::log2e);
        COMPARE(doubledouble::log10e.to_float(), (float)std::numbers::log10e);
        COMPARE(doubledouble::pi.to_float(), (float)std::numbers::pi);
        COMPARE(doubledouble::inv_pi.to_float(), (float)std::numbers::inv_pi);
        COMPARE(doubledouble::inv_sqrtpi.to_float(), (float)std::numbers::inv_sqrtpi);
        COMPARE(doubledouble::ln2.to_float(), (float)std::numbers::ln2);
        COMPARE(doubledouble::ln10.to_float(), (float)std::numbers::ln10);
        COMPARE(doubledouble::sqrt2.to_float(), (float)std::numbers::sqrt2);
        COMPARE(doubledouble::sqrt3.to_float(), (float)std::numbers::sqrt3);
        COMPARE(doubledouble::inv_sqrt3.to_float(), (float)std::numbers::inv_sqrt3);
        COMPARE(doubledouble::egamma.to_float(), (float)std::numbers::egamma);
        COMPARE(doubledouble::phi.to_float(), (float)std::numbers::phi);
    }
}
