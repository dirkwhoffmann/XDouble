#include "main.h"

TEST_CASE("Basic arithmetic") {

    srand(0);

    SUBCASE("Plus") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double(), y = rand_double();
            CHECK((doubledouble(x) + doubledouble(y)).to_float() == float(x + y));
        }
    }

    SUBCASE("Minus") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double(), y = rand_double();
            CHECK((doubledouble(x) - doubledouble(y)).to_float() == float(x - y));
        }
    }

    SUBCASE("Mult") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double(), y = rand_double();
            CHECK((doubledouble(x) * doubledouble(y)).to_float() == float(x * y));
        }
    }

    SUBCASE("Division") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double(), y = rand_double();
            if (y == 0.0) continue;
            CHECK((doubledouble(x) / doubledouble(y)).to_float() == float(x / y));
        }
    }

    SUBCASE("Division by zero") {

        CHECK((doubledouble(42.0) / 0.0).isinf());
        CHECK((doubledouble(-42.0) / 0.0).isinf());
        CHECK(doubledouble(42.0) / 0.0 == doubledouble::inf());
        CHECK(doubledouble(-42.0) / 0.0 != doubledouble::inf());
        CHECK(doubledouble(-42.0) / 0.0 == -doubledouble::inf());
        CHECK((doubledouble(0.0) / 0.0).isnan());
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
