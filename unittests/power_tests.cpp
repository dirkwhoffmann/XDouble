#include "doctest.h"
#include "double-double.h"

TEST_CASE("Power functions") {

    srand(0);

    SUBCASE("pow") {

        SUBCASE("integer exponent") {

            for (int i = 0; i < 100; i++) {

                double b = (rand() % 128) - 64.0 + 1.0 / rand();
                int e = (rand() % 5) - 2;

                CHECK(doubledouble(b).pow(e).to_float() == (float)std::pow(b,e));
            }
        }
        SUBCASE("fractional exponent") {

            for (int i = 0; i < 100; i++) {

                double b = (rand() % 128) + 1.0 / rand();
                double e = (rand() % 5) - 2 + 1.0 / rand();

                CHECK(doubledouble(b).pow(doubledouble(e)).to_float() == (float)std::pow(b,e));
            }

            CHECK(doubledouble(-2).pow(doubledouble(2)).isnan());
        }
    }

    SUBCASE("sqrt") {

        for (int i = 0; i < 100; i++) {

            double x = (rand() % 128) + 1.0 / rand();
            CHECK(doubledouble(x).sqrt().to_float() == (float)std::sqrt(x));
        }

        CHECK(doubledouble(-2).sqrt().isnan());
    }

}
