#include "main.h"

TEST_CASE("Minimum, maximum, difference functions") {

    SUBCASE("fdim") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            double y = rand_double();

            COMPARE (doubledouble(x).fdim(y).to_float(), (float)std::fdim(x, y));
        }

        COMPARE (doubledouble::posinf().fdim(2.0), std::fdim(posinf, 2.0));
        COMPARE (doubledouble::neginf().fdim(2.0), std::fdim(neginf, 2.0));
        COMPARE (doubledouble::posnan().fdim(2.0), std::fdim(posnan, 2.0));
        COMPARE (doubledouble::negnan().fdim(2.0), std::fdim(negnan, 2.0));
    }

    SUBCASE("fmax") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            double y = rand_double();

            COMPARE (doubledouble(x).fmax(y).to_float(), (float)std::fmax(x, y));
        }

        COMPARE (doubledouble::posinf().fmax(2.0), std::fmax(posinf, 2.0));
        COMPARE (doubledouble::neginf().fmax(2.0), std::fmax(neginf, 2.0));
        COMPARE (doubledouble::posnan().fmax(2.0), std::fmax(posnan, 2.0));
        COMPARE (doubledouble::negnan().fmax(2.0), std::fmax(negnan, 2.0));
    }

    SUBCASE("fmin") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            double y = rand_double();

            COMPARE (doubledouble(x).fmin(y).to_float(), (float)std::fmin(x, y));
        }

        COMPARE (doubledouble::posinf().fmin(2.0), std::fmin(posinf, 2.0));
        COMPARE (doubledouble::neginf().fmin(2.0), std::fmin(neginf, 2.0));
        COMPARE (doubledouble::posnan().fmin(2.0), std::fmin(posnan, 2.0));
        COMPARE (doubledouble::negnan().fmin(2.0), std::fmin(negnan, 2.0));
    }
}
