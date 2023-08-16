#include "main.h"

TEST_CASE("Rounding and remainder functions") {

#pragma STDC FENV_ACCESS ON

    srand(0);
    auto mode = fegetround();

    SUBCASE("ceil") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            { 2.75,     3,      3,      3,      3 },
            { 2.5,      3,      3,      3,      3 },
            { 2.25,     3,      3,      3,      3 },
            { 2.0,      2,      2,      2,      2 },
            { 1.75,     2,      2,      2,      2 },
            { 1.5,      2,      2,      2,      2 },
            { 1.25,     2,      2,      2,      2 },
            { 1.0,      1,      1,      1,      1 },
            { 0.75,     1,      1,      1,      1 },
            { 0.5,      1,      1,      1,      1 },
            { 0.25,     1,      1,      1,      1 },
            { 0,        0,      0,      0,      0 },
            { -0.25,    0,      0,      0,      0 },
            { -0.5,     0,      0,      0,      0 },
            { -0.75,    0,      0,      0,      0 },
            { -1.0,    -1,     -1,     -1,     -1 },
            { -1.25,   -1,     -1,     -1,     -1 },
            { -1.5,    -1,     -1,     -1,     -1 },
            { -1.75,   -1,     -1,     -1,     -1 },
            { -2,      -2,     -2,     -2,     -2 },
            { -2.25,   -2,     -2,     -2,     -2 },
            { -2.5,    -2,     -2,     -2,     -2 },
            { -2.75,   -2,     -2,     -2,     -2 },

            { 999,      0,      0,      0,      0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            CHECK(doubledouble(p[i].v).ceil() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK(doubledouble(p[i].v).ceil() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK(doubledouble(p[i].v).ceil() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK(doubledouble(p[i].v).ceil() == p[i].up);
        }
    }

    SUBCASE("floor") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            { 2.75,     2,      2,      2,      2 },
            { 2.5,      2,      2,      2,      2 },
            { 2.25,     2,      2,      2,      2 },
            { 2.0,      2,      2,      2,      2 },
            { 1.75,     1,      1,      1,      1 },
            { 1.5,      1,      1,      1,      1 },
            { 1.25,     1,      1,      1,      1 },
            { 1.0,      1,      1,      1,      1 },
            { 0.75,     0,      0,      0,      0 },
            { 0.5,      0,      0,      0,      0 },
            { 0.25,     0,      0,      0,      0 },
            { 0,        0,      0,      0,      0 },
            { -0.25,   -1,     -1,     -1,     -1 },
            { -0.5,    -1,     -1,     -1,     -1 },
            { -0.75,   -1,     -1,     -1,     -1 },
            { -1.0,    -1,     -1,     -1,     -1 },
            { -1.25,   -2,     -2,     -2,     -2 },
            { -1.5,    -2,     -2,     -2,     -2 },
            { -1.75,   -2,     -2,     -2,     -2 },
            { -2,      -2,     -2,     -2,     -2 },
            { -2.25,   -3,     -3,     -3,     -3 },
            { -2.5,    -3,     -3,     -3,     -3 },
            { -2.75,   -3,     -3,     -3,     -3 },

            { 999,      0,      0,      0,      0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            CHECK(doubledouble(p[i].v).floor() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK(doubledouble(p[i].v).floor() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK(doubledouble(p[i].v).floor() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK(doubledouble(p[i].v).floor() == p[i].up);
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

        struct { double v; float down; float round; float zero; float up; } p[] = {

            { 2.75,     2,      2,      2,      2 },
            { 2.5,      2,      2,      2,      2 },
            { 2.25,     2,      2,      2,      2 },
            { 2.0,      2,      2,      2,      2 },
            { 1.75,     1,      1,      1,      1 },
            { 1.5,      1,      1,      1,      1 },
            { 1.25,     1,      1,      1,      1 },
            { 1.0,      1,      1,      1,      1 },
            { 0.75,     0,      0,      0,      0 },
            { 0.5,      0,      0,      0,      0 },
            { 0.25,     0,      0,      0,      0 },
            { 0,        0,      0,      0,      0 },
            { -0.25,    0,      0,      0,      0 },
            { -0.5,     0,      0,      0,      0 },
            { -0.75,    0,      0,      0,      0 },
            { -1.0,    -1,     -1,     -1,     -1 },
            { -1.25,   -1,     -1,     -1,     -1 },
            { -1.5,    -1,     -1,     -1,     -1 },
            { -1.75,   -1,     -1,     -1,     -1 },
            { -2,      -2,     -2,     -2,     -2 },
            { -2.25,   -2,     -2,     -2,     -2 },
            { -2.5,    -2,     -2,     -2,     -2 },
            { -2.75,   -2,     -2,     -2,     -2 },

            { 999,      0,      0,      0,      0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            CHECK(doubledouble(p[i].v).trunc() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK(doubledouble(p[i].v).trunc() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK(doubledouble(p[i].v).trunc() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK(doubledouble(p[i].v).trunc() == p[i].up);
        }
    }

    SUBCASE("round") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            { 2.75,     3,      3,      3,      3 },
            { 2.5,      3,      3,      3,      3 },
            { 2.25,     2,      2,      2,      2 },
            { 2.0,      2,      2,      2,      2 },
            { 1.75,     2,      2,      2,      2 },
            { 1.5,      2,      2,      2,      2 },
            { 1.25,     1,      1,      1,      1 },
            { 1.0,      1,      1,      1,      1 },
            { 0.75,     1,      1,      1,      1 },
            { 0.5,      1,      1,      1,      1 },
            { 0.25,     0,      0,      0,      0 },
            { 0,        0,      0,      0,      0 },
            { -0.25,    0,      0,      0,      0 },
            { -0.5,    -1,     -1,     -1,     -1 },
            { -0.75,   -1,     -1,     -1,     -1 },
            { -1.0,    -1,     -1,     -1,     -1 },
            { -1.25,   -1,     -1,     -1,     -1 },
            { -1.5,    -2,     -2,     -2,     -2 },
            { -1.75,   -2,     -2,     -2,     -2 },
            { -2,      -2,     -2,     -2,     -2 },
            { -2.25,   -2,     -2,     -2,     -2 },
            { -2.5,    -3,     -3,     -3,     -3 },
            { -2.75,   -3,     -3,     -3,     -3 },

            { 999,      0,      0,      0,      0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            CHECK(doubledouble(p[i].v).round() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK(doubledouble(p[i].v).round() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK(doubledouble(p[i].v).round() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK(doubledouble(p[i].v).round() == p[i].up);
        }
    }

    SUBCASE("roundEven") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            { 2.75,     3,      3,      3,      3 },
            { 2.5,      2,      2,      2,      2 },
            { 2.25,     2,      2,      2,      2 },
            { 2.0,      2,      2,      2,      2 },
            { 1.75,     2,      2,      2,      2 },
            { 1.5,      2,      2,      2,      2 },
            { 1.25,     1,      1,      1,      1 },
            { 1.0,      1,      1,      1,      1 },
            { 0.75,     1,      1,      1,      1 },
            { 0.5,      0,      0,      0,      0 },
            { 0.25,     0,      0,      0,      0 },
            { 0,        0,      0,      0,      0 },
            { -0.25,    0,      0,      0,      0 },
            { -0.5,     0,      0,      0,      0 },
            { -0.75,   -1,     -1,     -1,     -1 },
            { -1.0,    -1,     -1,     -1,     -1 },
            { -1.25,   -1,     -1,     -1,     -1 },
            { -1.5,    -2,     -2,     -2,     -2 },
            { -1.75,   -2,     -2,     -2,     -2 },
            { -2,      -2,     -2,     -2,     -2 },
            { -2.25,   -2,     -2,     -2,     -2 },
            { -2.5,    -2,     -2,     -2,     -2 },
            { -2.75,   -3,     -3,     -3,     -3 },

            { 999,      0,      0,      0,      0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            CHECK(doubledouble(p[i].v).roundEven() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK(doubledouble(p[i].v).roundEven() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK(doubledouble(p[i].v).roundEven() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK(doubledouble(p[i].v).roundEven() == p[i].up);
        }
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

    SUBCASE("rint") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            { 2.75,     2,      3,      2,      3 },
            { 2.5,      2,      2,      2,      3 },
            { 2.25,     2,      2,      2,      3 },
            { 2.0,      2,      2,      2,      2 },
            { 1.75,     1,      2,      1,      2 },
            { 1.5,      1,      2,      1,      2 },
            { 1.25,     1,      1,      1,      2 },
            { 1.0,      1,      1,      1,      1 },
            { 0.75,     0,      1,      0,      1 },
            { 0.5,      0,      0,      0,      1 },
            { 0.25,     0,      0,      0,      1 },
            { 0,        0,      0,      0,      0 },
            { -0.25,   -1,      0,      0,      0 },
            { -0.5,    -1,      0,      0,      0 },
            { -0.75,   -1,     -1,      0,      0 },
            { -1.0,    -1,     -1,     -1,     -1 },
            { -1.25,   -2,     -1,     -1,     -1 },
            { -1.5,    -2,     -2,     -1,     -1 },
            { -1.75,   -2,     -2,     -1,     -1 },
            { -2,      -2,     -2,     -2,     -2 },
            { -2.25,   -3,     -2,     -2,     -2 },
            { -2.5,    -3,     -2,     -2,     -2 },
            { -2.75,   -3,     -3,     -2,     -2 },

            { 999,      0,      0,      0,      0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            CHECK(doubledouble(p[i].v).rint() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK(doubledouble(p[i].v).rint() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK(doubledouble(p[i].v).rint() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK(doubledouble(p[i].v).rint() == p[i].up);
        }
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

    SUBCASE("nearbyint") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            { 2.75,     2,      3,      2,      3 },
            { 2.5,      2,      2,      2,      3 },
            { 2.25,     2,      2,      2,      3 },
            { 2.0,      2,      2,      2,      2 },
            { 1.75,     1,      2,      1,      2 },
            { 1.5,      1,      2,      1,      2 },
            { 1.25,     1,      1,      1,      2 },
            { 1.0,      1,      1,      1,      1 },
            { 0.75,     0,      1,      0,      1 },
            { 0.5,      0,      0,      0,      1 },
            { 0.25,     0,      0,      0,      1 },
            { 0,        0,      0,      0,      0 },
            { -0.25,   -1,      0,      0,      0 },
            { -0.5,    -1,      0,      0,      0 },
            { -0.75,   -1,     -1,      0,      0 },
            { -1.0,    -1,     -1,     -1,     -1 },
            { -1.25,   -2,     -1,     -1,     -1 },
            { -1.5,    -2,     -2,     -1,     -1 },
            { -1.75,   -2,     -2,     -1,     -1 },
            { -2,      -2,     -2,     -2,     -2 },
            { -2.25,   -3,     -2,     -2,     -2 },
            { -2.5,    -3,     -2,     -2,     -2 },
            { -2.75,   -3,     -3,     -2,     -2 },

            { 999,      0,      0,      0,      0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            CHECK(doubledouble(p[i].v).nearbyint() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK(doubledouble(p[i].v).nearbyint() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK(doubledouble(p[i].v).nearbyint() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK(doubledouble(p[i].v).nearbyint() == p[i].up);
        }

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).nearbyint().to_float() == (float)std::nearbyint(x));
        }
    }

    fesetround(mode);
}
