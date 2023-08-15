#include "main.h"

TEST_CASE("Rounding and remainder functions") {

    srand(0);

    SUBCASE("ceil") {

        CHECK(doubledouble(2,0.3).ceil().to_float() == 3.0);
        CHECK(doubledouble(3,0.8).ceil().to_float() == 4.0);
        CHECK(doubledouble(5,0.5).ceil().to_float() == 6.0);
        CHECK(doubledouble(-2,-0.3).ceil().to_float() == -2.0);
        CHECK(doubledouble(-3,-0.8).ceil().to_float() == -3.0);
        CHECK(doubledouble(-5,-0.5).ceil().to_float() == -5.0);

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).ceil().to_float() == (float)std::ceil(x));
        }
    }

    SUBCASE("floor") {

        CHECK(doubledouble(2,0.3).floor().to_float() == 2.0);
        CHECK(doubledouble(3,0.8).floor().to_float() == 3.0);
        CHECK(doubledouble(5,0.5).floor().to_float() == 5.0);
        CHECK(doubledouble(-2,-0.3).floor().to_float() == -3.0);
        CHECK(doubledouble(-3,-0.8).floor().to_float() == -4.0);
        CHECK(doubledouble(-5,-0.5).floor().to_float() == -6.0);

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

        CHECK(doubledouble(2,0.3).trunc().to_float() == 2.0);
        CHECK(doubledouble(3,0.8).trunc().to_float() == 3.0);
        CHECK(doubledouble(5,0.5).trunc().to_float() == 5.0);
        CHECK(doubledouble(-2,-0.3).trunc().to_float() == -2.0);
        CHECK(doubledouble(-3,-0.8).trunc().to_float() == -3.0);
        CHECK(doubledouble(-5,-0.5).trunc().to_float() == -5.0);

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).trunc().to_float() == (float)std::trunc(x));
        }
    }

    SUBCASE("round") {

        CHECK(doubledouble(2,0.3).round().to_float() == 2.0);
        CHECK(doubledouble(3,0.8).round().to_float() == 4.0);
        CHECK(doubledouble(5,0.5).round().to_float() == 6.0);
        CHECK(doubledouble(-2,-0.3).round().to_float() == -2.0);
        CHECK(doubledouble(-3,-0.8).round().to_float() == -4.0);
        CHECK(doubledouble(-5,-0.5).round().to_float() == -6.0);

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).round().to_float() == (float)std::round(x));
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

    SUBCASE("nearbyint") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).nearbyint().to_float() == (float)std::nearbyint(x));
        }
    }
}
