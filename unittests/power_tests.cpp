#include "main.h"

TEST_CASE("Power functions") {

    srand(0);

    SUBCASE("pow") {

        SUBCASE("Integer exponent (special cases)") {

            COMPARE (doubledouble(0.0).powd(-2), posinf);
            COMPARE (doubledouble(0.0).powd(-1), posinf);
            COMPARE (doubledouble(0.0).powd(0), 1.0);
            COMPARE (doubledouble(0.0).powd(1), 0.0);
            COMPARE (doubledouble(0.0).powd(2), 0.0);
        }

        SUBCASE("Integer exponent") {

            for (int i = 0; i < NUM_TESTS; i++) {

                double b = rand_double();
                int e = (rand() % 5) - 2;

                COMPARE (doubledouble(b).powd(e).to_float(), (float)std::pow(b,e));
            }
        }

        SUBCASE("Fractional exponent (special cases)") {

            doubledouble base = -doubledouble::inf();

            COMPARE (base.pow(doubledouble::neginf()), 0.0);
            COMPARE (base.pow(-2.0), 0.0);
            COMPARE (base.pow(-1.5), 0.0);
            COMPARE (base.pow(-1.0), -0.0);
            COMPARE (base.pow(-0.5), 0.0);
            COMPARE (base.pow(0.0), 1.0);
            COMPARE (base.pow(0.5), posinf);
            COMPARE (base.pow(1.0), neginf);
            COMPARE (base.pow(1.5), posinf);
            COMPARE (base.pow(2.0), posinf);
            COMPARE (base.pow(doubledouble::posinf()), posinf);
            COMPARE (base.pow(doubledouble::posnan()), posnan);

            base = doubledouble(-2.0);

            COMPARE (base.pow(doubledouble::neginf()), 0.0);
            COMPARE (base.pow(-2.0), 0.25);
            COMPARE (base.pow(-1.5), std::pow(-2.0, -1.5));
            COMPARE (base.pow(-1.0), -0.5);
            COMPARE (base.pow(-0.5), std::pow(-2.0, -0.5));
            COMPARE (base.pow(0.0), 1.0);
            COMPARE (base.pow(0.5), std::pow(-2.0, 0.5));
            COMPARE (base.pow(1.0), -2.0);
            COMPARE (base.pow(1.5), std::pow(-2.0, 1.5));
            COMPARE (base.pow(2.0), 4.0);
            COMPARE (base.pow(doubledouble::posinf()), std::pow(-2.0, posinf));
            COMPARE (base.pow(doubledouble::posnan()), std::pow(-2.0, posnan));

            base = doubledouble(-1.5);

            COMPARE (base.pow(doubledouble::neginf()), 0.0);
            CHECK   (base.pow(-2.0).to_string(4) == "0.4444");
            COMPARE (base.pow(-1.5), std::pow(-1.5, -1.5));
            CHECK   (base.pow(-1.0).to_string(4) == "-0.6666");
            COMPARE (base.pow(-0.5), std::pow(-1.5, -0.5));
            COMPARE (base.pow(0.0), 1.0);
            COMPARE (base.pow(0.5), std::pow(-1.5, 0.5));
            COMPARE (base.pow(1.0), -1.5);
            COMPARE (base.pow(1.5), std::pow(-1.5, 1.5));
            COMPARE (base.pow(2.0), 2.25);
            COMPARE (base.pow(doubledouble::posinf()), posinf);
            COMPARE (base.pow(doubledouble::posnan()), posnan);

            base = doubledouble(-1.0);

            COMPARE (base.pow(doubledouble::neginf()), 1.0);
            COMPARE (base.pow(-2.0), 1.0);
            COMPARE (base.pow(-1.5), std::pow(-1.0, -1.5));
            COMPARE (base.pow(-1.0), -1.0);
            COMPARE (base.pow(-0.5), std::pow(-1.0, -0.5));
            COMPARE (base.pow(0.0), 1.0);
            COMPARE (base.pow(0.5), std::pow(-1.0, 0.5));
            COMPARE (base.pow(1.0), -1.0);
            COMPARE (base.pow(1.5), std::pow(-1.0, 1.5));
            COMPARE (base.pow(2.0), 1.0);
            COMPARE (base.pow(doubledouble::posinf()), 1.0);
            COMPARE (base.pow(doubledouble::posnan()), posnan);

            base = doubledouble(-0.5);

            COMPARE (base.pow(doubledouble::neginf()), posinf);
            COMPARE (base.pow(-2.0), 4.0);
            COMPARE (base.pow(-1.5), std::pow(-0.5, -1.5));
            COMPARE (base.pow(-1.0), -2.0);
            COMPARE (base.pow(-0.5), std::pow(-0.5, -0.5));
            COMPARE (base.pow(0.0), 1.0);
            COMPARE (base.pow(0.5), std::pow(-0.5, 0.5));
            COMPARE (base.pow(1.0), -0.5);
            COMPARE (base.pow(1.5), std::pow(-0.5, 1.5));
            COMPARE (base.pow(2.0), 0.25);
            COMPARE (base.pow(doubledouble::posinf()), 0.0);
            COMPARE (base.pow(doubledouble::posnan()), posnan);

            base = doubledouble(0.0);

            COMPARE (base.pow(doubledouble::neginf()), posinf);
            COMPARE (base.pow(-2.0), std::pow(0.0, -2.0));
            COMPARE (base.pow(-1.5), std::pow(0.0, -1.5));
            COMPARE (base.pow(-1.0), std::pow(0.0, -1.0));
            COMPARE (base.pow(-0.5), std::pow(0.0, -0.5));
            COMPARE (base.pow(0.0), 1.0);
            COMPARE (base.pow(0.5), 0.0);
            COMPARE (base.pow(1.0), 0.0);
            COMPARE (base.pow(1.5), 0.0);
            COMPARE (base.pow(2.0), 0.0);
            COMPARE (base.pow(doubledouble::posinf()), 0.0);
            COMPARE (base.pow(doubledouble::posnan()), posnan);

            base = doubledouble(-0.0);

            COMPARE (base.pow(doubledouble::neginf()), posinf);
            COMPARE (base.pow(-2.0), std::pow(-0.0, -2.0));
            COMPARE (base.pow(-1.5), std::pow(-0.0, -1.5));
            COMPARE (base.pow(-1.0), std::pow(-0.0, -1.0));
            COMPARE (base.pow(-0.5), std::pow(-0.0, -0.5));
            COMPARE (base.pow(0.0), 1.0);
            COMPARE (base.pow(0.5), 0.0);
            COMPARE (base.pow(1.0), -0.0);
            COMPARE (base.pow(1.5), 0.0);
            COMPARE (base.pow(2.0), 0.0);
            COMPARE (base.pow(doubledouble::posinf()), 0.0);
            COMPARE (base.pow(doubledouble::posnan()), posnan);

            base = doubledouble(0.5);

            COMPARE (base.pow(doubledouble::neginf()), std::pow(0.5, neginf));
            COMPARE (base.pow(-2.0), 4.0);
            CHECK   (base.pow(-1.5).to_string(4) == "2.8284");
            COMPARE (base.pow(-1.0), 2.0);
            CHECK   (base.pow(-0.5).to_string(4) == "1.4142");
            COMPARE (base.pow(0.0), 1.0);
            CHECK   (base.pow(0.5).to_string(4) == "0.7071");
            COMPARE (base.pow(1.0), 0.5);
            CHECK   (base.pow(1.5).to_string(4) == "0.3535");
            COMPARE (base.pow(2.0), 0.25);
            COMPARE (base.pow(doubledouble::posinf()), std::pow(0.5, posinf));
            COMPARE (base.pow(doubledouble::posnan()), std::pow(0.5, posnan));

            base = doubledouble(1.0);

            COMPARE (base.pow(doubledouble::neginf()), std::pow(1.0, neginf));
            COMPARE (base.pow(-2.0), 1.0);
            COMPARE (base.pow(-1.5), 1.0);
            COMPARE (base.pow(-1.0), 1.0);
            COMPARE (base.pow(-0.5), 1.0);
            COMPARE (base.pow(0.0), 1.0);
            COMPARE (base.pow(0.5), 1.0);
            COMPARE (base.pow(1.0), 1.0);
            COMPARE (base.pow(1.5), 1.0);
            COMPARE (base.pow(2.0), 1.0);
            COMPARE (base.pow(doubledouble::posinf()), std::pow(1.0, posinf));
            COMPARE (base.pow(doubledouble::posnan()), std::pow(1.0, posnan));

            base = doubledouble(1.5);

            COMPARE (base.pow(doubledouble::neginf()), std::pow(1.5, neginf));
            CHECK   (base.pow(-2.0).to_string(4) == "0.4444");
            CHECK   (base.pow(-1.5).to_string(4) == "0.5443");
            CHECK   (base.pow(-1.0).to_string(4) == "0.6666");
            CHECK   (base.pow(-0.5).to_string(4) == "0.8164");
            COMPARE (base.pow(0.0), 1.0);
            CHECK   (base.pow(0.5).to_string(4) == "1.2247");
            COMPARE (base.pow(1.0), 1.5);
            CHECK   (base.pow(1.5).to_string(4) == "1.8371");
            COMPARE (base.pow(2.0), 2.25);
            COMPARE (base.pow(doubledouble::posinf()), std::pow(1.5, posinf));
            COMPARE (base.pow(doubledouble::posnan()), std::pow(1.5, posnan));

            base = doubledouble(2.0);

            COMPARE (base.pow(doubledouble::neginf()), std::pow(2.0, neginf));
            CHECK   (base.pow(-2.0).to_string(4) == "0.2500");
            CHECK   (base.pow(-1.5).to_string(4) == "0.3535");
            CHECK   (base.pow(-1.0).to_string(4) == "0.5000");
            CHECK   (base.pow(-0.5).to_string(4) == "0.7071");
            CHECK   (base.pow(0.0).to_string(4) == "1.0000");
            CHECK   (base.pow(0.5).to_string(4) == "1.4142");
            CHECK   (base.pow(1.0).to_string(4) == "2.0000");
            CHECK   (base.pow(1.5).to_string(4) == "2.8284");
            CHECK   (base.pow(2.0).to_string(4) == "4.0000");
            COMPARE (base.pow(doubledouble::posinf()), std::pow(2.0, posinf));
            COMPARE (base.pow(doubledouble::posnan()), std::pow(2.0, posnan));

            base = doubledouble::posinf();

            COMPARE (base.pow(doubledouble::neginf()), std::pow(posinf, neginf));
            COMPARE (base.pow(-2.0), 0.0);
            COMPARE (base.pow(-1.5), 0.0);
            COMPARE (base.pow(-1.0), 0.0);
            COMPARE (base.pow(-0.5), 0.0);
            COMPARE (base.pow(0.0), 1.0);
            COMPARE (base.pow(0.5), posinf);
            COMPARE (base.pow(1.0), posinf);
            COMPARE (base.pow(1.5), posinf);
            COMPARE (base.pow(2.0), posinf);
            COMPARE (base.pow(doubledouble::posinf()), std::pow(posinf, posinf));
            COMPARE (base.pow(doubledouble::posnan()), std::pow(posinf, posnan));
        }

        SUBCASE("Fractional exponent") {

            for (int i = 0; i < NUM_TESTS; i++) {

                double b = rand_double_pos();
                double e = rand_double();

                COMPARE (doubledouble(b).pow(doubledouble(e)).to_float(), (float)std::pow(b,e));
            }
        }
    }

    SUBCASE("sqrt") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double_pos();
            COMPARE (doubledouble(x).sqrt().to_float(), (float)std::sqrt(x));
        }

        // 1.4142135623730950488016887242096980785696718753769480731766797379
        doubledouble sqrt2 = doubledouble(2).sqrt();
        CHECK (sqrt2.to_string(30) == "1.414213562373095048801688724209");

        // 1.6487212707001281468486507878141635716537761007101480115750793116
        doubledouble sqrte = doubledouble::e.sqrt();
        CHECK (sqrte.to_string(30) == "1.648721270700128146848650787814");
    }
}
