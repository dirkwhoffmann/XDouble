#include "main.h"

TEST_CASE("Floating-point manipulation functions") {

    SUBCASE("copysign") {

        doubledouble pi = doubledouble::pi;

        doubledouble x = 1.0;
        doubledouble y = -1.0;

        CHECK(pi.copysign(x) == pi);
        CHECK(pi.copysign(y) == -pi);
        CHECK((-pi).copysign(x) == -pi);
        CHECK((-pi).copysign(y) == pi);

        CHECK(doubledouble::inf().copysign(x) == doubledouble::inf());
        CHECK(doubledouble::inf().copysign(y) == -doubledouble::inf());
        CHECK(doubledouble::nan().copysign(x).isnan());
        CHECK(doubledouble::nan().copysign(y).isnan());
    }
}
