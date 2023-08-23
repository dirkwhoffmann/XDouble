#include "main.h"

TEST_CASE("Exponential and logarithmic functions") {

    srand(0);
    
    SUBCASE("exp") {

        CHECK (doubledouble("0"   ).exp().to_string(30) == "1.000000000000000000000000000000");
        CHECK (doubledouble("0.1" ).exp().to_string(30) == "1.105170918075647624811707826490");
        CHECK (doubledouble("0.5" ).exp().to_string(30) == "1.648721270700128146848650787814");
        CHECK (doubledouble("-0.1").exp().to_string(30) == "0.904837418035959573164249059446");
        CHECK (doubledouble("-0.5").exp().to_string(30) == "0.606530659712633423603799534991");

        COMPARE (doubledouble::nan().exp(), posnan);
        COMPARE (doubledouble::posinf().exp(), posinf);
        COMPARE (doubledouble::neginf().exp(), 0.0);

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            COMPARE (doubledouble(x).exp().to_float(), (float)std::exp(x));
        }
    }

    SUBCASE("frexp") {

        int e1 = 0, e2 = 0;

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double();
            COMPARE (doubledouble(x).frexp(&e1).to_float(), (float)std::frexp(x, &e2));
            CHECK (e1 == e2);
        }

        e1 = 0;
        COMPARE (doubledouble::nan().frexp(&e1), posnan);
        CHECK   (e1 == 0);
        COMPARE (doubledouble::posinf().frexp(&e1), posinf);
        CHECK   (e1 == 0);
        COMPARE (doubledouble::neginf().frexp(&e1), neginf);
        CHECK   (e1 == 0);
    }

    SUBCASE("frexp10") {

        int e;

        COMPARE (doubledouble(3141.5).frexp10(&e).to_float(), (float)0.31415);
        CHECK   (e == 4);
        COMPARE (doubledouble(314.15).frexp10(&e).to_float(), (float)0.31415);
        CHECK(   e == 3);
        COMPARE (doubledouble(31.415).frexp10(&e).to_float(), (float)0.31415);
        CHECK   (e == 2);
        COMPARE (doubledouble(3.1415).frexp10(&e).to_float(), (float)0.31415);
        CHECK   (e == 1);
        COMPARE (doubledouble(0.3141).frexp10(&e).to_float(), (float)0.3141);
        CHECK   (e == 0);
        COMPARE (doubledouble(0.0314).frexp10(&e).to_float(), (float)0.314);
        CHECK   (e == -1);
        COMPARE (doubledouble(0.0031).frexp10(&e).to_float(), (float)0.31);
        CHECK   (e == -2);
        COMPARE (doubledouble(0.0003).frexp10(&e).to_float(), (float)0.3);
        CHECK   (e == -3);
        COMPARE (doubledouble(0.0000).frexp10(&e).to_float(), (float)0);
        CHECK   (e == 0);

        COMPARE (doubledouble(-3141.5).frexp10(&e).to_float(), (float)-0.31415);
        CHECK   (e == 4);
        COMPARE (doubledouble(-314.15).frexp10(&e).to_float(), (float)-0.31415);
        CHECK   (e == 3);
        COMPARE (doubledouble(-31.415).frexp10(&e).to_float(), (float)-0.31415);
        CHECK   (e == 2);
        COMPARE (doubledouble(-3.1415).frexp10(&e).to_float(), (float)-0.31415);
        CHECK   (e == 1);
        COMPARE (doubledouble(-0.3141).frexp10(&e).to_float(), (float)-0.3141);
        CHECK   (e == 0);
        COMPARE (doubledouble(-0.0314).frexp10(&e).to_float(), (float)-0.314);
        CHECK   (e == -1);
        COMPARE (doubledouble(-0.0031).frexp10(&e).to_float(), (float)-0.31);
        CHECK   (e == -2);
        COMPARE (doubledouble(-0.0003).frexp10(&e).to_float(), (float)-0.3);
        CHECK   (e == -3);
        COMPARE (doubledouble(-0.0000).frexp10(&e).to_float(), (float)-0);
        CHECK   (e == 0);

        e = 42;
        COMPARE (doubledouble::nan().frexp10(&e), posnan);
        CHECK   (e == 0);
        e = 42;
        COMPARE (doubledouble::posinf().frexp10(&e), posinf);
        CHECK   (e == 0);
        e = 42;
        COMPARE (doubledouble::neginf().frexp10(&e), neginf);
        CHECK   (e == 0);
    }

    SUBCASE("ldexp") {

        for (int i = 0; i < NUM_TESTS; i++) {

            int e = rand();
            double x = rand_double();
            COMPARE (doubledouble(x).ldexp(e).to_float(), (float)std::ldexp(x, e));
        }

        COMPARE (doubledouble::nan().ldexp(2), posnan);
        COMPARE (doubledouble::posinf().ldexp(2), posinf);
        COMPARE (doubledouble::neginf().ldexp(2), neginf);
    }

    SUBCASE("ldexp10") {

        doubledouble pi(3.1415);

        COMPARE (pi.ldexp10(0).to_float(), (float)3.1415);
        COMPARE (pi.ldexp10(1).to_float(), (float)31.415);
        COMPARE (pi.ldexp10(2).to_float(), (float)314.15);
        COMPARE (pi.ldexp10(3).to_float(), (float)3141.5);
        COMPARE (pi.ldexp10(4).to_float(), (float)31415);
        COMPARE (pi.ldexp10(5).to_float(), (float)314150);

        COMPARE (doubledouble::nan().ldexp10(2), posnan);
        COMPARE (doubledouble::posinf().ldexp10(2), posinf);
        COMPARE (doubledouble::neginf().ldexp10(2), neginf);
    }

    SUBCASE("log") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double_pos();
            COMPARE (doubledouble(x).log().to_float(), (float)std::log(x));
        }

        COMPARE (doubledouble(0.0).log(), std::log(0.0));
        COMPARE (doubledouble(1.0).log(), std::log(1.0));
        COMPARE (doubledouble(-.5).log(), std::log(-.5));
        COMPARE (doubledouble::posinf().log(), std::log(posinf));
        COMPARE (doubledouble::neginf().log(), std::log(neginf));
        COMPARE (doubledouble::posnan().log(), std::log(posnan));
        COMPARE (doubledouble::negnan().log(), std::log(negnan));
    }

    SUBCASE("log10") {

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double_pos();
            COMPARE (doubledouble(x).log10().to_float(), (float)std::log10(x));
        }
    }

    SUBCASE("modf") {

        doubledouble i1; double i2 = 0.0;

        for (int i = 0; i < NUM_TESTS; i++) {

            double x = rand_double_pos();
            COMPARE (doubledouble(x).modf(&i1).to_float(), (float)std::modf(x, &i2));
            COMPARE ((float)i1, (float)i2);
        }

        COMPARE (doubledouble::posinf().modf(&i1).to_float(), std::modf(posinf, &i2));
        COMPARE (doubledouble::neginf().modf(&i1).to_float(), std::modf(neginf, &i2));
        COMPARE (doubledouble::posnan().modf(&i1).to_float(), std::modf(posnan, &i2));
        COMPARE (doubledouble::negnan().modf(&i1).to_float(), std::modf(negnan, &i2));
    }
}
