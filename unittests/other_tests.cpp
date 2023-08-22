#include "main.h"

TEST_CASE("Other functions") {

    srand(0);

    SUBCASE("fabs") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double();
            COMPARE ((doubledouble(x).fabs()).to_float(), float(std::fabs(x)));
        }

        COMPARE (doubledouble::posnan().fabs(), std::fabs(posnan));
        COMPARE (doubledouble::negnan().fabs(), std::fabs(negnan));
        COMPARE (doubledouble::posinf().fabs(), std::fabs(posinf));
        COMPARE (doubledouble::neginf().fabs(), std::fabs(neginf));
    }

    SUBCASE("abs") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double();
            COMPARE ((doubledouble(x).abs()).to_float(), float(std::abs(x)));
        }

        COMPARE (doubledouble::posnan().abs(), std::abs(posnan));
        COMPARE (doubledouble::negnan().abs(), std::abs(negnan));
        COMPARE (doubledouble::posinf().abs(), std::abs(posinf));
        COMPARE (doubledouble::neginf().abs(), std::abs(neginf));
    }
}
