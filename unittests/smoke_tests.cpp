#include "main.h"

TEST_CASE("Basic smoke tests") {

    SUBCASE("Constructing") {

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

    SUBCASE("Converting to textual representations") {

        doubledouble pi = 3.14159265;

        CHECK(pi.to_string(0) == "3");
        CHECK(pi.to_string(1) == "3.1");
        CHECK(pi.to_string(2) == "3.14");
        CHECK(pi.to_string(3) == "3.141");
        CHECK(pi.to_string(4) == "3.1415");
        CHECK(pi.to_string(5) == "3.14159");

        doubledouble me = -2.71828182;

        CHECK(me.to_string(0) == "-2");
        CHECK(me.to_string(1) == "-2.7");
        CHECK(me.to_string(2) == "-2.71");
        CHECK(me.to_string(3) == "-2.718");
        CHECK(me.to_string(4) == "-2.7182");
        CHECK(me.to_string(5) == "-2.71828");

        
        doubledouble pi2("3.14159265358979323846264338327950");
        CHECK(pi2.to_string(32) == "3.14159265358979323846264338327950");

        doubledouble me2("-2.71828182845904523536028747135266");
        CHECK(me2.to_string(32) == "-2.71828182845904523536028747135266");
    }
}
