#include "main.h"

TEST_CASE("Floating-point manipulation functions") {

    SUBCASE("copysign") {

        doubledouble pi = doubledouble::pi;

        doubledouble x = 1.0;
        doubledouble y = -1.0;

        COMPARE (pi.copysign(x), pi);
        COMPARE ((-pi).copysign(x), pi);
        COMPARE (pi.copysign(y), -pi);
        COMPARE ((-pi).copysign(y), -pi);

        COMPARE (doubledouble::posinf().copysign(x), posinf);
        COMPARE (doubledouble::posinf().copysign(y), neginf);
        COMPARE (doubledouble::neginf().copysign(x), posinf);
        COMPARE (doubledouble::neginf().copysign(y), neginf);
        COMPARE (doubledouble::posnan().copysign(x), posnan);
        COMPARE (doubledouble::posnan().copysign(y), negnan);
        COMPARE (doubledouble::negnan().copysign(x), posnan);
        COMPARE (doubledouble::negnan().copysign(y), negnan);
    }
}
