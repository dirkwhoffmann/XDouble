#include "main.h"

TEST_CASE("Power functions") {

    srand(0);

    SUBCASE("pow") {

        SUBCASE("integer exponent") {

            for (int i = 0; i < NUM_TESTS; i++) {

                double b = rand_double();
                int e = (rand() % 5) - 2;

                CHECK(doubledouble(b).pow(e).to_float() == (float)std::pow(b,e));
            }
        }
        SUBCASE("fractional exponent") {

            for (int i = 0; i < NUM_TESTS; i++) {

                double b = rand_double_pos();
                double e = rand_double();

                CHECK(doubledouble(b).pow(doubledouble(e)).to_float() == (float)std::pow(b,e));
            }

            CHECK(doubledouble(-2).pow(doubledouble(2)).isnan());
        }
    }

    SUBCASE("sqrt") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double_pos();
            CHECK(doubledouble(x).sqrt().to_float() == (float)std::sqrt(x));
        }

        CHECK(doubledouble(-2).sqrt().isnan());
    }

}
