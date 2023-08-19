#include "main.h"

TEST_CASE("Basic arithmetic") {

    srand(0);

    SUBCASE("Negation") {

        CHECK(-doubledouble(42.0).to_double() == -42.0);
        CHECK(-doubledouble(-42.0).to_double() == 42.0);
    }

    SUBCASE("Addition") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                auto x = rand_double(), y = rand_double();
                CHECK((doubledouble(x) + doubledouble(y)).to_float() == float(x + y));
            }
        }

        SUBCASE("Special cases") {

            CHECK((doubledouble(123.0) + doubledouble(123.0)).isfinite());
            CHECK((doubledouble(123.0) + doubledouble(-123.0)).isfinite());
            CHECK((doubledouble(123.0) + doubledouble::nan()).isnan());
            CHECK((doubledouble(123.0) + doubledouble::inf()).isinf());
            CHECK((doubledouble(123.0) + -doubledouble::inf()).isinf());

            CHECK((doubledouble(-123.0) + doubledouble(123.0)).isfinite());
            CHECK((doubledouble(-123.0) + doubledouble(-123.0)).isfinite());
            CHECK((doubledouble(-123.0) + doubledouble::nan()).isnan());
            CHECK((doubledouble(-123.0) + doubledouble::inf()).isinf());
            CHECK((doubledouble(-123.0) + -doubledouble::inf()).isinf());

            CHECK((doubledouble::nan() + doubledouble(123.0)).isnan());
            CHECK((doubledouble::nan() + doubledouble(-123.0)).isnan());
            CHECK((doubledouble::nan() + doubledouble::nan()).isnan());
            CHECK((doubledouble::nan() + doubledouble::inf()).isnan());
            CHECK((doubledouble::nan() + -doubledouble::inf()).isnan());

            CHECK((doubledouble::inf() + doubledouble(123.0)).isinf());
            CHECK((doubledouble::inf() + doubledouble(-123.0)).isinf());
            CHECK((doubledouble::inf() + doubledouble::nan()).isnan());
            CHECK((doubledouble::inf() + doubledouble::inf()).isinf());
            CHECK((doubledouble::inf() + -doubledouble::inf()).isnan());

            CHECK((-doubledouble::inf() + doubledouble(123.0)).isinf());
            CHECK((-doubledouble::inf() + doubledouble(-123.0)).isinf());
            CHECK((-doubledouble::inf() + doubledouble::nan()).isnan());
            CHECK((-doubledouble::inf() + doubledouble::inf()).isnan());
            CHECK((-doubledouble::inf() + -doubledouble::inf()).isinf());

            CHECK((doubledouble(123.0) + doubledouble(123.0)).signbit() == 0);
            CHECK((doubledouble(123.0) + doubledouble(-123.0)).signbit() == 0);
            CHECK((doubledouble(123.0) + doubledouble::inf()).signbit() == 0);
            CHECK((doubledouble(123.0) + -doubledouble::inf()).signbit() == 1);

            CHECK((doubledouble(-123.0) + doubledouble(123.0)).signbit() == 0);
            CHECK((doubledouble(-123.0) + doubledouble(-123.0)).signbit() == 1);
            CHECK((doubledouble(-123.0) + doubledouble::inf()).signbit() == 0);
            CHECK((doubledouble(-123.0) + -doubledouble::inf()).signbit() == 1);

            CHECK((doubledouble::inf() + doubledouble(123.0)).signbit() == 0);
            CHECK((doubledouble::inf() + doubledouble(-123.0)).signbit() == 0);
            CHECK((doubledouble::inf() + doubledouble::inf()).signbit() == 0);

            CHECK((-doubledouble::inf() + doubledouble(123.0)).signbit() == 1);
            CHECK((-doubledouble::inf() + doubledouble(-123.0)).signbit() == 1);
            CHECK((-doubledouble::inf() + -doubledouble::inf()).signbit() == 1);
        }
    }

    SUBCASE("Subtraction") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                auto x = rand_double(), y = rand_double();
                CHECK((doubledouble(x) - doubledouble(y)).to_float() == float(x - y));
            }
        }

        SUBCASE("Special cases") {

            CHECK((doubledouble(123.0) - doubledouble(123.0)).isfinite());
            CHECK((doubledouble(123.0) - doubledouble(-123.0)).isfinite());
            CHECK((doubledouble(123.0) - doubledouble::nan()).isnan());
            CHECK((doubledouble(123.0) - doubledouble::inf()).isinf());
            CHECK((doubledouble(123.0) - -doubledouble::inf()).isinf());

            CHECK((doubledouble(-123.0) - doubledouble(123.0)).isfinite());
            CHECK((doubledouble(-123.0) - doubledouble(-123.0)).isfinite());
            CHECK((doubledouble(-123.0) - doubledouble::nan()).isnan());
            CHECK((doubledouble(-123.0) - doubledouble::inf()).isinf());
            CHECK((doubledouble(-123.0) - -doubledouble::inf()).isinf());

            CHECK((doubledouble::nan() - doubledouble(123.0)).isnan());
            CHECK((doubledouble::nan() - doubledouble(-123.0)).isnan());
            CHECK((doubledouble::nan() - doubledouble::nan()).isnan());
            CHECK((doubledouble::nan() - doubledouble::inf()).isnan());
            CHECK((doubledouble::nan() - -doubledouble::inf()).isnan());

            CHECK((doubledouble::inf() - doubledouble(123.0)).isinf());
            CHECK((doubledouble::inf() - doubledouble(-123.0)).isinf());
            CHECK((doubledouble::inf() - doubledouble::nan()).isnan());
            CHECK((doubledouble::inf() - doubledouble::inf()).isnan());
            CHECK((doubledouble::inf() - -doubledouble::inf()).isinf());

            CHECK((-doubledouble::inf() - doubledouble(123.0)).isinf());
            CHECK((-doubledouble::inf() - doubledouble(-123.0)).isinf());
            CHECK((-doubledouble::inf() - doubledouble::nan()).isnan());
            CHECK((-doubledouble::inf() - doubledouble::inf()).isinf());
            CHECK((-doubledouble::inf() - -doubledouble::inf()).isnan());

            CHECK((doubledouble(123.0) - doubledouble(123.0)).signbit() == 0);
            CHECK((doubledouble(123.0) - doubledouble(-123.0)).signbit() == 0);
            CHECK((doubledouble(123.0) - doubledouble::inf()).signbit() == 1);
            CHECK((doubledouble(123.0) - -doubledouble::inf()).signbit() == 0);

            CHECK((doubledouble(-123.0) - doubledouble(123.0)).signbit() == 1);
            CHECK((doubledouble(-123.0) - doubledouble(-123.0)).signbit() == 0);
            CHECK((doubledouble(-123.0) - doubledouble::inf()).signbit() == 1);
            CHECK((doubledouble(-123.0) - -doubledouble::inf()).signbit() == 0);

            CHECK((doubledouble::inf() - doubledouble(123.0)).signbit() == 0);
            CHECK((doubledouble::inf() - doubledouble(-123.0)).signbit() == 0);
            CHECK((doubledouble::inf() - -doubledouble::inf()).signbit() == 0);

            CHECK((-doubledouble::inf() + doubledouble(123.0)).signbit() == 1);
            CHECK((-doubledouble::inf() + doubledouble(-123.0)).signbit() == 1);
            CHECK((-doubledouble::inf() - doubledouble::inf()).signbit() == 1);
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

            CHECK((doubledouble(123.0) * doubledouble(123.0)).isfinite());
            CHECK((doubledouble(123.0) * doubledouble(-123.0)).isfinite());
            CHECK((doubledouble(123.0) * doubledouble::nan()).isnan());
            CHECK((doubledouble(123.0) * doubledouble::inf()).isinf());
            CHECK((doubledouble(123.0) * -doubledouble::inf()).isinf());

            CHECK((doubledouble(-123.0) * doubledouble(123.0)).isfinite());
            CHECK((doubledouble(-123.0) * doubledouble(-123.0)).isfinite());
            CHECK((doubledouble(-123.0) * doubledouble::nan()).isnan());
            CHECK((doubledouble(-123.0) * doubledouble::inf()).isinf());
            CHECK((doubledouble(-123.0) * -doubledouble::inf()).isinf());

            CHECK((doubledouble::nan() * doubledouble(123.0)).isnan());
            CHECK((doubledouble::nan() * doubledouble(-123.0)).isnan());
            CHECK((doubledouble::nan() * doubledouble::nan()).isnan());
            CHECK((doubledouble::nan() * doubledouble::inf()).isnan());
            CHECK((doubledouble::nan() * -doubledouble::inf()).isnan());

            CHECK((doubledouble::inf() * doubledouble(123.0)).isinf());
            CHECK((doubledouble::inf() * doubledouble(-123.0)).isinf());
            CHECK((doubledouble::inf() * doubledouble::nan()).isnan());
            CHECK((doubledouble::inf() * doubledouble::inf()).isinf());
            CHECK((doubledouble::inf() * -doubledouble::inf()).isinf());

            CHECK((-doubledouble::inf() * doubledouble(123.0)).isinf());
            CHECK((-doubledouble::inf() * doubledouble(-123.0)).isinf());
            CHECK((-doubledouble::inf() * doubledouble::nan()).isnan());
            CHECK((-doubledouble::inf() * doubledouble::inf()).isinf());
            CHECK((-doubledouble::inf() * -doubledouble::inf()).isinf());

            CHECK((doubledouble(123.0) * doubledouble(123.0)).signbit() == 0);
            CHECK((doubledouble(123.0) * doubledouble(-123.0)).signbit() == 1);
            CHECK((doubledouble(123.0) * doubledouble::inf()).signbit() == 0);
            CHECK((doubledouble(123.0) * -doubledouble::inf()).signbit() == 1);

            CHECK((doubledouble(-123.0) * doubledouble(123.0)).signbit() == 1);
            CHECK((doubledouble(-123.0) * doubledouble(-123.0)).signbit() == 0);
            CHECK((doubledouble(-123.0) * doubledouble::inf()).signbit() == 1);
            CHECK((doubledouble(-123.0) * -doubledouble::inf()).signbit() == 0);

            CHECK((doubledouble::inf() * doubledouble(123.0)).signbit() == 0);
            CHECK((doubledouble::inf() * doubledouble(-123.0)).signbit() == 1);
            CHECK((doubledouble::inf() * doubledouble::inf()).signbit() == 0);
            CHECK((doubledouble::inf() * -doubledouble::inf()).signbit() == 1);

            CHECK((-doubledouble::inf() * doubledouble(123.0)).signbit() == 1);
            CHECK((-doubledouble::inf() * doubledouble(-123.0)).signbit() == 0);
            CHECK((-doubledouble::inf() * doubledouble::inf()).signbit() == 1);
            CHECK((-doubledouble::inf() * -doubledouble::inf()).signbit() == 0);
        }
    }

    SUBCASE("Division") {

        SUBCASE("Standard cases") {

            for (int i = 0; i < NUM_TESTS; i++) {

                auto x = rand_double(), y = rand_double();
                if (y == 0.0) continue;
                CHECK((doubledouble(x) / doubledouble(y)).to_float() == float(x / y));
            }
        }

        SUBCASE("Special cases") {

            CHECK((doubledouble(123.0) / doubledouble(123.0)).isfinite());
            CHECK((doubledouble(123.0) / doubledouble(-123.0)).isfinite());
            CHECK((doubledouble(123.0) / doubledouble::nan()).isnan());
            CHECK((doubledouble(123.0) / doubledouble::inf()).iszero());
            CHECK((doubledouble(123.0) / -doubledouble::inf()).iszero());

            CHECK((doubledouble(-123.0) / doubledouble(123.0)).isfinite());
            CHECK((doubledouble(-123.0) / doubledouble(-123.0)).isfinite());
            CHECK((doubledouble(-123.0) / doubledouble::nan()).isnan());
            CHECK((doubledouble(-123.0) / doubledouble::inf()).iszero());
            CHECK((doubledouble(-123.0) / -doubledouble::inf()).iszero());

            CHECK((doubledouble::nan() / doubledouble(123.0)).isnan());
            CHECK((doubledouble::nan() / doubledouble(-123.0)).isnan());
            CHECK((doubledouble::nan() / doubledouble::nan()).isnan());
            CHECK((doubledouble::nan() / doubledouble::inf()).isnan());
            CHECK((doubledouble::nan() / -doubledouble::inf()).isnan());

            CHECK((doubledouble::inf() / doubledouble(123.0)).isinf());
            CHECK((doubledouble::inf() / doubledouble(-123.0)).isinf());
            CHECK((doubledouble::inf() / doubledouble::nan()).isnan());
            CHECK((doubledouble::inf() / doubledouble::inf()).isnan());
            CHECK((doubledouble::inf() / -doubledouble::inf()).isnan());

            CHECK((-doubledouble::inf() / doubledouble(123.0)).isinf());
            CHECK((-doubledouble::inf() / doubledouble(-123.0)).isinf());
            CHECK((-doubledouble::inf() / doubledouble::nan()).isnan());
            CHECK((-doubledouble::inf() / doubledouble::inf()).isnan());
            CHECK((-doubledouble::inf() / -doubledouble::inf()).isnan());

            CHECK((doubledouble(123.0) / doubledouble(123.0)).signbit() == 0);
            CHECK((doubledouble(123.0) / doubledouble(-123.0)).signbit() == 1);
            CHECK((doubledouble(123.0) / doubledouble::inf()).signbit() == 0);
            CHECK((doubledouble(123.0) / -doubledouble::inf()).signbit() == 1);

            CHECK((doubledouble(-123.0) / doubledouble(123.0)).signbit() == 1);
            CHECK((doubledouble(-123.0) / doubledouble(-123.0)).signbit() == 0);
            CHECK((doubledouble(-123.0) / doubledouble::inf()).signbit() == 1);
            CHECK((doubledouble(-123.0) / -doubledouble::inf()).signbit() == 0);

            CHECK((doubledouble::inf() / doubledouble(123.0)).signbit() == 0);
            CHECK((doubledouble::inf() / doubledouble(-123.0)).signbit() == 1);

            CHECK((-doubledouble::inf() / doubledouble(123.0)).signbit() == 1);
            CHECK((-doubledouble::inf() / doubledouble(-123.0)).signbit() == 0);
        }

        SUBCASE("Division by zero") {

            CHECK((doubledouble(42.0) / 0.0).isinf());
            CHECK((doubledouble(-42.0) / 0.0).isinf());
            CHECK(doubledouble(42.0) / 0.0 == doubledouble::inf());
            CHECK(doubledouble(42.0) / 0.0 != -doubledouble::inf());
            CHECK(doubledouble(-42.0) / 0.0 == -doubledouble::inf());
            CHECK(doubledouble(-42.0) / 0.0 != doubledouble::inf());
            CHECK((doubledouble(42.0) / 0.0).signbit() == 0);
            CHECK((doubledouble(-42.0) / 0.0).signbit() == 1);
            CHECK((doubledouble(0.0) / 0.0).isnan());
            CHECK((doubledouble::nan() / 0.0).isnan());
            CHECK((doubledouble::inf() / 0.0).isinf());
        }
    }

    SUBCASE("Increment and decrement operators") {

        for (int i = 0; i < NUM_TESTS; i++) {

            auto x = rand_double();
            doubledouble dx(x);

            x++; dx++; CHECK(dx.to_float() == (float)x);
            ++x; ++dx; CHECK(dx.to_float() == (float)x);
            x--; dx--; CHECK(dx.to_float() == (float)x);
            --x; --dx; CHECK(dx.to_float() == (float)x);
        }
    }
}
