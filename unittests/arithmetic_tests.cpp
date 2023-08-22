#include "main.h"

TEST_CASE("Basic arithmetic") {

    srand(0);

    SUBCASE("Negation") {

        COMPARE((-doubledouble(0.0)), -0.0);
        COMPARE((-doubledouble(42.0)).to_double(), -42.0);
        COMPARE((-doubledouble(-42.0)).to_double(), 42.0);
        COMPARE((-doubledouble::posnan()), -posnan);
        COMPARE((-doubledouble::negnan()), -negnan);
        COMPARE((-doubledouble::posinf()), -posinf);
        COMPARE((-doubledouble::neginf()), -neginf);
    }

    SUBCASE("Addition") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                auto x = rand_double(), y = rand_double();
                COMPARE((doubledouble(x) + doubledouble(y)).to_float(), float(x + y));
            }
        }

        SUBCASE("Special cases") {

            COMPARE(doubledouble(123.0) + doubledouble(123.0), 123.0 + 123.0);
            COMPARE(doubledouble(123.0) + doubledouble(-123.0), 123.0 - 123.0);
            COMPARE(doubledouble(123.0) + doubledouble::posnan(), 123.0 + posnan);
            COMPARE(doubledouble(123.0) + doubledouble::negnan(), 123.0 + negnan);
            COMPARE(doubledouble(123.0) + doubledouble::posinf(), 123.0 + posinf);
            COMPARE(doubledouble(123.0) + doubledouble::neginf(), 123.0 + neginf);

            COMPARE(doubledouble(-123.0) + doubledouble(123.0), -123.0 + 123.0);
            COMPARE(doubledouble(-123.0) + doubledouble(-123.0), -123.0 + -123.0);
            COMPARE(doubledouble(-123.0) + doubledouble::posnan(), -123.0 + posnan);
            COMPARE(doubledouble(-123.0) + doubledouble::negnan(), -123.0 + negnan);
            COMPARE(doubledouble(-123.0) + doubledouble::posinf(), -123.0 + posinf);
            COMPARE(doubledouble(-123.0) + doubledouble::neginf(), -123.0 + neginf);

            COMPARE(doubledouble::posnan() + doubledouble(123.0), posnan + 123.0);
            COMPARE(doubledouble::posnan() + doubledouble(-123.0), posnan - 123.0);
            COMPARE(doubledouble::posnan() + doubledouble::posnan(), posnan + posnan);
            COMPARE(doubledouble::posnan() + doubledouble::posinf(), posnan + posinf);
            COMPARE(doubledouble::posnan() + doubledouble::neginf(), posnan + neginf);

            COMPARE(doubledouble::negnan() + doubledouble(123.0), negnan + 123.0);
            COMPARE(doubledouble::negnan() + doubledouble(-123.0), negnan + -123.0);
            COMPARE(doubledouble::negnan() + doubledouble::posnan(), negnan + posnan);
            COMPARE(doubledouble::negnan() + doubledouble::posinf(), negnan + posinf);
            COMPARE(doubledouble::negnan() + doubledouble::neginf(), negnan + neginf);

            COMPARE(doubledouble::posinf() + doubledouble(123.0), posinf + 123.0);
            COMPARE(doubledouble::posinf() + doubledouble(-123.0), posinf + -123.0);
            COMPARE(doubledouble::posinf() + doubledouble::posnan(), posinf + posnan);
            COMPARE(doubledouble::posinf() + doubledouble::posinf(), posinf + posinf);
            COMPARE(doubledouble::posinf() + doubledouble::neginf(), posinf + neginf);

            COMPARE(doubledouble::neginf() + doubledouble(123.0), neginf + 123.0);
            COMPARE(doubledouble::neginf() + doubledouble(-123.0), neginf + -123.0);
            COMPARE(doubledouble::neginf() + doubledouble::posnan(), neginf + posnan);
            COMPARE(doubledouble::neginf() + doubledouble::posinf(), neginf + posinf);
            COMPARE(doubledouble::neginf() + doubledouble::neginf(), neginf + neginf);
        }
    }

    SUBCASE("Subtraction") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                auto x = rand_double(), y = rand_double();
                COMPARE((doubledouble(x) - doubledouble(y)).to_float(), float(x - y));
            }
        }

        SUBCASE("Special cases") {

            COMPARE(doubledouble(123.0) - doubledouble(123.0), 0.0);
            COMPARE(doubledouble(123.0) - doubledouble(-123.0), 246.0);
            COMPARE(doubledouble(123.0) - doubledouble::posnan(), negnan);
            COMPARE(doubledouble(123.0) - doubledouble::negnan(), posnan);
            COMPARE(doubledouble(123.0) - doubledouble::posinf(), neginf);
            COMPARE(doubledouble(123.0) - doubledouble::neginf(), posinf);

            COMPARE(doubledouble(-123.0) - doubledouble(123.0), -246.0);
            COMPARE(doubledouble(-123.0) - doubledouble(-123.0), 0.0);
            COMPARE(doubledouble(-123.0) - doubledouble::posnan(), negnan);
            COMPARE(doubledouble(-123.0) - doubledouble::negnan(), posnan);
            COMPARE(doubledouble(-123.0) - doubledouble::posinf(), neginf);
            COMPARE(doubledouble(-123.0) - doubledouble::neginf(), posinf);

            COMPARE(doubledouble::posnan() - doubledouble(123.0), posnan);
            COMPARE(doubledouble::posnan() - doubledouble(-123.0), posnan);
            COMPARE(doubledouble::posnan() - doubledouble::nan(), posnan);
            COMPARE(doubledouble::posnan() - doubledouble::posinf(), posnan);
            COMPARE(doubledouble::posnan() - doubledouble::neginf(), posnan);

            COMPARE(doubledouble::negnan() - doubledouble(123.0), negnan);
            COMPARE(doubledouble::negnan() - doubledouble(-123.0), negnan);
            COMPARE(doubledouble::negnan() - doubledouble::nan(), negnan);
            COMPARE(doubledouble::negnan() - doubledouble::posinf(), negnan);
            COMPARE(doubledouble::negnan() - doubledouble::neginf(), negnan);

            COMPARE(doubledouble::posinf() - doubledouble(123.0), posinf);
            COMPARE(doubledouble::posinf() - doubledouble(-123.0), posinf);
            COMPARE(doubledouble::posinf() - doubledouble::nan(), negnan);
            COMPARE(doubledouble::posinf() - doubledouble::posinf(), posnan);
            COMPARE(doubledouble::posinf() - doubledouble::neginf(), posinf);

            COMPARE(doubledouble::neginf() - doubledouble(123.0), neginf);
            COMPARE(doubledouble::neginf() - doubledouble(-123.0), neginf);
            COMPARE(doubledouble::neginf() - doubledouble::nan(), negnan);
            COMPARE(doubledouble::neginf() - doubledouble::posinf(), neginf);
            COMPARE(doubledouble::neginf() - doubledouble::neginf(), posnan);
        }
    }

    SUBCASE("Multiplication") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                auto x = rand_double(), y = rand_double();
                CHECK((doubledouble(x) * doubledouble(y)).to_float() == float(x * y));
            }
        }

        SUBCASE("Special cases") {

            COMPARE(doubledouble(123.0) * doubledouble(123.0), 15129.0);
            COMPARE(doubledouble(123.0) * doubledouble(-123.0), -15129.0);
            COMPARE(doubledouble(123.0) * doubledouble::nan(), posnan);
            COMPARE(doubledouble(123.0) * doubledouble::posinf(), posinf);
            COMPARE(doubledouble(123.0) * doubledouble::neginf(), neginf);

            COMPARE(doubledouble(-123.0) * doubledouble(123.0), -15129.0);
            COMPARE(doubledouble(-123.0) * doubledouble(-123.0), 15129.0);
            COMPARE(doubledouble(-123.0) * doubledouble::nan(), posnan);
            COMPARE(doubledouble(-123.0) * doubledouble::posinf(), neginf);
            COMPARE(doubledouble(-123.0) * doubledouble::neginf(), posinf);

            COMPARE(doubledouble::posnan() * doubledouble(123.0), posnan);
            COMPARE(doubledouble::posnan() * doubledouble(-123.0), posnan);
            COMPARE(doubledouble::posnan() * doubledouble::nan(), posnan);
            COMPARE(doubledouble::posnan() * doubledouble::posinf(), posnan);
            COMPARE(doubledouble::posnan() * doubledouble::neginf(), posnan);

            COMPARE(doubledouble::negnan() * doubledouble(123.0), negnan);
            COMPARE(doubledouble::negnan() * doubledouble(-123.0), negnan);
            COMPARE(doubledouble::negnan() * doubledouble::nan(), negnan);
            COMPARE(doubledouble::negnan() * doubledouble::posinf(), negnan);
            COMPARE(doubledouble::negnan() * doubledouble::neginf(), negnan);

            COMPARE(doubledouble::posinf() * doubledouble(123.0), posinf);
            COMPARE(doubledouble::posinf() * doubledouble(-123.0), neginf);
            COMPARE(doubledouble::posinf() * doubledouble::nan(), posnan);
            COMPARE(doubledouble::posinf() * doubledouble::posinf(), posinf);
            COMPARE(doubledouble::posinf() * doubledouble::neginf(), neginf);

            COMPARE(doubledouble::neginf() * doubledouble(123.0), neginf);
            COMPARE(doubledouble::neginf() * doubledouble(-123.0), posinf);
            COMPARE(doubledouble::neginf() * doubledouble::nan(), posnan);
            COMPARE(doubledouble::neginf() * doubledouble::posinf(), neginf);
            COMPARE(doubledouble::neginf() * doubledouble::neginf(), posinf);
        }
    }

    SUBCASE("Division") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                auto x = rand_double(), y = rand_double();
                if (y == 0.0) continue;
                COMPARE((doubledouble(x) / doubledouble(y)).to_float(), float(x / y));
            }
        }

        SUBCASE("Special cases") {

            COMPARE(doubledouble(123.0) / doubledouble(123.0), 1.0);
            COMPARE(doubledouble(123.0) / doubledouble(-123.0), -1.0);
            COMPARE(doubledouble(123.0) / doubledouble::nan(), posnan);
            COMPARE(doubledouble(123.0) / doubledouble::inf(), 0.0);
            COMPARE(doubledouble(123.0) / -doubledouble::inf(), -0.0);

            COMPARE(doubledouble(-123.0) / doubledouble(123.0), -1.0);
            COMPARE(doubledouble(-123.0) / doubledouble(-123.0), 1.0);
            COMPARE(doubledouble(-123.0) / doubledouble::nan(), posnan);
            COMPARE(doubledouble(-123.0) / doubledouble::inf(), -0.0);
            COMPARE(doubledouble(-123.0) / -doubledouble::inf(), 0.0);

            COMPARE(doubledouble::posnan() / doubledouble(123.0), posnan);
            COMPARE(doubledouble::posnan() / doubledouble(-123.0), posnan);
            COMPARE(doubledouble::posnan() / doubledouble::nan(), posnan);
            COMPARE(doubledouble::posnan() / doubledouble::inf(), posnan);
            COMPARE(doubledouble::posnan() / -doubledouble::inf(), posnan);

            COMPARE(doubledouble::negnan() / doubledouble(123.0), negnan);
            COMPARE(doubledouble::negnan() / doubledouble(-123.0), negnan);
            COMPARE(doubledouble::negnan() / doubledouble::nan(), negnan);
            COMPARE(doubledouble::negnan() / doubledouble::inf(), negnan);
            COMPARE(doubledouble::negnan() / -doubledouble::inf(), negnan);

            COMPARE(doubledouble::posinf() / doubledouble(123.0), posinf);
            COMPARE(doubledouble::posinf() / doubledouble(-123.0), neginf);
            COMPARE(doubledouble::posinf() / doubledouble::nan(), posnan);
            COMPARE(doubledouble::posinf() / doubledouble::inf(), posnan);
            COMPARE(doubledouble::posinf() / -doubledouble::inf(), posnan);

            COMPARE(doubledouble::neginf() / doubledouble(123.0), neginf);
            COMPARE(doubledouble::neginf() / doubledouble(-123.0), posinf);
            COMPARE(doubledouble::neginf() / doubledouble::nan(), posnan);
            COMPARE(doubledouble::neginf() / doubledouble::inf(), posnan);
            COMPARE(doubledouble::neginf() / -doubledouble::inf(), posnan);
        }

        SUBCASE("Division by zero") {

            COMPARE(doubledouble(42.0) / 0.0, posinf);
            COMPARE(doubledouble(-42.0) / 0.0, neginf);
            COMPARE(doubledouble(0.0) / 0.0, posnan);
            COMPARE(doubledouble::posnan() / 0.0, posnan);
            COMPARE(doubledouble::negnan() / 0.0, negnan);
            COMPARE(doubledouble::posinf() / 0.0, posinf);
            COMPARE(doubledouble::neginf() / 0.0, neginf);
        }
    }

    SUBCASE("Increment and decrement operators") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double();
            doubledouble dx(x);

            x++; dx++; COMPARE(dx.to_float(), (float)x);
            ++x; ++dx; COMPARE(dx.to_float(), (float)x);
            x--; dx--; COMPARE(dx.to_float(), (float)x);
            --x; --dx; COMPARE(dx.to_float(), (float)x);
        }
    }
}
