#include "main.h"

TEST_CASE("Minimum, maximum, difference functions") {

    SUBCASE("fdim") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            double y = rand_double();

            CHECK(doubledouble(x).fdim(y).to_float() == (float)std::fdim(x, y));
        }

        CHECK(doubledouble::inf().fdim(2.0) == std::fdim(std::numeric_limits<double>::infinity(), 2.0));
        CHECK((-doubledouble::inf()).fdim(2.0) == std::fdim(-std::numeric_limits<double>::infinity(), 2.0));
        CHECK(doubledouble(2.0).fdim(doubledouble::nan()).isnan());
        CHECK(doubledouble::nan().fdim(2.0).isnan());
    }

    SUBCASE("fmax") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            double y = rand_double();

            CHECK(doubledouble(x).fmax(y).to_float() == (float)std::fmax(x, y));
        }

        CHECK(doubledouble::inf().fmax(2.0) == std::fmax(std::numeric_limits<double>::infinity(), 2.0));
        CHECK((-doubledouble::inf()).fmax(2.0) == std::fmax(-std::numeric_limits<double>::infinity(), 2.0));
        CHECK(doubledouble(2.0).fmax(doubledouble::nan()) == 2.0);
        CHECK(doubledouble::nan().fmax(2.0) == 2.0);
    }

    SUBCASE("fmin") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            double y = rand_double();

            CHECK(doubledouble(x).fmin(y).to_float() == (float)std::fmin(x, y));
        }

        CHECK(doubledouble::inf().fmin(2.0) == std::fmin(std::numeric_limits<double>::infinity(), 2.0));
        CHECK((-doubledouble::inf()).fmin(2.0) == std::fmin(-std::numeric_limits<double>::infinity(), 2.0));
        CHECK(doubledouble(2.0).fmin(doubledouble::nan()) == 2.0);
        CHECK(doubledouble::nan().fmin(2.0) == 2.0);
    }
}
