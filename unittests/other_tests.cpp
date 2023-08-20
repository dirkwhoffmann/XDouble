#include "main.h"

TEST_CASE("Other functions") {

    srand(0);

    SUBCASE("fabs") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double();
            CHECK((doubledouble(x).fabs()).to_float() == float(std::fabs(x)));
        }

        CHECK(doubledouble::nan().fabs().isnan());
        CHECK(doubledouble::inf().fabs().isinf());
        CHECK((-doubledouble::inf()).fabs().isinf());
        CHECK(doubledouble::inf().fabs().signbit() == 0);
        CHECK((-doubledouble::inf()).fabs().signbit() == 0);
    }

    SUBCASE("abs") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double();
            CHECK((doubledouble(x).abs()).to_float() == float(std::abs(x)));
        }

        CHECK(doubledouble::nan().abs().isnan());
        CHECK(doubledouble::inf().abs().isinf());
        CHECK((-doubledouble::inf()).abs().isinf());
        CHECK(doubledouble::inf().abs().signbit() == 0);
        CHECK((-doubledouble::inf()).abs().signbit() == 0);
    }
}
