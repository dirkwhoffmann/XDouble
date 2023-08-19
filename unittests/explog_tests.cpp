#include "main.h"

TEST_CASE("Exponential and logarithmic functions") {

    srand(0);
    
    SUBCASE("exp") {


        CHECK(doubledouble("0"   ).exp().to_string(30) == "1.000000000000000000000000000000");
        CHECK(doubledouble("0.1" ).exp().to_string(30) == "1.105170918075647624811707826490");
        CHECK(doubledouble("0.5" ).exp().to_string(30) == "1.648721270700128146848650787814");
        CHECK(doubledouble("-0.1").exp().to_string(30) ==  ".904837418035959573164249059446");
        CHECK(doubledouble("-0.5").exp().to_string(30) ==  ".606530659712633423603799534991");

        doubledouble q1 = doubledouble("0.1" ).exp();
        quaddouble q2 = quaddouble("0.1" ).exp();

        printf("q1 :: %s\n", q1.to_string(40).c_str());
        printf("q2 :: %s\n", q2.to_string(40).c_str());
         
        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            CHECK(doubledouble(x).exp().to_float() == (float)std::exp(x));
        }
    }

    SUBCASE("frexp") {

        for (int i = 0; i < NUM_TESTS; i++) {

            int e1, e2;
            double x = rand_double();
            CHECK(doubledouble(x).frexp(&e1).to_float() == (float)std::frexp(x, &e2));
            CHECK(e1 == e2);
        }
    }

    SUBCASE("frexp10") {

        int e;

        CHECK(doubledouble(3141.5).frexp10(&e).to_float() == (float)0.31415);
        CHECK(e == 4);
        CHECK(doubledouble(314.15).frexp10(&e).to_float() == (float)0.31415);
        CHECK(e == 3);
        CHECK(doubledouble(31.415).frexp10(&e).to_float() == (float)0.31415);
        CHECK(e == 2);
        CHECK(doubledouble(3.1415).frexp10(&e).to_float() == (float)0.31415);
        CHECK(e == 1);
        CHECK(doubledouble(0.3141).frexp10(&e).to_float() == (float)0.3141);
        CHECK(e == 0);
        CHECK(doubledouble(0.0314).frexp10(&e).to_float() == (float)0.314);
        CHECK(e == -1);
        CHECK(doubledouble(0.0031).frexp10(&e).to_float() == (float)0.31);
        CHECK(e == -2);
        CHECK(doubledouble(0.0003).frexp10(&e).to_float() == (float)0.3);
        CHECK(e == -3);
        CHECK(doubledouble(0.0000).frexp10(&e).to_float() == (float)0);
        CHECK(e == 0);

        CHECK(doubledouble(-3141.5).frexp10(&e).to_float() == (float)-0.31415);
        CHECK(e == 4);
        CHECK(doubledouble(-314.15).frexp10(&e).to_float() == (float)-0.31415);
        CHECK(e == 3);
        CHECK(doubledouble(-31.415).frexp10(&e).to_float() == (float)-0.31415);
        CHECK(e == 2);
        CHECK(doubledouble(-3.1415).frexp10(&e).to_float() == (float)-0.31415);
        CHECK(e == 1);
        CHECK(doubledouble(-0.3141).frexp10(&e).to_float() == (float)-0.3141);
        CHECK(e == 0);
        CHECK(doubledouble(-0.0314).frexp10(&e).to_float() == (float)-0.314);
        CHECK(e == -1);
        CHECK(doubledouble(-0.0031).frexp10(&e).to_float() == (float)-0.31);
        CHECK(e == -2);
        CHECK(doubledouble(-0.0003).frexp10(&e).to_float() == (float)-0.3);
        CHECK(e == -3);
        CHECK(doubledouble(-0.0000).frexp10(&e).to_float() == (float)-0);
        CHECK(e == 0);
    }

    SUBCASE("ldexp") {

        for (int i = 0; i < NUM_TESTS; i++) {

            int e = rand();
            double x = rand_double();
            CHECK(doubledouble(x).ldexp(e).to_float() == (float)std::ldexp(x, e));
        }
    }

    SUBCASE("ldexp10") {

        doubledouble pi(3.1415);

        CHECK(pi.ldexp10(0).to_float() == (float)3.1415);
        CHECK(pi.ldexp10(1).to_float() == (float)31.415);
        CHECK(pi.ldexp10(2).to_float() == (float)314.15);
        CHECK(pi.ldexp10(3).to_float() == (float)3141.5);
        CHECK(pi.ldexp10(4).to_float() == (float)31415);
        CHECK(pi.ldexp10(5).to_float() == (float)314150);
    }

    SUBCASE("log") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double_pos();
            CHECK(doubledouble(x).log().to_float() == (float)std::log(x));
        }
    }

    SUBCASE("log10") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double_pos();
            CHECK(doubledouble(x).log10().to_float() == (float)std::log10(x));
        }
    }

    SUBCASE("modf") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double_pos();
            doubledouble i1; double i2;
            CHECK(doubledouble(x).modf(&i1).to_float() == (float)std::modf(x, &i2));
            CHECK((float)i1 == (float)i2);
        }
    }
}
