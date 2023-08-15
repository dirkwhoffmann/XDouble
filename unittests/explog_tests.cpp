#include "doctest.h"
#include "double-double.h"

TEST_CASE("Exponential and logarithmic functions") {

    SUBCASE("exp") {

        CHECK(doubledouble("0"   ).exp().to_string(30) == "1.000000000000000000000000000000");
        CHECK(doubledouble("0.1" ).exp().to_string(30) == "1.105170918075647624811707826490");
        CHECK(doubledouble("0.5" ).exp().to_string(30) == "1.648721270700128146848650787814");
        CHECK(doubledouble("-0.1").exp().to_string(30) ==  ".904837418035959573164249059446");
        CHECK(doubledouble("-0.5").exp().to_string(30) ==  ".606530659712633423603799534991");
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
