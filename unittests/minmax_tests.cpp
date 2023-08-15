#include "main.h"

TEST_CASE("Minimum, maximum, difference functions") {

    SUBCASE("fdim") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            double y = rand_double();

            CHECK(doubledouble(x).fdim(y).to_float() == (float)std::fdim(x, y));
        }
    }

    SUBCASE("fmax") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            double y = rand_double();

            CHECK(doubledouble(x).fmax(y).to_float() == (float)std::fmax(x, y));
        }
    }

    SUBCASE("fmin") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            double y = rand_double();

            CHECK(doubledouble(x).fmin(y).to_float() == (float)std::fmin(x, y));
        }
    }
}
