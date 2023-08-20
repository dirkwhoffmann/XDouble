#include "main.h"

TEST_CASE("Rounding and remainder functions") {

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
            CHECK((float)doubledouble(p[i].v).ceil() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK((float)doubledouble(p[i].v).ceil() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK((float)doubledouble(p[i].v).ceil() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK((float)doubledouble(p[i].v).ceil() == p[i].up);
        }

        doubledouble pi("3.14159265358979323846264338327950");

        CHECK(pi.ceil(1).to_float() == (float)3.2);
        CHECK(pi.ceil(2).to_float() == (float)3.15);
        CHECK(pi.ceil(3).to_float() == (float)3.142);
        CHECK(pi.ceil(4).to_float() == (float)3.1416);
        CHECK(pi.ceil(5).to_float() == (float)3.14160);

        CHECK((-pi).ceil(1).to_float() == (float)-3.1);
        CHECK((-pi).ceil(2).to_float() == (float)-3.14);
        CHECK((-pi).ceil(3).to_float() == (float)-3.141);
        CHECK((-pi).ceil(4).to_float() == (float)-3.1415);
        CHECK((-pi).ceil(5).to_float() == (float)-3.14159);

        CHECK(doubledouble::nan().ceil().isnan() == std::isnan(std::ceil(std::numeric_limits<double>::quiet_NaN())));
        CHECK(doubledouble::inf().ceil().isinf() == std::isinf(std::ceil(std::numeric_limits<double>::infinity())));
        CHECK((-doubledouble::inf()).ceil().isinf() == std::isinf(std::ceil(-std::numeric_limits<double>::infinity())));
        CHECK(doubledouble::inf().ceil().signbit() == std::signbit(std::ceil(std::numeric_limits<double>::infinity())));
        CHECK((-doubledouble::inf()).ceil().signbit() == std::signbit(std::ceil(-std::numeric_limits<double>::infinity())));
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
            CHECK((float)doubledouble(p[i].v).floor() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK((float)doubledouble(p[i].v).floor() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK((float)doubledouble(p[i].v).floor() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK((float)doubledouble(p[i].v).floor() == p[i].up);
        }

        doubledouble pi("3.14159265358979323846264338327950");

        CHECK(pi.floor(1).to_float() == (float)3.1);
        CHECK(pi.floor(2).to_float() == (float)3.14);
        CHECK(pi.floor(3).to_float() == (float)3.141);
        CHECK(pi.floor(4).to_float() == (float)3.1415);
        CHECK(pi.floor(5).to_float() == (float)3.14159);

        CHECK((-pi).floor(1).to_float() == (float)-3.2);
        CHECK((-pi).floor(2).to_float() == (float)-3.15);
        CHECK((-pi).floor(3).to_float() == (float)-3.142);
        CHECK((-pi).floor(4).to_float() == (float)-3.1416);
        CHECK((-pi).floor(5).to_float() == (float)-3.1416);

        CHECK(doubledouble::nan().floor().isnan() == std::isnan(std::floor(std::numeric_limits<double>::quiet_NaN())));
        CHECK(doubledouble::inf().floor().isinf() == std::isinf(std::floor(std::numeric_limits<double>::infinity())));
        CHECK((-doubledouble::inf()).floor().isinf() == std::isinf(std::floor(-std::numeric_limits<double>::infinity())));
        CHECK(doubledouble::inf().floor().signbit() == std::signbit(std::floor(std::numeric_limits<double>::infinity())));
        CHECK((-doubledouble::inf()).floor().signbit() == std::signbit(std::floor(-std::numeric_limits<double>::infinity())));
    }

    SUBCASE("fmod") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                double x = rand_double();
                double denom = rand_double();
                auto result = doubledouble(x).fmod(denom);

                if (result.isnan()) {
                    CHECK(std::isnan(std::fmod(x, denom)));
                } else {
                    CHECK(result.to_float() == (float)std::fmod(x, denom));
                }
            }
        }

        SUBCASE("Special cases") {

            CHECK(doubledouble(2.0).fmod(0.0).isnan());
            CHECK(doubledouble::nan().fmod(0.0).isnan());
            CHECK(doubledouble::inf().fmod(0.0).isnan());

            CHECK(doubledouble(2.0).fmod(doubledouble::nan()).isnan());
            CHECK(doubledouble::nan().fmod(2.0).isnan());
            CHECK(doubledouble::nan().fmod(doubledouble::nan()).isnan());
            CHECK(doubledouble::nan().fmod(doubledouble::inf()).isnan());
            CHECK(doubledouble::inf().fmod(doubledouble::nan()).isnan());

            CHECK(doubledouble(2.0).fmod(doubledouble::inf()) == doubledouble(2.0));
            CHECK(doubledouble(4.1).fmod(doubledouble::inf()) == doubledouble(4.1));
            CHECK(doubledouble::inf().fmod(2.0).isnan());
            CHECK(doubledouble::inf().fmod(doubledouble::inf()).isnan());


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
            CHECK((float)doubledouble(p[i].v).trunc() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK((float)doubledouble(p[i].v).trunc() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK((float)doubledouble(p[i].v).trunc() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK((float)doubledouble(p[i].v).trunc() == p[i].up);
        }

        doubledouble pi("3.14159265358979323846264338327950");

        CHECK(pi.trunc(1).to_float() == (float)3.1);
        CHECK(pi.trunc(2).to_float() == (float)3.14);
        CHECK(pi.trunc(3).to_float() == (float)3.141);
        CHECK(pi.trunc(4).to_float() == (float)3.1415);
        CHECK(pi.trunc(5).to_float() == (float)3.14159);

        CHECK((-pi).trunc(1).to_float() == (float)-3.1);
        CHECK((-pi).trunc(2).to_float() == (float)-3.14);
        CHECK((-pi).trunc(3).to_float() == (float)-3.141);
        CHECK((-pi).trunc(4).to_float() == (float)-3.1415);
        CHECK((-pi).trunc(5).to_float() == (float)-3.14159);

        CHECK(doubledouble::nan().trunc().isnan() == std::isnan(std::trunc(std::numeric_limits<double>::quiet_NaN())));
        CHECK(doubledouble::inf().trunc().isinf() == std::isinf(std::trunc(std::numeric_limits<double>::infinity())));
        CHECK((-doubledouble::inf()).trunc().isinf() == std::isinf(std::trunc(-std::numeric_limits<double>::infinity())));
        CHECK(doubledouble::inf().trunc().signbit() == std::signbit(std::trunc(std::numeric_limits<double>::infinity())));
        CHECK((-doubledouble::inf()).trunc().signbit() == std::signbit(std::trunc(-std::numeric_limits<double>::infinity())));
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
            CHECK((float)doubledouble(p[i].v).round() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK((float)doubledouble(p[i].v).round() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK((float)doubledouble(p[i].v).round() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK((float)doubledouble(p[i].v).round() == p[i].up);
        }

        doubledouble pi("3.14159265358979323846264338327950");

        CHECK(pi.round(1).to_float() == (float)3.1);
        CHECK(pi.round(2).to_float() == (float)3.14);
        CHECK(pi.round(3).to_float() == (float)3.142);
        CHECK(pi.round(4).to_float() == (float)3.1416);
        CHECK(pi.round(5).to_float() == (float)3.14159);

        CHECK((-pi).round(1).to_float() == (float)-3.1);
        CHECK((-pi).round(2).to_float() == (float)-3.14);
        CHECK((-pi).round(3).to_float() == (float)-3.142);
        CHECK((-pi).round(4).to_float() == (float)-3.1416);
        CHECK((-pi).round(5).to_float() == (float)-3.14159);

        CHECK(doubledouble::nan().round().isnan() == std::isnan(std::round(std::numeric_limits<double>::quiet_NaN())));
        CHECK(doubledouble::inf().round().isinf() == std::isinf(std::round(std::numeric_limits<double>::infinity())));
        CHECK((-doubledouble::inf()).round().isinf() == std::isinf(std::round(-std::numeric_limits<double>::infinity())));
        CHECK(doubledouble::inf().round().signbit() == std::signbit(std::round(std::numeric_limits<double>::infinity())));
        CHECK((-doubledouble::inf()).round().signbit() == std::signbit(std::round(-std::numeric_limits<double>::infinity())));
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
            CHECK((float)doubledouble(p[i].v).roundEven() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK((float)doubledouble(p[i].v).roundEven() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK((float)doubledouble(p[i].v).roundEven() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK((float)doubledouble(p[i].v).roundEven() == p[i].up);
        }

        CHECK(doubledouble::nan().roundEven().isnan() == true);
        CHECK(doubledouble::inf().roundEven().isinf() == true);
        CHECK((-doubledouble::inf()).roundEven().isinf() == true);
        CHECK(doubledouble::inf().roundEven().signbit() == 0);
        CHECK((-doubledouble::inf()).roundEven().signbit() == 1);
    }

    SUBCASE("lround") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).lround() == std::lround(x));
        }

        CHECK(doubledouble::nan().lround() == std::lround(std::numeric_limits<double>::quiet_NaN()));
        CHECK(doubledouble::inf().lround() == std::lround(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).lround() == std::lround(-std::numeric_limits<double>::infinity()));
        CHECK(doubledouble::inf().lround() == std::lround(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).lround() == std::lround(-std::numeric_limits<double>::infinity()));
    }

    SUBCASE("llround") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).llround() == std::llround(x));
        }

        CHECK(doubledouble::nan().llround() == std::llround(std::numeric_limits<double>::quiet_NaN()));
        CHECK(doubledouble::inf().llround() == std::llround(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).llround() == std::llround(-std::numeric_limits<double>::infinity()));
        CHECK(doubledouble::inf().llround() == std::llround(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).llround() == std::llround(-std::numeric_limits<double>::infinity()));
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
            CHECK((float)doubledouble(p[i].v).rint() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK((float)doubledouble(p[i].v).rint() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK((float)doubledouble(p[i].v).rint() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK((float)doubledouble(p[i].v).rint() == p[i].up);
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
            CHECK(std::abs(doubledouble(pi).rint(r[i].digits).to_double() - r[i].down) < 1e-10);
            fesetround(FE_TONEAREST);
            CHECK(std::abs(doubledouble(pi).rint(r[i].digits).to_double() - r[i].round) < 1e-10);
            fesetround(FE_TOWARDZERO);
            CHECK(std::abs(doubledouble(pi).rint(r[i].digits).to_double() - r[i].zero) < 1e-10);
            fesetround(FE_UPWARD);
            CHECK(std::abs(doubledouble(pi).rint(r[i].digits).to_double() - r[i].up) < 1e-10);
        }

        CHECK(doubledouble::nan().rint().isnan() == std::isnan(std::rint(std::numeric_limits<double>::quiet_NaN())));
        CHECK(doubledouble::inf().rint().isinf() == std::isinf(std::rint(std::numeric_limits<double>::infinity())));
        CHECK((-doubledouble::inf()).rint().isinf() == std::isinf(std::rint(-std::numeric_limits<double>::infinity())));
        CHECK(doubledouble::inf().rint().signbit() == std::signbit(std::rint(std::numeric_limits<double>::infinity())));
        CHECK((-doubledouble::inf()).rint().signbit() == std::signbit(std::rint(-std::numeric_limits<double>::infinity())));
    }

    SUBCASE("lrint") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).lrint() == std::lrint(x));
        }

        CHECK(doubledouble::nan().lrint() == std::lrint(std::numeric_limits<double>::quiet_NaN()));
        CHECK(doubledouble::inf().lrint() == std::lrint(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).lrint() == std::lrint(-std::numeric_limits<double>::infinity()));
        CHECK(doubledouble::inf().lrint() == std::lrint(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).lrint() == std::lrint(-std::numeric_limits<double>::infinity()));
    }

    SUBCASE("llrint") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).llrint() == std::llrint(x));
        }

        CHECK(doubledouble::nan().llrint() == std::llrint(std::numeric_limits<double>::quiet_NaN()));
        CHECK(doubledouble::inf().llrint() == std::llrint(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).llrint() == std::llrint(-std::numeric_limits<double>::infinity()));
        CHECK(doubledouble::inf().llrint() == std::llrint(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).llrint() == std::llrint(-std::numeric_limits<double>::infinity()));
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
            CHECK((float)doubledouble(p[i].v).nearbyint() == p[i].down);
            fesetround(FE_TONEAREST);
            CHECK((float)doubledouble(p[i].v).nearbyint() == p[i].round);
            fesetround(FE_TOWARDZERO);
            CHECK((float)doubledouble(p[i].v).nearbyint() == p[i].zero);
            fesetround(FE_UPWARD);
            CHECK((float)doubledouble(p[i].v).nearbyint() == p[i].up);
        }

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).nearbyint().to_float() == (float)std::nearbyint(x));
        }

        CHECK(doubledouble::nan().nearbyint().isnan());
        CHECK(doubledouble::inf().nearbyint() == std::nearbyint(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).nearbyint() == std::nearbyint(-std::numeric_limits<double>::infinity()));
        CHECK(doubledouble::inf().nearbyint() == std::nearbyint(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).nearbyint() == std::nearbyint(-std::numeric_limits<double>::infinity()));
    }

    fesetround(mode);
}
