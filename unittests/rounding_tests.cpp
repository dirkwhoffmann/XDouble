#include "main.h"

TEST_CASE("Rounding and remainder functions") {

    srand(0);
    auto mode = fegetround();

    SUBCASE("ceil") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            {  2.75,    3.0,    3.0,    3.0,    3.0 },
            {  2.5,     3.0,    3.0,    3.0,    3.0 },
            {  2.25,    3.0,    3.0,    3.0,    3.0 },
            {  2.0,     2.0,    2.0,    2.0,    2.0 },
            {  1.75,    2.0,    2.0,    2.0,    2.0 },
            {  1.5,     2.0,    2.0,    2.0,    2.0 },
            {  1.25,    2.0,    2.0,    2.0,    2.0 },
            {  1.0,     1.0,    1.0,    1.0,    1.0 },
            {  0.75,    1.0,    1.0,    1.0,    1.0 },
            {  0.5,     1.0,    1.0,    1.0,    1.0 },
            {  0.25,    1.0,    1.0,    1.0,    1.0 },
            {  0,       0.0,    0.0,    0.0,    0.0 },
            { -0.25,   -0.0,   -0.0,   -0.0,   -0.0 },
            { -0.5,    -0.0,   -0.0,   -0.0,   -0.0 },
            { -0.75,   -0.0,   -0.0,   -0.0,   -0.0 },
            { -1.0,    -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.25,   -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.5,    -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.75,   -1.0,   -1.0,   -1.0,   -1.0 },
            { -2,      -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.25,   -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.5,    -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.75,   -2.0,   -2.0,   -2.0,   -2.0 },

            { 999,      0.0,    0.0,    0.0,    0.0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            COMPARE ((float)doubledouble(p[i].v).ceil(), p[i].down);
            fesetround(FE_TONEAREST);
            COMPARE ((float)doubledouble(p[i].v).ceil(), p[i].round);
            fesetround(FE_TOWARDZERO);
            COMPARE ((float)doubledouble(p[i].v).ceil(), p[i].zero);
            fesetround(FE_UPWARD);
            COMPARE ((float)doubledouble(p[i].v).ceil(), p[i].up);
        }

        doubledouble pi("3.14159265358979323846264338327950");

        CHECK (pi.ceil(1).to_float() - (float)3.2 < 1e-10);
        CHECK (pi.ceil(2).to_float() - (float)3.15 < 1e-10);
        CHECK (pi.ceil(3).to_float() - (float)3.142 < 1e-10);
        CHECK (pi.ceil(4).to_float() - (float)3.1416 < 1e-10);
        CHECK (pi.ceil(5).to_float() - (float)3.14160 < 1e-10);

        CHECK ((-pi).ceil(1).to_float() - (float)-3.1 < 1e-10);
        CHECK ((-pi).ceil(2).to_float() - (float)-3.14 < 1e-10);
        CHECK ((-pi).ceil(3).to_float() - (float)-3.141 < 1e-10);
        CHECK ((-pi).ceil(4).to_float() - (float)-3.1415 < 1e-10);
        CHECK ((-pi).ceil(5).to_float() - (float)-3.14159 < 1e-10);

        CHECK (doubledouble::posnan().ceil().isnan() == std::isnan(std::ceil(posnan)));
        CHECK (doubledouble::negnan().ceil().isnan() == std::isnan(std::ceil(negnan)));
        CHECK (doubledouble::posinf().ceil().isinf() == std::isinf(std::ceil(posinf)));
        CHECK (doubledouble::neginf().ceil().isinf() == std::isinf(std::ceil(neginf)));
    }

    SUBCASE("floor") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            {  2.75,    2.0,    2.0,    2.0,    2.0 },
            {  2.5,     2.0,    2.0,    2.0,    2.0 },
            {  2.25,    2.0,    2.0,    2.0,    2.0 },
            {  2.0,     2.0,    2.0,    2.0,    2.0 },
            {  1.75,    1.0,    1.0,    1.0,    1.0 },
            {  1.5,     1.0,    1.0,    1.0,    1.0 },
            {  1.25,    1.0,    1.0,    1.0,    1.0 },
            {  1.0,     1.0,    1.0,    1.0,    1.0 },
            {  0.75,    0.0,    0.0,    0.0,    0.0 },
            {  0.5,     0.0,    0.0,    0.0,    0.0 },
            {  0.25,    0.0,    0.0,    0.0,    0.0 },
            {  0,       0.0,    0.0,    0.0,    0.0 },
            { -0.25,   -1.0,   -1.0,   -1.0,   -1.0 },
            { -0.5,    -1.0,   -1.0,   -1.0,   -1.0 },
            { -0.75,   -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.0,    -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.25,   -2.0,   -2.0,   -2.0,   -2.0 },
            { -1.5,    -2.0,   -2.0,   -2.0,   -2.0 },
            { -1.75,   -2.0,   -2.0,   -2.0,   -2.0 },
            { -2,      -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.25,   -3.0,   -3.0,   -3.0,   -3.0 },
            { -2.5,    -3.0,   -3.0,   -3.0,   -3.0 },
            { -2.75,   -3.0,   -3.0,   -3.0,   -3.0 },

            { 999,      0.0,    0.0,    0.0,    0.0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            COMPARE ((float)doubledouble(p[i].v).floor(), p[i].down);
            fesetround(FE_TONEAREST);
            COMPARE ((float)doubledouble(p[i].v).floor(), p[i].round);
            fesetround(FE_TOWARDZERO);
            COMPARE ((float)doubledouble(p[i].v).floor(), p[i].zero);
            fesetround(FE_UPWARD);
            COMPARE ((float)doubledouble(p[i].v).floor(), p[i].up);
        }

        doubledouble pi("3.14159265358979323846264338327950");

        COMPARE (pi.floor(1).to_float(), (float)3.1);
        COMPARE (pi.floor(2).to_float(), (float)3.14);
        COMPARE (pi.floor(3).to_float(), (float)3.141);
        COMPARE (pi.floor(4).to_float(), (float)3.1415);
        COMPARE (pi.floor(5).to_float(), (float)3.14159);

        COMPARE ((-pi).floor(1).to_float(), (float)-3.2);
        COMPARE ((-pi).floor(2).to_float(), (float)-3.15);
        COMPARE ((-pi).floor(3).to_float(), (float)-3.142);
        COMPARE ((-pi).floor(4).to_float(), (float)-3.1416);
        COMPARE ((-pi).floor(5).to_float(), (float)-3.1416);

        COMPARE (doubledouble::posnan().floor().isnan(), std::isnan(std::floor(posnan)));
        COMPARE (doubledouble::posinf().floor().isinf(), std::isinf(std::floor(posinf)));
        COMPARE (doubledouble::neginf().floor().isinf(), std::isinf(std::floor(neginf)));
    }

    SUBCASE("fmod") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                double x = rand_double();
                double denom = rand_double();
                auto result = doubledouble(x).fmod(denom);

                COMPARE (result.to_float(), (float)std::fmod(x, denom));
            }
        }

        SUBCASE("Special cases") {

            COMPARE (doubledouble(2.0).fmod(0.0), std::fmod(2.0, 0.0));
            COMPARE (doubledouble::nan().fmod(0.0), std::fmod(posnan, 0.0));
            COMPARE (doubledouble::inf().fmod(0.0), std::fmod(posinf, 0.0));

            COMPARE (doubledouble(2.0).fmod(doubledouble::nan()), std::fmod(2.0, posnan));
            COMPARE (doubledouble::nan().fmod(2.0), std::fmod(posnan, 2.0));
            COMPARE (doubledouble::nan().fmod(doubledouble::nan()), std::fmod(posnan, posnan));
            COMPARE (doubledouble::nan().fmod(doubledouble::inf()), std::fmod(posnan, posinf));
            COMPARE (doubledouble::inf().fmod(doubledouble::nan()), std::fmod(posinf, posnan));

            COMPARE (doubledouble(2.0).fmod(doubledouble::inf()), std::fmod(2.0, posinf));
            COMPARE (doubledouble(4.1).fmod(doubledouble::inf()), std::fmod(4.1, posinf));
            COMPARE (doubledouble::inf().fmod(2.0), std::fmod(posinf, 2.0));
            COMPARE (doubledouble::inf().fmod(doubledouble::inf()), std::fmod(posinf, posinf));
        }
    }

    SUBCASE("trunc") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            {  2.75,    2.0,    2.0,    2.0,    2.0 },
            {  2.5,     2.0,    2.0,    2.0,    2.0 },
            {  2.25,    2.0,    2.0,    2.0,    2.0 },
            {  2.0,     2.0,    2.0,    2.0,    2.0 },
            {  1.75,    1.0,    1.0,    1.0,    1.0 },
            {  1.5,     1.0,    1.0,    1.0,    1.0 },
            {  1.25,    1.0,    1.0,    1.0,    1.0 },
            {  1.0,     1.0,    1.0,    1.0,    1.0 },
            {  0.75,    0.0,    0.0,    0.0,    0.0 },
            {  0.5,     0.0,    0.0,    0.0,    0.0 },
            {  0.25,    0.0,    0.0,    0.0,    0.0 },
            {  0,       0.0,    0.0,    0.0,    0.0 },
            { -0.25,   -0.0,   -0.0,   -0.0,   -0.0 },
            { -0.5,    -0.0,   -0.0,   -0.0,   -0.0 },
            { -0.75,   -0.0,   -0.0,   -0.0,   -0.0 },
            { -1.0,    -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.25,   -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.5,    -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.75,   -1.0,   -1.0,   -1.0,   -1.0 },
            { -2,      -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.25,   -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.5,    -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.75,   -2.0,   -2.0,   -2.0,   -2.0 },

            { 999,      0.0,    0.0,    0.0,    0.0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            COMPARE ((float)doubledouble(p[i].v).trunc(), p[i].down);
            fesetround(FE_TONEAREST);
            COMPARE ((float)doubledouble(p[i].v).trunc(), p[i].round);
            fesetround(FE_TOWARDZERO);
            COMPARE ((float)doubledouble(p[i].v).trunc(), p[i].zero);
            fesetround(FE_UPWARD);
            COMPARE ((float)doubledouble(p[i].v).trunc(), p[i].up);
        }

        doubledouble pi("3.14159265358979323846264338327950");

        COMPARE (pi.trunc(1).to_float(), (float)3.1);
        COMPARE (pi.trunc(2).to_float(), (float)3.14);
        COMPARE (pi.trunc(3).to_float(), (float)3.141);
        COMPARE (pi.trunc(4).to_float(), (float)3.1415);
        COMPARE (pi.trunc(5).to_float(), (float)3.14159);

        COMPARE ((-pi).trunc(1).to_float(), (float)-3.1);
        COMPARE ((-pi).trunc(2).to_float(), (float)-3.14);
        COMPARE ((-pi).trunc(3).to_float(), (float)-3.141);
        COMPARE ((-pi).trunc(4).to_float(), (float)-3.1415);
        COMPARE ((-pi).trunc(5).to_float(), (float)-3.14159);

        COMPARE (doubledouble::posnan().trunc().isnan(), std::isnan(std::trunc(posnan)));
        COMPARE (doubledouble::posinf().trunc().isinf(), std::isinf(std::trunc(posinf)));
        COMPARE (doubledouble::neginf().trunc().isinf(), std::isinf(std::trunc(neginf)));
    }

    SUBCASE("round") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            {  2.75,    3.0,    3.0,    3.0,    3.0 },
            {  2.5,     3.0,    3.0,    3.0,    3.0 },
            {  2.25,    2.0,    2.0,    2.0,    2.0 },
            {  2.0,     2.0,    2.0,    2.0,    2.0 },
            {  1.75,    2.0,    2.0,    2.0,    2.0 },
            {  1.5,     2.0,    2.0,    2.0,    2.0 },
            {  1.25,    1.0,    1.0,    1.0,    1.0 },
            {  1.0,     1.0,    1.0,    1.0,    1.0 },
            {  0.75,    1.0,    1.0,    1.0,    1.0 },
            {  0.5,     1.0,    1.0,    1.0,    1.0 },
            {  0.25,    0.0,    0.0,    0.0,    0.0 },
            {  0,       0.0,    0.0,    0.0,    0.0 },
            { -0.25,   -0.0,   -0.0,   -0.0,   -0.0 },
            { -0.5,    -1.0,   -1.0,   -1.0,   -1.0 },
            { -0.75,   -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.0,    -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.25,   -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.5,    -2.0,   -2.0,   -2.0,   -2.0 },
            { -1.75,   -2.0,   -2.0,   -2.0,   -2.0 },
            { -2,      -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.25,   -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.5,    -3.0,   -3.0,   -3.0,   -3.0 },
            { -2.75,   -3.0,   -3.0,   -3.0,   -3.0 },

            { 999,      0.0,    0.0,    0.0,    0.0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            COMPARE ((float)doubledouble(p[i].v).round(), p[i].down);
            fesetround(FE_TONEAREST);
            COMPARE ((float)doubledouble(p[i].v).round(), p[i].round);
            fesetround(FE_TOWARDZERO);
            COMPARE ((float)doubledouble(p[i].v).round(), p[i].zero);
            fesetround(FE_UPWARD);
            COMPARE ((float)doubledouble(p[i].v).round(), p[i].up);
        }

        doubledouble pi("3.14159265358979323846264338327950");

        COMPARE (pi.round(1).to_float(), (float)3.1);
        COMPARE (pi.round(2).to_float(), (float)3.14);
        COMPARE (pi.round(3).to_float(), (float)3.142);
        COMPARE (pi.round(4).to_float(), (float)3.1416);
        COMPARE (pi.round(5).to_float(), (float)3.14159);

        COMPARE ((-pi).round(1).to_float(), (float)-3.1);
        COMPARE ((-pi).round(2).to_float(), (float)-3.14);
        COMPARE ((-pi).round(3).to_float(), (float)-3.142);
        COMPARE ((-pi).round(4).to_float(), (float)-3.1416);
        COMPARE ((-pi).round(5).to_float(), (float)-3.14159);

        COMPARE (doubledouble::posnan().round().isnan(), std::isnan(std::round(posnan)));
        COMPARE (doubledouble::posinf().round().isinf(), std::isinf(std::round(posinf)));
        COMPARE (doubledouble::neginf().round().isinf(), std::isinf(std::round(neginf)));
    }

    SUBCASE("roundEven") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            {  2.75,    3.0,    3.0,    3.0,    3.0 },
            {  2.5,     2.0,    2.0,    2.0,    2.0 },
            {  2.25,    2.0,    2.0,    2.0,    2.0 },
            {  2.0,     2.0,    2.0,    2.0,    2.0 },
            {  1.75,    2.0,    2.0,    2.0,    2.0 },
            {  1.5,     2.0,    2.0,    2.0,    2.0 },
            {  1.25,    1.0,    1.0,    1.0,    1.0 },
            {  1.0,     1.0,    1.0,    1.0,    1.0 },
            {  0.75,    1.0,    1.0,    1.0,    1.0 },
            {  0.5,     0.0,    0.0,    0.0,    0.0 },
            {  0.25,    0.0,    0.0,    0.0,    0.0 },
            {  0.0,     0.0,    0.0,    0.0,    0.0 },
            { -0.25,   -0.0,   -0.0,   -0.0,   -0.0 },
            { -0.5,    -0.0,   -0.0,   -0.0,   -0.0 },
            { -0.75,   -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.0,    -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.25,   -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.5,    -2.0,   -2.0,   -2.0,   -2.0 },
            { -1.75,   -2.0,   -2.0,   -2.0,   -2.0 },
            { -2,      -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.25,   -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.5,    -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.75,   -3.0,   -3.0,   -3.0,   -3.0 },

            { 999,      0.0,    0.0,    0.0,    0.0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            COMPARE ((float)doubledouble(p[i].v).roundEven(), p[i].down);
            fesetround(FE_TONEAREST);
            COMPARE ((float)doubledouble(p[i].v).roundEven(), p[i].round);
            fesetround(FE_TOWARDZERO);
            COMPARE ((float)doubledouble(p[i].v).roundEven(), p[i].zero);
            fesetround(FE_UPWARD);
            COMPARE ((float)doubledouble(p[i].v).roundEven(), p[i].up);
        }

        COMPARE (doubledouble::posnan().roundEven().isnan(), std::isnan(std::round(posnan)));
        COMPARE (doubledouble::posinf().roundEven().isinf(), std::isinf(std::round(posinf)));
        COMPARE (doubledouble::neginf().roundEven().isinf(), std::isinf(std::round(neginf)));
    }

    SUBCASE("lround") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            COMPARE (doubledouble(x).lround(), std::lround(x));
        }

        CHECK (doubledouble::posnan().lround() == std::lround(posnan));
        CHECK (doubledouble::negnan().lround() == std::lround(negnan));
        CHECK (doubledouble::posinf().lround() == std::lround(posinf));
        CHECK (doubledouble::neginf().lround() == std::lround(neginf));
    }

    SUBCASE("llround") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            COMPARE (doubledouble(x).llround(), std::llround(x));
        }

        CHECK (doubledouble::posnan().llround() == std::llround(posnan));
        CHECK (doubledouble::negnan().llround() == std::llround(negnan));
        CHECK (doubledouble::posinf().llround() == std::llround(posinf));
        CHECK (doubledouble::neginf().llround() == std::llround(neginf));
    }

    SUBCASE("rint") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            {  2.75,    2.0,    3.0,    2.0,    3.0 },
            {  2.5,     2.0,    2.0,    2.0,    3.0 },
            {  2.25,    2.0,    2.0,    2.0,    3.0 },
            {  2.0,     2.0,    2.0,    2.0,    2.0 },
            {  1.75,    1.0,    2.0,    1.0,    2.0 },
            {  1.5,     1.0,    2.0,    1.0,    2.0 },
            {  1.25,    1.0,    1.0,    1.0,    2.0 },
            {  1.0,     1.0,    1.0,    1.0,    1.0 },
            {  0.75,    0.0,    1.0,    0.0,    1.0 },
            {  0.5,     0.0,    0.0,    0.0,    1.0 },
            {  0.25,    0.0,    0.0,    0.0,    1.0 },
            {  0,       0.0,    0.0,    0.0,    0.0 },
            { -0.25,   -1.0,   -0.0,   -0.0,   -0.0 },
            { -0.5,    -1.0,   -0.0,   -0.0,   -0.0 },
            { -0.75,   -1.0,   -1.0,   -0.0,   -0.0 },
            { -1.0,    -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.25,   -2.0,   -1.0,   -1.0,   -1.0 },
            { -1.5,    -2.0,   -2.0,   -1.0,   -1.0 },
            { -1.75,   -2.0,   -2.0,   -1.0,   -1.0 },
            { -2,      -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.25,   -3.0,   -2.0,   -2.0,   -2.0 },
            { -2.5,    -3.0,   -2.0,   -2.0,   -2.0 },
            { -2.75,   -3.0,   -3.0,   -2.0,   -2.0 },

            { 999,      0.0,    0.0,    0.0,    0.0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            COMPARE ((float)doubledouble(p[i].v).rint(), p[i].down);
            fesetround(FE_TONEAREST);
            COMPARE ((float)doubledouble(p[i].v).rint(), p[i].round);
            fesetround(FE_TOWARDZERO);
            COMPARE ((float)doubledouble(p[i].v).rint(), p[i].zero);
            fesetround(FE_UPWARD);
            COMPARE ((float)doubledouble(p[i].v).rint(), p[i].up);
        }

        doubledouble pi("3.14159265358979323846264338327950");

        struct { int digits; double down; double round; double zero; double up; } r[] = {

            { 1,    3.1,        3.1,        3.1,        3.2     },
            { 2,    3.14,       3.14,       3.14,       3.15    },
            { 3,    3.141,      3.142,      3.141,      3.142   },
            { 4,    3.1415,     3.1416,     3.1415,     3.1416  },
            { 5,    3.14159,    3.14159,    3.14159,    3.14160 },

            { 999,  0,          0,          0,          0       }
        };

        for (int i = 0; r[i].digits != 999; i++) {

            fesetround(FE_DOWNWARD);
            CHECK (std::abs(doubledouble(pi).rint(r[i].digits).to_double() - r[i].down) < 1e-10);
            fesetround(FE_TONEAREST);
            CHECK (std::abs(doubledouble(pi).rint(r[i].digits).to_double() - r[i].round) < 1e-10);
            fesetround(FE_TOWARDZERO);
            CHECK (std::abs(doubledouble(pi).rint(r[i].digits).to_double() - r[i].zero) < 1e-10);
            fesetround(FE_UPWARD);
            CHECK (std::abs(doubledouble(pi).rint(r[i].digits).to_double() - r[i].up) < 1e-10);
        }

        COMPARE (doubledouble::posnan().rint(), std::rint(posnan));
        COMPARE (doubledouble::negnan().rint(), std::rint(negnan));
        COMPARE (doubledouble::posinf().rint(), std::rint(posinf));
        COMPARE (doubledouble::neginf().rint(), std::rint(neginf));
    }

    SUBCASE("lrint") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).lrint() == std::lrint(x));
        }

        CHECK(doubledouble::posnan().lrint() == std::lrint(posnan));
        CHECK(doubledouble::negnan().lrint() == std::lrint(negnan));
        CHECK(doubledouble::posinf().lrint() == std::lrint(posinf));
        CHECK(doubledouble::neginf().lrint() == std::lrint(neginf));
    }

    SUBCASE("llrint") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).llrint() == std::llrint(x));
        }

        CHECK(doubledouble::posnan().llrint() == std::llrint(posnan));
        CHECK(doubledouble::negnan().llrint() == std::llrint(negnan));
        CHECK(doubledouble::posinf().llrint() == std::llrint(posinf));
        CHECK(doubledouble::neginf().llrint() == std::llrint(neginf));
    }

    SUBCASE("nearbyint") {

        struct { double v; float down; float round; float zero; float up; } p[] = {

            {  2.75,    2.0,    3.0,    2.0,    3.0 },
            {  2.5,     2.0,    2.0,    2.0,    3.0 },
            {  2.25,    2.0,    2.0,    2.0,    3.0 },
            {  2.0,     2.0,    2.0,    2.0,    2.0 },
            {  1.75,    1.0,    2.0,    1.0,    2.0 },
            {  1.5,     1.0,    2.0,    1.0,    2.0 },
            {  1.25,    1.0,    1.0,    1.0,    2.0 },
            {  1.0,     1.0,    1.0,    1.0,    1.0 },
            {  0.75,    0.0,    1.0,    0.0,    1.0 },
            {  0.5,     0.0,    0.0,    0.0,    1.0 },
            {  0.25,    0.0,    0.0,    0.0,    1.0 },
            {  0,       0.0,    0.0,    0.0,    0.0 },
            { -0.25,   -1.0,   -0.0,   -0.0,   -0.0 },
            { -0.5,    -1.0,   -0.0,   -0.0,   -0.0 },
            { -0.75,   -1.0,   -1.0,   -0.0,   -0.0 },
            { -1.0,    -1.0,   -1.0,   -1.0,   -1.0 },
            { -1.25,   -2.0,   -1.0,   -1.0,   -1.0 },
            { -1.5,    -2.0,   -2.0,   -1.0,   -1.0 },
            { -1.75,   -2.0,   -2.0,   -1.0,   -1.0 },
            { -2,      -2.0,   -2.0,   -2.0,   -2.0 },
            { -2.25,   -3.0,   -2.0,   -2.0,   -2.0 },
            { -2.5,    -3.0,   -2.0,   -2.0,   -2.0 },
            { -2.75,   -3.0,   -3.0,   -2.0,   -2.0 },

            { 999,      0.0,    0.0,    0.0,    0.0 }
        };

        for (int i = 0; p[i].v != 999; i++) {

            fesetround(FE_DOWNWARD);
            COMPARE ((float)doubledouble(p[i].v).nearbyint(), p[i].down);
            fesetround(FE_TONEAREST);
            COMPARE ((float)doubledouble(p[i].v).nearbyint(), p[i].round);
            fesetround(FE_TOWARDZERO);
            COMPARE ((float)doubledouble(p[i].v).nearbyint(), p[i].zero);
            fesetround(FE_UPWARD);
            COMPARE ((float)doubledouble(p[i].v).nearbyint(), p[i].up);
        }

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            COMPARE (doubledouble(x).nearbyint().to_float(), (float)std::nearbyint(x));
        }

        COMPARE (doubledouble::posnan().nearbyint(), std::nearbyint(posnan));
        COMPARE (doubledouble::negnan().nearbyint(), std::nearbyint(negnan));
        COMPARE (doubledouble::posinf().nearbyint(), std::nearbyint(posinf));
        COMPARE (doubledouble::neginf().nearbyint(), std::nearbyint(neginf));
    }

    fesetround(mode);
}
