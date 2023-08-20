#include "main.h"

TEST_CASE("Power functions") {

    srand(0);

    SUBCASE("pow") {

        SUBCASE("Integer exponent") {

            for (int i = 0; i < NUM_TESTS; i++) {

                double b = rand_double();
                int e = (rand() % 5) - 2;

                CHECK(doubledouble(b).powd(e).to_float() == (float)std::pow(b,e));
            }

            CHECK(doubledouble(0.0).powd(-2) == doubledouble::inf());
            CHECK(doubledouble(0.0).powd(-1) == doubledouble::inf());
            CHECK(doubledouble(0.0).powd(0) == 1.0);
            CHECK(doubledouble(0.0).powd(1) == 0.0);
            CHECK(doubledouble(0.0).powd(2) == 0.0);



        }

        SUBCASE("Fractional exponent") {

            for (int i = 0; i < NUM_TESTS; i++) {

                double b = rand_double_pos();
                double e = rand_double();

                CHECK(doubledouble(b).pow(doubledouble(e)).to_float() == (float)std::pow(b,e));
            }

            CHECK(doubledouble(0.0).pow(-doubledouble::inf()) == doubledouble::inf());
            CHECK(doubledouble(0.0).pow(-2.0) == doubledouble::inf());
            CHECK(doubledouble(0.0).pow(-1.5) == doubledouble::inf());
            CHECK(doubledouble(0.0).pow(-1.0) == doubledouble::inf());
            CHECK(doubledouble(0.0).pow(-0.5) == doubledouble::inf());
            CHECK(doubledouble(0.0).pow(0.0) == 1.0);
            CHECK(doubledouble(0.0).pow(0.5).ispluszero());
            CHECK(doubledouble(0.0).pow(1.0).ispluszero());
            CHECK(doubledouble(0.0).pow(1.5).ispluszero());
            CHECK(doubledouble(0.0).pow(2.0).ispluszero());
            CHECK(doubledouble(0.0).pow(doubledouble::inf()).ispluszero());
            CHECK(doubledouble(0.0).pow(doubledouble::nan()).isnan());

            CHECK(doubledouble(-0.0).pow(-doubledouble::inf()) == doubledouble::inf());
            CHECK(doubledouble(-0.0).pow(-2.0) == doubledouble::inf());
            CHECK(doubledouble(-0.0).pow(-1.5) == doubledouble::inf());
            CHECK(doubledouble(-0.0).pow(-1.0) == -doubledouble::inf());
            CHECK(doubledouble(-0.0).pow(-0.5) == doubledouble::inf());
            CHECK(doubledouble(-0.0).pow(0.0) == 1.0);
            CHECK(doubledouble(-0.0).pow(0.5).ispluszero());
            CHECK(doubledouble(-0.0).pow(1.0).isminuszero());
            CHECK(doubledouble(-0.0).pow(1.5).ispluszero());
            CHECK(doubledouble(-0.0).pow(2.0).ispluszero());
            CHECK(doubledouble(-0.0).pow(doubledouble::inf()).ispluszero());
            CHECK(doubledouble(-0.0).pow(doubledouble::nan()).isnan());



            auto base = -0.0;
            std::cout << "1: = " << std::pow(base, -std::numeric_limits<double>::infinity()) << std::endl;
            std::cout << "2: = " << std::pow(base, -2.0) << std::endl;
            std::cout << "3: = " << std::pow(base, -1.5) << std::endl;
            std::cout << "4: = " << std::pow(base, -1.0) << std::endl;
            std::cout << "5: = " << std::pow(base, -0.5) << std::endl;
            std::cout << "6: = " << std::pow(base, 0.0) << std::endl;
            std::cout << "7: = " << std::pow(base, 0.5) << std::endl;
            std::cout << "8: = " << std::pow(base, 1.0) << std::endl;
            std::cout << "9: = " << std::pow(base, 1.5) << std::endl;
            std::cout << "A: = " << std::pow(base, 2.0) << std::endl;
            std::cout << "B: = " << std::pow(base, std::numeric_limits<double>::infinity()) << std::endl;
            std::cout << "C: = " << std::pow(base, std::numeric_limits<double>::quiet_NaN()) << std::endl;

/*
            CHECK(doubledouble(1.0).pow(-doubledouble::inf()) == 1.0);
            CHECK(doubledouble(1.0).pow(-2.0) == 1.0);
            CHECK(doubledouble(1.0).pow(-1.0) == 1.0);
            CHECK(doubledouble(1.0).pow(0.0) == 1.0);
            CHECK(doubledouble(1.0).pow(1.0) == 1.0);
            CHECK(doubledouble(1.0).pow(2.0) == 1.0);
            CHECK(doubledouble(1.0).pow(doubledouble::inf()) == 1.0);
            CHECK(doubledouble(1.0).pow(doubledouble::nan()) == 1.0);

            CHECK(doubledouble(-doubledouble::inf()).pow(-doubledouble::inf()) == 0.0);
            CHECK(doubledouble(-doubledouble::inf()).pow(-2.5) == 0.0);
            CHECK(doubledouble(-doubledouble::inf()).pow(-1.5) == 0.0);
            CHECK(doubledouble(-doubledouble::inf()).pow(0.0) == 1.0);
            CHECK(doubledouble(-doubledouble::inf()).pow(1.5) == doubledouble::inf());
            CHECK(doubledouble(-doubledouble::inf()).pow(2.5) == doubledouble::inf());
            CHECK(doubledouble(-doubledouble::inf()).pow(doubledouble::inf()) == doubledouble::inf());
            CHECK(doubledouble(-doubledouble::inf()).pow(doubledouble::nan()) == doubledouble::nan());

            CHECK(doubledouble(-2).pow(doubledouble(2)).isnan());
 */
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
        doubledouble sqrte = doubledouble::e.sqrt();
        CHECK(sqrte.to_string(30) == "1.648721270700128146848650787814");
    }
}
