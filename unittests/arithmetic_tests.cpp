#include "doctest.h"
#include "double-double.h"

TEST_CASE("Basic arithmetic") {

    SUBCASE("Addition") {

        for (double x = -50.0, y = 5.0; x <= 100.0; x += 1.0, y -= 0.1) {

            doubledouble dx(x), dy(y);
            CHECK((dx + dy).to_float() == float(x + y));
        }
    }

    SUBCASE("Subtraction") {

        for (double x = -50.0, y = 5.0; x <= 100.0; x += 1.0, y -= 0.1) {

            doubledouble dx(x), dy(y);
            CHECK((dx - dy).to_float() == float(x - y));
        }
    }

    SUBCASE("Multiplication") {

        for (double x = -50.0, y = 5.0; x <= 100.0; x += 1.0, y -= 0.1) {

            doubledouble dx(x), dy(y);
            CHECK((dx * dy).to_float() == float(x * y));
        }
    }

    SUBCASE("Division") {

        for (double x = -50.0, y = 5.0; x <= 100.0; x += 1.0, y -= 0.1) {

            doubledouble dx(x), dy(y);
            CHECK((dx / dy).to_float() == float(x / y));
        }
    }

    SUBCASE("Increment and decrement operators") {

        for (double x = -5.0; x <= 10.0; x += 0.1) {

            doubledouble dx(x);

            dx++; CHECK(std::abs(dx.to_double() - (x + 1.0)) < 1e-10);
            ++dx; CHECK(std::abs(dx.to_double() - (x + 2.0)) < 1e-10);
            dx--; CHECK(std::abs(dx.to_double() - (x + 1.0)) < 1e-10);
            --dx; CHECK(std::abs(dx.to_double() - (x + 0.0)) < 1e-10);
        }
    }
}
