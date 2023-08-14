#include "doctest.h"
#include "double-double.h"

TEST_CASE("Basic smoke tests") {

    SUBCASE("Constructing") {

        doubledouble x = 2.25;

        CHECK(doubledouble() == doubledouble("0"));
        CHECK(doubledouble(0.5) == doubledouble("0.5"));
        CHECK(doubledouble(0.5,0.125) == doubledouble("0.125"));
        CHECK(doubledouble(x) == doubledouble("2.25"));
    }

    SUBCASE("Casting to different types") {

        CHECK((int)doubledouble(0.5) == 0);
        CHECK((int)doubledouble(3.14) == 3);
        CHECK((int)doubledouble(-3.14) == -3);

        CHECK((long)doubledouble(0.5) == 0);
        CHECK((long)doubledouble(3.14) == 3);
        CHECK((long)doubledouble(-3.14) == -3);

        CHECK((float)doubledouble(0) == 0.0f);
        CHECK((float)doubledouble(0.5) == 0.5f);
        CHECK((float)doubledouble(0.5,0.125) == 0.625f);

        CHECK((double)doubledouble(0) == 0.0);
        CHECK((double)doubledouble(0.5) == 0.5);
        CHECK((double)doubledouble(0.5,0.125) == 0.625);

        CHECK((long double)doubledouble(0) == 0.0L);
        CHECK((long double)doubledouble(0.5) == 0.5L);
        CHECK((long double)doubledouble(0.5,0.125) == 0.625L);
    }

    SUBCASE("Converting to textual representations") {

        doubledouble pi = 3.14159265;

        CHECK(pi.to_string(1) == "3.1");
        CHECK(pi.to_string(2) == "3.14");
        CHECK(pi.to_string(3) == "3.141");
        CHECK(pi.to_string(4) == "3.1415");
        CHECK(pi.to_string(5) == "3.14159");
    }

    SUBCASE("Parsing strings") {
        
        doubledouble pi("3.14159265358979323846264338327950");
        CHECK(pi.to_string(32) == "3.14159265358979323846264338327950");
    }
}
