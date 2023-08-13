#include "doctest.h"
#include "double-double.h"

TEST_CASE("Basic arithmetic") {

    SUBCASE("Addition") {

        SUBCASE("double") {

            doubledouble x = -50.0;
            doubledouble y = 5.0;

            for (int i = 0; i < 100; i++, x += 1.0, y -= 0.1) {

                CHECK((x + y).asDouble() == x.asDouble() + y.asDouble());
            }
        }
        SUBCASE("long double") {

            longdoubledouble x = -50.0;
            longdoubledouble y = 5.0;

            for (int i = 0; i < 100; i++, x += 1.0, y -= 0.1) {

                CHECK((x + y).asLongDouble() == x.asLongDouble() + y.asLongDouble());
            }
        }
    }
    SUBCASE("Subtraction") {

        SUBCASE("double") {

            doubledouble x = -50.0;
            doubledouble y = 5.0;

            for (int i = 0; i < 100; i++, x += 1.0, y -= 0.1) {

                CHECK((x - y).asDouble() == x.asDouble() - y.asDouble());
            }
        }
        SUBCASE("long double") {

            longdoubledouble x = -50.0;
            longdoubledouble y = 5.0;

            for (int i = 0; i < 100; i++, x += 1.0, y -= 0.1) {

                CHECK((x - y).asLongDouble() == x.asLongDouble() - y.asLongDouble());
            }
        }
    }
    SUBCASE("Multiplication") {

        SUBCASE("double") {

            doubledouble x = -50.0;
            doubledouble y = 5.0;

            for (int i = 0; i < 100; i++, x += 1.0, y -= 0.1) {

                CHECK((x * y).asDouble() == x.asDouble() * y.asDouble());
            }
        }
        SUBCASE("long double") {

            longdoubledouble x = -50.0;
            longdoubledouble y = 5.0;

            for (int i = 0; i < 100; i++, x += 1.0, y -= 0.1) {

                CHECK((x * y).asLongDouble() == x.asLongDouble() * y.asLongDouble());
            }
        }
    }
    SUBCASE("Division") {

        SUBCASE("double") {

            doubledouble x = -50.0;
            doubledouble y = 5.0;

            for (int i = 0; i < 100; i++, x += 1.0, y -= 0.1) {

                if (y == 0) continue;
                CHECK((x / y).asDouble() == x.asDouble() / y.asDouble());
            }
        }
        SUBCASE("long double") {

            longdoubledouble x = -50.0;
            longdoubledouble y = 5.0;

            for (int i = 0; i < 100; i++, x += 1.0, y -= 0.1) {

                if (y == 0) continue;
                CHECK((x / y).asLongDouble() == x.asLongDouble() / y.asLongDouble());
            }
        }
    }
}
