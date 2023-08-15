#include "main.h"

TEST_CASE("Rounding and remainder functions") {

#pragma STDC FENV_ACCESS ON

    srand(0);

    SUBCASE("ceil") {

        CHECK(doubledouble(2.75).ceil().to_float() == 3);
        CHECK(doubledouble(2.5).ceil().to_float() == 3);
        CHECK(doubledouble(2.25).ceil().to_float() == 3);
        CHECK(doubledouble(2.0).ceil().to_float() == 2);
        CHECK(doubledouble(1.75).ceil().to_float() == 2);
        CHECK(doubledouble(1.5).ceil().to_float() == 2);
        CHECK(doubledouble(1.25).ceil().to_float() == 2);
        CHECK(doubledouble(1.0).ceil().to_float() == 1);
        CHECK(doubledouble(0.75).ceil().to_float() == 1);
        CHECK(doubledouble(0.5).ceil().to_float() == 1);
        CHECK(doubledouble(0.25).ceil().to_float() == 1);
        CHECK(doubledouble(0).ceil().to_float() == 0);
        CHECK(doubledouble(-0.25).ceil().to_float() == 0);
        CHECK(doubledouble(-0.5).ceil().to_float() == 0);
        CHECK(doubledouble(-0.75).ceil().to_float() == 0);
        CHECK(doubledouble(-1.0).ceil().to_float() == -1);
        CHECK(doubledouble(-1.25).ceil().to_float() == -1);
        CHECK(doubledouble(-1.5).ceil().to_float() == -1);
        CHECK(doubledouble(-1.75).ceil().to_float() == -1);
        CHECK(doubledouble(-2).ceil().to_float() == -2);
        CHECK(doubledouble(-2.25).ceil().to_float() == -2);
        CHECK(doubledouble(-2.5).ceil().to_float() == -2);
        CHECK(doubledouble(-2.75).ceil().to_float() == -2);

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).ceil().to_float() == (float)std::ceil(x));
        }
    }

    SUBCASE("floor") {

        CHECK(doubledouble(2.75).floor().to_float() == 2);
        CHECK(doubledouble(2.5).floor().to_float() == 2);
        CHECK(doubledouble(2.25).floor().to_float() == 2);
        CHECK(doubledouble(2.0).floor().to_float() == 2);
        CHECK(doubledouble(1.75).floor().to_float() == 1);
        CHECK(doubledouble(1.5).floor().to_float() == 1);
        CHECK(doubledouble(1.25).floor().to_float() == 1);
        CHECK(doubledouble(1.0).floor().to_float() == 1);
        CHECK(doubledouble(0.75).floor().to_float() == 0);
        CHECK(doubledouble(0.5).floor().to_float() == 0);
        CHECK(doubledouble(0.25).floor().to_float() == 0);
        CHECK(doubledouble(0).floor().to_float() == 0);
        CHECK(doubledouble(-0.25).floor().to_float() == -1);
        CHECK(doubledouble(-0.5).floor().to_float() == -1);
        CHECK(doubledouble(-0.75).floor().to_float() == -1);
        CHECK(doubledouble(-1.0).floor().to_float() == -1);
        CHECK(doubledouble(-1.25).floor().to_float() == -2);
        CHECK(doubledouble(-1.5).floor().to_float() == -2);
        CHECK(doubledouble(-1.75).floor().to_float() == -2);
        CHECK(doubledouble(-2).floor().to_float() == -2);
        CHECK(doubledouble(-2.25).floor().to_float() == -3);
        CHECK(doubledouble(-2.5).floor().to_float() == -3);
        CHECK(doubledouble(-2.75).floor().to_float() == -3);

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).floor().to_float() == (float)std::floor(x));
        }
    }

    SUBCASE("fmod") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            double denom = rand_double();
            CHECK(doubledouble(x).fmod(denom).to_float() == (float)std::fmod(x, denom));
        }
    }

    SUBCASE("trunc") {

        CHECK(doubledouble(2.75).trunc().to_float() == 2);
        CHECK(doubledouble(2.5).trunc().to_float() == 2);
        CHECK(doubledouble(2.25).trunc().to_float() == 2);
        CHECK(doubledouble(2.0).trunc().to_float() == 2);
        CHECK(doubledouble(1.75).trunc().to_float() == 1);
        CHECK(doubledouble(1.5).trunc().to_float() == 1);
        CHECK(doubledouble(1.25).trunc().to_float() == 1);
        CHECK(doubledouble(1.0).trunc().to_float() == 1);
        CHECK(doubledouble(0.75).trunc().to_float() == 0);
        CHECK(doubledouble(0.5).trunc().to_float() == 0);
        CHECK(doubledouble(0.25).trunc().to_float() == 0);
        CHECK(doubledouble(0).trunc().to_float() == 0);
        CHECK(doubledouble(-0.25).trunc().to_float() == 0);
        CHECK(doubledouble(-0.5).trunc().to_float() == 0);
        CHECK(doubledouble(-0.75).trunc().to_float() == 0);
        CHECK(doubledouble(-1.0).trunc().to_float() == -1);
        CHECK(doubledouble(-1.25).trunc().to_float() == -1);
        CHECK(doubledouble(-1.5).trunc().to_float() == -1);
        CHECK(doubledouble(-1.75).trunc().to_float() == -1);
        CHECK(doubledouble(-2).trunc().to_float() == -2);
        CHECK(doubledouble(-2.25).trunc().to_float() == -2);
        CHECK(doubledouble(-2.5).trunc().to_float() == -2);
        CHECK(doubledouble(-2.75).trunc().to_float() == -2);

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).trunc().to_float() == (float)std::trunc(x));
        }
    }

    SUBCASE("round") {

        CHECK(doubledouble(2.75).round().to_float() == 3);
        CHECK(doubledouble(2.5).round().to_float() == 3);
        CHECK(doubledouble(2.25).round().to_float() == 2);
        CHECK(doubledouble(2.0).round().to_float() == 2);
        CHECK(doubledouble(1.75).round().to_float() == 2);
        CHECK(doubledouble(1.5).round().to_float() == 2);
        CHECK(doubledouble(1.25).round().to_float() == 1);
        CHECK(doubledouble(1.0).round().to_float() == 1);
        CHECK(doubledouble(0.75).round().to_float() == 1);
        CHECK(doubledouble(0.5).round().to_float() == 1);
        CHECK(doubledouble(0.25).round().to_float() == 0);
        CHECK(doubledouble(0).round().to_float() == 0);
        CHECK(doubledouble(-0.25).round().to_float() == 0);
        CHECK(doubledouble(-0.5).round().to_float() == -1);
        CHECK(doubledouble(-0.75).round().to_float() == -1);
        CHECK(doubledouble(-1.0).round().to_float() == -1);
        CHECK(doubledouble(-1.25).round().to_float() == -1);
        CHECK(doubledouble(-1.5).round().to_float() == -2);
        CHECK(doubledouble(-1.75).round().to_float() == -2);
        CHECK(doubledouble(-2).round().to_float() == -2);
        CHECK(doubledouble(-2.25).round().to_float() == -2);
        CHECK(doubledouble(-2.5).round().to_float() == -3);
        CHECK(doubledouble(-2.75).round().to_float() == -3);

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).round().to_float() == (float)std::round(x));
        }
    }

    SUBCASE("roundEven") {

        CHECK(doubledouble(2.75).roundEven().to_float() == 3);
        CHECK(doubledouble(2.5).roundEven().to_float() == 2);
        CHECK(doubledouble(2.25).roundEven().to_float() == 2);
        CHECK(doubledouble(2.0).roundEven().to_float() == 2);
        CHECK(doubledouble(1.75).roundEven().to_float() == 2);
        CHECK(doubledouble(1.5).roundEven().to_float() == 2);
        CHECK(doubledouble(1.25).roundEven().to_float() == 1);
        CHECK(doubledouble(1.0).roundEven().to_float() == 1);
        CHECK(doubledouble(0.75).roundEven().to_float() == 1);
        CHECK(doubledouble(0.5).roundEven().to_float() == 0);
        CHECK(doubledouble(0.25).roundEven().to_float() == 0);
        CHECK(doubledouble(0).roundEven().to_float() == 0);
        CHECK(doubledouble(-0.25).roundEven().to_float() == 0);
        CHECK(doubledouble(-0.5).roundEven().to_float() == 0);
        CHECK(doubledouble(-0.75).roundEven().to_float() == -1);
        CHECK(doubledouble(-1.0).roundEven().to_float() == -1);
        CHECK(doubledouble(-1.25).roundEven().to_float() == -1);
        CHECK(doubledouble(-1.5).roundEven().to_float() == -2);
        CHECK(doubledouble(-1.75).roundEven().to_float() == -2);
        CHECK(doubledouble(-2).roundEven().to_float() == -2);
        CHECK(doubledouble(-2.25).roundEven().to_float() == -2);
        CHECK(doubledouble(-2.5).roundEven().to_float() == -2);
        CHECK(doubledouble(-2.75).roundEven().to_float() == -3);
    }

    SUBCASE("lround") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).lround() == std::lround(x));
        }
    }

    SUBCASE("llround") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).llround() == std::llround(x));
        }
    }

    SUBCASE("nearbyint") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).nearbyint().to_float() == (float)std::nearbyint(x));
        }
    }

    SUBCASE("rint") {

        auto mode = fegetround();

        SUBCASE("FE_DOWNWARD") {

            fesetround(FE_DOWNWARD);

            CHECK(doubledouble(3).rint().to_float() == 3);
            CHECK(doubledouble(3.25).rint().to_float() == 3);
            CHECK(doubledouble(3.5).rint().to_float() == 3);
            CHECK(doubledouble(3.75).rint().to_float() == 3);
            CHECK(doubledouble(4).rint().to_float() == 4);
            CHECK(doubledouble(4.25).rint().to_float() == 4);
            CHECK(doubledouble(4.5).rint().to_float() == 4);
            CHECK(doubledouble(4.75).rint().to_float() == 4);

            CHECK(doubledouble(-3).rint().to_float() == -3);
            CHECK(doubledouble(-3.25).rint().to_float() == -4);
            CHECK(doubledouble(-3.5).rint().to_float() == -4);
            CHECK(doubledouble(-3.75).rint().to_float() == -4);
            CHECK(doubledouble(-4).rint().to_float() == -4);
            CHECK(doubledouble(-4.25).rint().to_float() == -5);
            CHECK(doubledouble(-4.5).rint().to_float() == -5);
            CHECK(doubledouble(-4.75).rint().to_float() == -5);

            for (int i = 0; i < NUM_TESTS; i++) {

                double x = rand_double();
                CHECK(doubledouble(x).rint().to_float() == (float)std::rint(x));
            }
        }

        SUBCASE("FE_TONEAREST") {

            fesetround(FE_TONEAREST);

            CHECK(doubledouble(3).rint().to_float() == 3);
            CHECK(doubledouble(3.25).rint().to_float() == 3);
            CHECK(doubledouble(3.5).rint().to_float() == 4);
            CHECK(doubledouble(3.75).rint().to_float() == 4);
            CHECK(doubledouble(4).rint().to_float() == 4);
            CHECK(doubledouble(4.25).rint().to_float() == 4);
            CHECK(doubledouble(4.5).rint().to_float() == 4);
            CHECK(doubledouble(4.75).rint().to_float() == 5);

            CHECK(doubledouble(-3).rint().to_float() == -3);
            CHECK(doubledouble(-3.25).rint().to_float() == -3);
            CHECK(doubledouble(-3.5).rint().to_float() == -4);
            CHECK(doubledouble(-3.75).rint().to_float() == -4);
            CHECK(doubledouble(-4).rint().to_float() == -4);
            CHECK(doubledouble(-4.25).rint().to_float() == -4);
            CHECK(doubledouble(-4.5).rint().to_float() == -4);
            CHECK(doubledouble(-4.75).rint().to_float() == -5);

            for (int i = 0; i < NUM_TESTS; i++) {

                double x = rand_double();
                CHECK(doubledouble(x).rint().to_float() == (float)std::rint(x));
            }
        }

        SUBCASE("FE_TOWARDZERO") {

            fesetround(FE_TOWARDZERO);

            CHECK(doubledouble(3).rint().to_float() == 3);
            CHECK(doubledouble(3.25).rint().to_float() == 3);
            CHECK(doubledouble(3.5).rint().to_float() == 3);
            CHECK(doubledouble(3.75).rint().to_float() == 3);
            CHECK(doubledouble(4).rint().to_float() == 4);
            CHECK(doubledouble(4.25).rint().to_float() == 4);
            CHECK(doubledouble(4.5).rint().to_float() == 4);
            CHECK(doubledouble(4.75).rint().to_float() == 4);

            CHECK(doubledouble(-3).rint().to_float() == -3);
            CHECK(doubledouble(-3.25).rint().to_float() == -3);
            CHECK(doubledouble(-3.5).rint().to_float() == -3);
            CHECK(doubledouble(-3.75).rint().to_float() == -3);
            CHECK(doubledouble(-4).rint().to_float() == -4);
            CHECK(doubledouble(-4.25).rint().to_float() == -4);
            CHECK(doubledouble(-4.5).rint().to_float() == -4);
            CHECK(doubledouble(-4.75).rint().to_float() == -4);

            for (int i = 0; i < NUM_TESTS; i++) {

                double x = rand_double();
                CHECK(doubledouble(x).rint().to_float() == (float)std::rint(x));
            }
        }

        SUBCASE("FE_UPWARD") {

            fesetround(FE_UPWARD);

            CHECK(doubledouble(3).rint().to_float() == 3);
            CHECK(doubledouble(3.25).rint().to_float() == 4);
            CHECK(doubledouble(3.5).rint().to_float() == 4);
            CHECK(doubledouble(3.75).rint().to_float() == 4);
            CHECK(doubledouble(4).rint().to_float() == 4);
            CHECK(doubledouble(4.25).rint().to_float() == 5);
            CHECK(doubledouble(4.5).rint().to_float() == 5);
            CHECK(doubledouble(4.75).rint().to_float() == 5);

            CHECK(doubledouble(-3).rint().to_float() == -3);
            CHECK(doubledouble(-3.25).rint().to_float() == -3);
            CHECK(doubledouble(-3.5).rint().to_float() == -3);
            CHECK(doubledouble(-3.75).rint().to_float() == -3);
            CHECK(doubledouble(-4).rint().to_float() == -4);
            CHECK(doubledouble(-4.25).rint().to_float() == -4);
            CHECK(doubledouble(-4.5).rint().to_float() == -4);
            CHECK(doubledouble(-4.75).rint().to_float() == -4);

            for (int i = 0; i < NUM_TESTS; i++) {
                
                double x = rand_double();
                CHECK(doubledouble(x).rint().to_float() == (float)std::rint(x));
            }
        }

        fesetround(mode);
    }

    SUBCASE("lrint") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).lrint() == std::lrint(x));
        }
    }

    SUBCASE("llrint") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).llrint() == std::llrint(x));
        }
    }
}
