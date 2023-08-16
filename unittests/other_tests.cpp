#include "main.h"

TEST_CASE("Other functions") {

    srand(0);

    SUBCASE("fabs") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double();
            CHECK((doubledouble(x).fabs()).to_float() == float(std::fabs(x)));
        }
    }

    SUBCASE("abs") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double();
            CHECK((doubledouble(x).abs()).to_float() == float(std::abs(x)));
        }
    }

    SUBCASE("fma") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double(), y = rand_double(), z = rand_double();
            CHECK((doubledouble(x).fma(y, z)).to_float() == float(std::fma(x, y, z)));
        }
    }
}
