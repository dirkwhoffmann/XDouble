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
    }

    SUBCASE("nan") {

        CHECK(doubledouble::nan().isnan());
    }
}
