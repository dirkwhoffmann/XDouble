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
}
