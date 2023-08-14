#include "doctest.h"
#include "double-double.h"

TEST_CASE("Conversion") {

    SUBCASE("Casts") {

        doubledouble x = doubledouble::pi;

        auto y1 = (long double)x;
        auto y2 = (double)x;
        auto y3 = (float)x;

    }
}
