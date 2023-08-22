#include "main.h"

TEST_CASE("Basic arithmetic") {

    srand(0);

    SUBCASE("Negation") {

        COMPARE ((-doubledouble(0.0)), -0.0);
        COMPARE ((-doubledouble(42.0)).to_double(), -42.0);
        COMPARE ((-doubledouble(-42.0)).to_double(), 42.0);
        COMPARE ((-doubledouble::posnan()), -posnan);
        COMPARE ((-doubledouble::negnan()), -negnan);
        COMPARE ((-doubledouble::posinf()), -posinf);
        COMPARE ((-doubledouble::neginf()), -neginf);
    }

    SUBCASE("Addition") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                auto x = rand_double(), y = rand_double();
                COMPARE ((doubledouble(x) + doubledouble(y)).to_float(), float(x + y));
            }
        }

        SUBCASE("Special cases") {

            COMPARE (doubledouble(123.0) + doubledouble(123.0), 123.0 + 123.0);
            COMPARE (doubledouble(123.0) + doubledouble(-123.0), 123.0 - 123.0);
            COMPARE (doubledouble(123.0) + doubledouble::posnan(), 123.0 + posnan);
            COMPARE (doubledouble(123.0) + doubledouble::negnan(), 123.0 + negnan);
            COMPARE (doubledouble(123.0) + doubledouble::posinf(), 123.0 + posinf);
            COMPARE (doubledouble(123.0) + doubledouble::neginf(), 123.0 + neginf);

            COMPARE (doubledouble(-123.0) + doubledouble(123.0), -123.0 + 123.0);
            COMPARE (doubledouble(-123.0) + doubledouble(-123.0), -123.0 + -123.0);
            COMPARE (doubledouble(-123.0) + doubledouble::posnan(), -123.0 + posnan);
            COMPARE (doubledouble(-123.0) + doubledouble::negnan(), -123.0 + negnan);
            COMPARE (doubledouble(-123.0) + doubledouble::posinf(), -123.0 + posinf);
            COMPARE (doubledouble(-123.0) + doubledouble::neginf(), -123.0 + neginf);

            COMPARE (doubledouble::posnan() + doubledouble(123.0), posnan + 123.0);
            COMPARE (doubledouble::posnan() + doubledouble(-123.0), posnan - 123.0);
            COMPARE (doubledouble::posnan() + doubledouble::posnan(), posnan + posnan);
            COMPARE (doubledouble::posnan() + doubledouble::negnan(), posnan + negnan);
            COMPARE (doubledouble::posnan() + doubledouble::posinf(), posnan + posinf);
            COMPARE (doubledouble::posnan() + doubledouble::neginf(), posnan + neginf);

            COMPARE (doubledouble::negnan() + doubledouble(123.0), negnan + 123.0);
            COMPARE (doubledouble::negnan() + doubledouble(-123.0), negnan + -123.0);
            COMPARE (doubledouble::negnan() + doubledouble::posnan(), negnan + posnan);
            COMPARE (doubledouble::negnan() + doubledouble::negnan(), negnan + negnan);
            COMPARE (doubledouble::negnan() + doubledouble::posinf(), negnan + posinf);
            COMPARE (doubledouble::negnan() + doubledouble::neginf(), negnan + neginf);

            COMPARE (doubledouble::posinf() + doubledouble(123.0), posinf + 123.0);
            COMPARE (doubledouble::posinf() + doubledouble(-123.0), posinf + -123.0);
            COMPARE (doubledouble::posinf() + doubledouble::posnan(), posinf + posnan);
            COMPARE (doubledouble::posinf() + doubledouble::negnan(), posinf + negnan);
            COMPARE (doubledouble::posinf() + doubledouble::posinf(), posinf + posinf);
            COMPARE (doubledouble::posinf() + doubledouble::neginf(), posinf + neginf);

            COMPARE (doubledouble::neginf() + doubledouble(123.0), neginf + 123.0);
            COMPARE (doubledouble::neginf() + doubledouble(-123.0), neginf + -123.0);
            COMPARE (doubledouble::neginf() + doubledouble::posnan(), neginf + posnan);
            COMPARE (doubledouble::neginf() + doubledouble::negnan(), neginf + negnan);
            COMPARE (doubledouble::neginf() + doubledouble::posinf(), neginf + posinf);
            COMPARE (doubledouble::neginf() + doubledouble::neginf(), neginf + neginf);
        }
    }

    SUBCASE("Subtraction") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                auto x = rand_double(), y = rand_double();
                COMPARE ((doubledouble(x) - doubledouble(y)).to_float(), float(x - y));
            }
        }

        SUBCASE("Special cases") {

            COMPARE (doubledouble(123.0) - doubledouble(123.0), 123.0 - 123.0);
            COMPARE (doubledouble(123.0) - doubledouble(-123.0), 246.0);
            COMPARE (doubledouble(123.0) - doubledouble::posnan(), 123.0 - posnan);
            COMPARE (doubledouble(123.0) - doubledouble::negnan(), 123.0 - negnan);
            COMPARE (doubledouble(123.0) - doubledouble::posinf(), 123.0 - posinf);
            COMPARE (doubledouble(123.0) - doubledouble::neginf(), 123.0 - neginf);

            COMPARE (doubledouble(-123.0) - doubledouble(123.0), -246.0);
            COMPARE (doubledouble(-123.0) - doubledouble(-123.0), 0.0);
            COMPARE (doubledouble(-123.0) - doubledouble::posnan(), -123.0 - posnan);
            COMPARE (doubledouble(-123.0) - doubledouble::negnan(), -123.0 - negnan);
            COMPARE (doubledouble(-123.0) - doubledouble::posinf(), -123.0 - posinf);
            COMPARE (doubledouble(-123.0) - doubledouble::neginf(), -123.0 - neginf);

            COMPARE (doubledouble::posnan() - doubledouble(123.0), posnan - 123.0);
            COMPARE (doubledouble::posnan() - doubledouble(-123.0), posnan - -123.0);
            COMPARE (doubledouble::posnan() - doubledouble::posnan(), posnan - posnan);
            COMPARE (doubledouble::posnan() - doubledouble::negnan(), posnan - negnan);
            COMPARE (doubledouble::posnan() - doubledouble::posinf(), posnan - posinf);
            COMPARE (doubledouble::posnan() - doubledouble::neginf(), posnan - neginf);

            COMPARE (doubledouble::negnan() - doubledouble(123.0), negnan - 123.0);
            COMPARE (doubledouble::negnan() - doubledouble(-123.0), negnan - -123.0);
            COMPARE (doubledouble::negnan() - doubledouble::posnan(), negnan - posnan);
            COMPARE (doubledouble::negnan() - doubledouble::negnan(), negnan - negnan);
            COMPARE (doubledouble::negnan() - doubledouble::posinf(), negnan - posinf);
            COMPARE (doubledouble::negnan() - doubledouble::neginf(), negnan - neginf);

            COMPARE (doubledouble::posinf() - doubledouble(123.0), posinf - 123.0);
            COMPARE (doubledouble::posinf() - doubledouble(-123.0), posinf - -123.0);
            COMPARE (doubledouble::posinf() - doubledouble::posnan(), posinf - posnan);
            COMPARE (doubledouble::posinf() - doubledouble::negnan(), posinf - negnan);
            COMPARE (doubledouble::posinf() - doubledouble::posinf(), posinf - posinf);
            COMPARE (doubledouble::posinf() - doubledouble::neginf(), posinf - neginf);

            COMPARE (doubledouble::neginf() - doubledouble(123.0), neginf - 123.0);
            COMPARE (doubledouble::neginf() - doubledouble(-123.0), neginf - -123.0);
            COMPARE (doubledouble::neginf() - doubledouble::posnan(), neginf - posnan);
            COMPARE (doubledouble::neginf() - doubledouble::negnan(), neginf - negnan);
            COMPARE (doubledouble::neginf() - doubledouble::posinf(), neginf - posinf);
            COMPARE (doubledouble::neginf() - doubledouble::neginf(), neginf - neginf);
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

            COMPARE (doubledouble(123.0) * doubledouble(123.0), 123.0 * 123.0);
            COMPARE (doubledouble(123.0) * doubledouble(-123.0), 123.0 * -123.0);
            COMPARE (doubledouble(123.0) * doubledouble::posnan(), 123.0 * posnan);
            COMPARE (doubledouble(123.0) * doubledouble::negnan(), 123.0 * negnan);
            COMPARE (doubledouble(123.0) * doubledouble::posinf(), 123.0 * posinf);
            COMPARE (doubledouble(123.0) * doubledouble::neginf(), 123.0 * neginf);

            COMPARE (doubledouble(-123.0) * doubledouble(123.0), -123.0 * 123.0);
            COMPARE (doubledouble(-123.0) * doubledouble(-123.0), -123.0 * -123.0);
            COMPARE (doubledouble(-123.0) * doubledouble::posnan(), -123.0 * posnan);
            COMPARE (doubledouble(-123.0) * doubledouble::negnan(), -123.0 * negnan);
            COMPARE (doubledouble(-123.0) * doubledouble::posinf(), -123.0 * posinf);
            COMPARE (doubledouble(-123.0) * doubledouble::neginf(), -123.0 * neginf);

            COMPARE (doubledouble::posnan() * doubledouble(123.0), posnan * 123.0);
            COMPARE (doubledouble::posnan() * doubledouble(-123.0), posnan * -123.0);
            COMPARE (doubledouble::posnan() * doubledouble::posnan(), posnan * posnan);
            COMPARE (doubledouble::posnan() * doubledouble::negnan(), posnan * negnan);
            COMPARE (doubledouble::posnan() * doubledouble::posinf(), posnan * posinf);
            COMPARE (doubledouble::posnan() * doubledouble::neginf(), posnan * neginf);

            COMPARE (doubledouble::negnan() * doubledouble(123.0), negnan * 123.0);
            COMPARE (doubledouble::negnan() * doubledouble(-123.0), negnan * -123.0);
            COMPARE (doubledouble::negnan() * doubledouble::posnan(), negnan * posnan);
            COMPARE (doubledouble::negnan() * doubledouble::negnan(), negnan * negnan);
            COMPARE (doubledouble::negnan() * doubledouble::posinf(), negnan * posinf);
            COMPARE (doubledouble::negnan() * doubledouble::neginf(), negnan * neginf);

            COMPARE (doubledouble::posinf() * doubledouble(123.0), posinf * 123.0);
            COMPARE (doubledouble::posinf() * doubledouble(-123.0), posinf * -123.0);
            COMPARE (doubledouble::posinf() * doubledouble::posnan(), posinf * posnan);
            COMPARE (doubledouble::posinf() * doubledouble::negnan(), posinf * negnan);
            COMPARE (doubledouble::posinf() * doubledouble::posinf(), posinf * posinf);
            COMPARE (doubledouble::posinf() * doubledouble::neginf(), posinf * neginf);

            COMPARE (doubledouble::neginf() * doubledouble(123.0), neginf * 123.0);
            COMPARE (doubledouble::neginf() * doubledouble(-123.0), neginf * -123.0);
            COMPARE (doubledouble::neginf() * doubledouble::posnan(), neginf * posnan);
            COMPARE (doubledouble::neginf() * doubledouble::posinf(), neginf * posinf);
            COMPARE (doubledouble::neginf() * doubledouble::neginf(), neginf * neginf);
        }
    }

    SUBCASE("Division") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                auto x = rand_double(), y = rand_double();
                if (y == 0.0) continue;
                COMPARE ((doubledouble(x) / doubledouble(y)).to_float(), float(x / y));
            }
        }

        SUBCASE("Special cases") {

            COMPARE (doubledouble(123.0) / doubledouble(123.0), 123.0 / 123.0);
            COMPARE (doubledouble(123.0) / doubledouble(-123.0), 123.0 / -123.0);
            COMPARE (doubledouble(123.0) / doubledouble::posnan(), 123.0 / posnan);
            COMPARE (doubledouble(123.0) / doubledouble::negnan(), 123.0 / negnan);
            COMPARE (doubledouble(123.0) / doubledouble::posinf(), 123.0 / posinf);
            COMPARE (doubledouble(123.0) / doubledouble::neginf(), 123.0 / neginf);

            COMPARE (doubledouble(-123.0) / doubledouble(123.0), -123.0 / 123.0);
            COMPARE (doubledouble(-123.0) / doubledouble(-123.0), -123.0 / -123.0);
            COMPARE (doubledouble(-123.0) / doubledouble::posnan(), -123.0 / posnan);
            COMPARE (doubledouble(-123.0) / doubledouble::negnan(), -123.0 / negnan);
            COMPARE (doubledouble(-123.0) / doubledouble::posinf(), -123.0 / posinf);
            COMPARE (doubledouble(-123.0) / doubledouble::neginf(), -123.0 / neginf);

            COMPARE (doubledouble::posnan() / doubledouble(123.0), posnan / 123.0);
            COMPARE (doubledouble::posnan() / doubledouble(-123.0), posnan / -123.0);
            COMPARE (doubledouble::posnan() / doubledouble::posnan(), posnan / posnan);
            COMPARE (doubledouble::posnan() / doubledouble::negnan(), posnan / negnan);
            COMPARE (doubledouble::posnan() / doubledouble::posinf(), posnan / posinf);
            COMPARE (doubledouble::posnan() / doubledouble::neginf(), posnan / neginf);

            COMPARE (doubledouble::negnan() / doubledouble(123.0), negnan / 123.0);
            COMPARE (doubledouble::negnan() / doubledouble(-123.0), negnan / -123.0);
            COMPARE (doubledouble::negnan() / doubledouble::posnan(), negnan / posnan);
            COMPARE (doubledouble::negnan() / doubledouble::negnan(), negnan / negnan);
            COMPARE (doubledouble::negnan() / doubledouble::posinf(), negnan / posinf);
            COMPARE (doubledouble::negnan() / doubledouble::neginf(), negnan / neginf);

            COMPARE (doubledouble::posinf() / doubledouble(123.0), posinf / 123.0);
            COMPARE (doubledouble::posinf() / doubledouble(-123.0), posinf / -123.0);
            COMPARE (doubledouble::posinf() / doubledouble::posnan(), posinf / posnan);
            COMPARE (doubledouble::posinf() / doubledouble::negnan(), posinf / negnan);
            COMPARE (doubledouble::posinf() / doubledouble::posinf(), posinf / posinf);
            COMPARE (doubledouble::posinf() / doubledouble::neginf(), posinf / neginf);

            COMPARE (doubledouble::neginf() / doubledouble(123.0), neginf / 123.0);
            COMPARE (doubledouble::neginf() / doubledouble(-123.0), neginf / -123.0);
            COMPARE (doubledouble::neginf() / doubledouble::posnan(), neginf / posnan);
            COMPARE (doubledouble::neginf() / doubledouble::negnan(), neginf / negnan);
            COMPARE (doubledouble::neginf() / doubledouble::posinf(), neginf / posinf);
            COMPARE (doubledouble::neginf() / doubledouble::neginf(), neginf / neginf);
        }

        SUBCASE("Division by zero") {

            COMPARE (doubledouble(42.0) / 0.0, 42.0 / 0.0);
            COMPARE (doubledouble(-42.0) / 0.0, -42.0 / 0.0);
            COMPARE (doubledouble(0.0) / 0.0, 0.0 / 0.0);
            COMPARE (doubledouble::posnan() / 0.0, posnan / 0.0);
            COMPARE (doubledouble::negnan() / 0.0, negnan / 0.0);
            COMPARE (doubledouble::posinf() / 0.0, posinf / 0.0);
            COMPARE (doubledouble::neginf() / 0.0, neginf / 0.0);
        }
    }

    SUBCASE("Increment and decrement operators") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double();
            doubledouble dx(x);

            x++; dx++; COMPARE (dx.to_float(), (float)x);
            ++x; ++dx; COMPARE (dx.to_float(), (float)x);
            x--; dx--; COMPARE (dx.to_float(), (float)x);
            --x; --dx; COMPARE (dx.to_float(), (float)x);
        }
    }
}
