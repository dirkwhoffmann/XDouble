include "doctest.h"
#include "double-double.h"

TEST_CASE("Basic smoke tests") {

    SUBCASE("Exponential function") {

        doubledouble x = 2.25;

        CHECK(doubledouble().to_double() == 0.0);
        CHECK(doubledouble(0.5).to_double() == 0.5);
        CHECK(doubledouble(0.5,0.125).to_double() == 0.625);
        CHECK(doubledouble(x).to_double() == 2.25);
        CHECK(doubledouble("3.5").to_double() == 3.5);
        CHECK(doubledouble("-3.5").to_double() == -3.5);
    }

    SUBCASE("Converting to different types") {

        CHECK(doubledouble(0.5).to_int() == 0);
        CHECK(doubledouble(3.14).to_int() == 3);
        CHECK(doubledouble(-3.14).to_int() == -3);

        CHECK(doubledouble(0.5).to_long() == 0);
        CHECK(doubledouble(3.14).to_long() == 3);
        CHECK(doubledouble(-3.14).to_long() == -3);

        CHECK(doubledouble(0).to_float() == 0.0f);
        CHECK(doubledouble(0.5).to_float() == 0.5f);
        CHECK(doubledouble(0.5,0.125).to_float() == 0.625f);

        CHECK(doubledouble(0).to_double() == 0.0);
        CHECK(doubledouble(0.5).to_double() == 0.5);
        CHECK(doubledouble(-0.5).to_double() == -0.5);
        CHECK(doubledouble(0.5,0.125).to_double() == 0.625);
        CHECK(doubledouble(-0.5,-0.125).to_double() == -0.625);

        CHECK(doubledouble(0).to_long_double() == 0.0L);
        CHECK(doubledouble(0.5).to_long_double() == 0.5L);
        CHECK(doubledouble(-0.5).to_long_double() == -0.5L);
        CHECK(doubledouble(0.5,0.125).to_long_double() == 0.625L);
        CHECK(doubledouble(-0.5,-0.125).to_long_double() == -0.625L);
    }
}
