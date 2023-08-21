#include "main.h"

TEST_CASE("Power functions") {

    srand(0);

    SUBCASE("pow") {

        SUBCASE("Integer exponent (special cases)") {

            CHECK(doubledouble(0.0).powd(-2) == doubledouble::inf());
            CHECK(doubledouble(0.0).powd(-1) == doubledouble::inf());
            CHECK(doubledouble(0.0).powd(0) == 1.0);
            CHECK(doubledouble(0.0).powd(1) == 0.0);
            CHECK(doubledouble(0.0).powd(2) == 0.0);
        }

        SUBCASE("Integer exponent") {

            for (int i = 0; i < NUM_TESTS; i++) {

                double b = rand_double();
                int e = (rand() % 5) - 2;

                CHECK(doubledouble(b).powd(e).to_float() == (float)std::pow(b,e));
            }
        }

        SUBCASE("Fractional exponent (special cases)") {

            doubledouble base = -doubledouble::inf();

            CHECK(base.pow(-doubledouble::inf()).isposzero());
            CHECK(base.pow(-2.0).isposzero());
            CHECK(base.pow(-1.5).isposzero());
            CHECK(base.pow(-1.0).isnegzero());
            CHECK(base.pow(-0.5).isposzero());
            CHECK(base.pow(0.0) == 1.0);
            CHECK(base.pow(0.5).isposinf());
            CHECK(base.pow(1.0).isneginf());
            CHECK(base.pow(1.5).isposinf());
            CHECK(base.pow(2.0).isposinf());
            CHECK(base.pow(doubledouble::inf()).isposinf());
            CHECK(base.pow(doubledouble::nan()).isnan());

            base = doubledouble(-2.0);

            CHECK(base.pow(-doubledouble::inf()).isposzero());
            CHECK(base.pow(-2.0) == 0.25);
            CHECK(base.pow(-1.5).isnan());
            CHECK(base.pow(-1.0) == -0.5);
            CHECK(base.pow(-0.5).isnan());
            CHECK(base.pow(0.0) == 1.0);
            CHECK(base.pow(0.5).isnan());
            CHECK(base.pow(1.0) == -2.0);
            CHECK(base.pow(1.5).isnan());
            CHECK(base.pow(2.0) == 4.0);
            CHECK(base.pow(doubledouble::inf()).isinf());
            CHECK(base.pow(doubledouble::nan()).isnan());

            base = doubledouble(-1.5);

            CHECK(base.pow(-doubledouble::inf()).isposzero());
            CHECK(base.pow(-2.0).to_string(4) == "0.4444");
            CHECK(base.pow(-1.5).isnan());
            CHECK(base.pow(-1.0).to_string(4) == "-0.6666");
            CHECK(base.pow(-0.5).isnan());
            CHECK(base.pow(0.0) == 1.0);
            CHECK(base.pow(0.5).isnan());
            CHECK(base.pow(1.0) == -1.5);
            CHECK(base.pow(1.5).isnan());
            CHECK(base.pow(2.0) == 2.25);
            CHECK(base.pow(doubledouble::inf()).isinf());
            CHECK(base.pow(doubledouble::nan()).isnan());

            base = doubledouble(-1.0);

            CHECK(base.pow(-doubledouble::inf()) == 1.0);
            CHECK(base.pow(-2.0) == 1.0);
            CHECK(base.pow(-1.5).isnan());
            CHECK(base.pow(-1.0) == -1.0);
            CHECK(base.pow(-0.5).isnan());
            CHECK(base.pow(0.0) == 1.0);
            CHECK(base.pow(0.5).isnan());
            CHECK(base.pow(1.0) == -1.0);
            CHECK(base.pow(1.5).isnan());
            CHECK(base.pow(2.0) == 1.0);
            CHECK(base.pow(doubledouble::inf()) == 1.0);
            CHECK(base.pow(doubledouble::nan()).isnan());

            base = doubledouble(-0.5);

            CHECK(base.pow(-doubledouble::inf()).isinf());
            CHECK(base.pow(-2.0) == 4.0);
            CHECK(base.pow(-1.5).isnan());
            CHECK(base.pow(-1.0) == -2.0);
            CHECK(base.pow(-0.5).isnan());
            CHECK(base.pow(0.0) == 1.0);
            CHECK(base.pow(0.5).isnan());
            CHECK(base.pow(1.0) == -0.5);
            CHECK(base.pow(1.5).isnan());
            CHECK(base.pow(2.0) == 0.25);
            CHECK(base.pow(doubledouble::inf()).isposzero());
            CHECK(base.pow(doubledouble::nan()).isnan());

            base = doubledouble(0.0);

            CHECK(base.pow(-doubledouble::inf()) == doubledouble::inf());
            CHECK(base.pow(-2.0) == doubledouble::inf());
            CHECK(base.pow(-1.5) == doubledouble::inf());
            CHECK(base.pow(-1.0) == doubledouble::inf());
            CHECK(base.pow(-0.5) == doubledouble::inf());
            CHECK(base.pow(0.0) == 1.0);
            CHECK(base.pow(0.5).isposzero());
            CHECK(base.pow(1.0).isposzero());
            CHECK(base.pow(1.5).isposzero());
            CHECK(base.pow(2.0).isposzero());
            CHECK(base.pow(doubledouble::inf()).isposzero());
            CHECK(base.pow(doubledouble::nan()).isnan());

            base = doubledouble(-0.0);

            CHECK(base.pow(-doubledouble::inf()) == doubledouble::inf());
            CHECK(base.pow(-2.0) == doubledouble::posinf());
            CHECK(base.pow(-1.5) == doubledouble::posinf());
            CHECK(base.pow(-1.0) == doubledouble::neginf());
            CHECK(base.pow(-0.5) == doubledouble::posinf());
            CHECK(base.pow(0.0) == 1.0);
            CHECK(base.pow(0.5).isposzero());
            CHECK(base.pow(1.0).isnegzero());
            CHECK(base.pow(1.5).isposzero());
            CHECK(base.pow(2.0).isposzero());
            CHECK(base.pow(doubledouble::inf()).isposzero());
            CHECK(base.pow(doubledouble::nan()).isnan());

            base = doubledouble(0.5);

            CHECK(base.pow(-doubledouble::inf()) == doubledouble::inf());
            CHECK(base.pow(-2.0) == 4.0);
            CHECK(base.pow(-1.5).to_string(4) == "2.8284");
            CHECK(base.pow(-1.0) == 2.0);
            CHECK(base.pow(-0.5).to_string(4) == "1.4142");
            CHECK(base.pow(0.0) == 1.0);
            CHECK(base.pow(0.5).to_string(4) == "0.7071");
            CHECK(base.pow(1.0) == 0.5);
            CHECK(base.pow(1.5).to_string(4) == "0.3535");
            CHECK(base.pow(2.0) == 0.25);
            CHECK(base.pow(doubledouble::inf()).isposzero());
            CHECK(base.pow(doubledouble::nan()).isnan());

            base = doubledouble(1.0);

            CHECK(base.pow(-doubledouble::inf()) == 1.0);
            CHECK(base.pow(-2.0) == 1.0);
            CHECK(base.pow(-1.5) == 1.0);
            CHECK(base.pow(-1.0) == 1.0);
            CHECK(base.pow(-0.5) == 1.0);
            CHECK(base.pow(0.0) == 1.0);
            CHECK(base.pow(0.5) == 1.0);
            CHECK(base.pow(1.0) == 1.0);
            CHECK(base.pow(1.5) == 1.0);
            CHECK(base.pow(2.0) == 1.0);
            CHECK(base.pow(doubledouble::inf()) == 1.0);
            CHECK(base.pow(doubledouble::nan()) == 1.0);

            base = doubledouble(1.5);

            CHECK(base.pow(-doubledouble::inf()).isposzero());
            CHECK(base.pow(-2.0).to_string(4) == "0.4444");
            CHECK(base.pow(-1.5).to_string(4) == "0.5443");
            CHECK(base.pow(-1.0).to_string(4) == "0.6666");
            CHECK(base.pow(-0.5).to_string(4) == "0.8164");
            CHECK(base.pow(0.0) == 1.0);
            CHECK(base.pow(0.5).to_string(4) == "1.2247");
            CHECK(base.pow(1.0) == 1.5);
            CHECK(base.pow(1.5).to_string(4) == "1.8371");
            CHECK(base.pow(2.0) == 2.25);
            CHECK(base.pow(doubledouble::inf()).isposinf());
            CHECK(base.pow(doubledouble::nan()).isnan());

            base = doubledouble(2.0);

            CHECK(base.pow(-doubledouble::inf()).isposzero());
            CHECK(base.pow(-2.0).to_string(4) == "0.2500");
            CHECK(base.pow(-1.5).to_string(4) == "0.3535");
            CHECK(base.pow(-1.0).to_string(4) == "0.5000");
            CHECK(base.pow(-0.5).to_string(4) == "0.7071");
            CHECK(base.pow(0.0).to_string(4) == "1.0000");
            CHECK(base.pow(0.5).to_string(4) == "1.4142");
            CHECK(base.pow(1.0).to_string(4) == "2.0000");
            CHECK(base.pow(1.5).to_string(4) == "2.8284");
            CHECK(base.pow(2.0).to_string(4) == "4.0000");
            CHECK(base.pow(doubledouble::inf()).isposinf());
            CHECK(base.pow(doubledouble::nan()).isnan());

            base = doubledouble::inf();

            CHECK(base.pow(-doubledouble::inf()).isposzero());
            CHECK(base.pow(-2.0).isposzero());
            CHECK(base.pow(-1.5).isposzero());
            CHECK(base.pow(-1.0).isposzero());
            CHECK(base.pow(-0.5).isposzero());
            CHECK(base.pow(0.0) == 1.0);
            CHECK(base.pow(0.5).isinf());
            CHECK(base.pow(1.0).isinf());
            CHECK(base.pow(1.5).isinf());
            CHECK(base.pow(2.0).isinf());
            CHECK(base.pow(doubledouble::inf()).isinf());
            CHECK(base.pow(doubledouble::nan()).isnan());

            /*
            std::cout << std::endl;
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
            */
        }

        SUBCASE("Fractional exponent") {

            for (int i = 0; i < NUM_TESTS; i++) {

                double b = rand_double_pos();
                double e = rand_double();

                CHECK(doubledouble(b).pow(doubledouble(e)).to_float() == (float)std::pow(b,e));
            }
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
