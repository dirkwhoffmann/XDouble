#include "main.h"

TEST_CASE("Power functions") {

    srand(0);

    SUBCASE("pow") {

        SUBCASE("integer exponent") {

            for (int i = 0; i < NUM_TESTS; i++) {

                double b = rand_double();
                int e = (rand() % 5) - 2;

                if (doubledouble(b).pow(e).to_float() != (float)std::pow(b,e)) {
                    printf("i = %d b = %f e = %d\n", i, b, e);
                }
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

        // 1.4142135623730950488016887242096980785696718753769480731766797379
        doubledouble sqrt2 = doubledouble(2).sqrt();
        CHECK(sqrt2.to_string(30) == "1.414213562373095048801688724209");

        // 1.6487212707001281468486507878141635716537761007101480115750793116
        doubledouble sqrte = doubledouble::e_v.sqrt();
        CHECK(sqrte.to_string(30) == "1.648721270700128146848650787814");

    }
}
