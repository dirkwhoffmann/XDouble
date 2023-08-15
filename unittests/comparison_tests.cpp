#include "main.h"

TEST_CASE("Comparison") {

    struct {
        const char *x; const char *y;
        bool eq; bool neq; bool l; bool g; bool le; bool ge; } p[] = {

            { "0",      "0",        true,   false,  false,  false,  true,   true  },
            { "3.14",   "3.14",     true,   false,  false,  false,  true,   true  },
            { "-3.14",  "-3.14",    true,   false,  false,  false,  true,   true  },
            { "42",     "42.1",     false,  true,   true,   false,  true,   false },
            { "42.1",   "42",       false,  true,   false,  true,   false,  true  },
            { "-42",    "-42.1",    false,  true,   false,  true,   false,  true  },
            { "-42.1",  "-42",      false,  true,   true,   false,  true,   false },
            { "",       "",         0,      0,      0,      0,      0,      0     }
    };

    SUBCASE("Equal") {

        for (int i = 0; p[i].x[0]; i++) {
            CHECK ((doubledouble(p[i].x) == doubledouble(p[i].y)) == p[i].eq);
        }
        CHECK (!(doubledouble::nan() == doubledouble(0)));
        CHECK (!(doubledouble(0)     == doubledouble::nan()));
        CHECK (!(doubledouble::nan() == doubledouble::nan()));
    }
    SUBCASE("Unequal") {

        for (int i = 0; p[i].x[0]; i++) {
            CHECK ((doubledouble(p[i].x) != doubledouble(p[i].y)) == p[i].neq);
        }
        CHECK (doubledouble::nan() != doubledouble(0));
        CHECK (doubledouble(0)     != doubledouble::nan());
        CHECK (doubledouble::nan() != doubledouble::nan());
    }
    SUBCASE("Less") {

        for (int i = 0; p[i].x[0]; i++) {
            CHECK ((doubledouble(p[i].x) < doubledouble(p[i].y)) == p[i].l);
        }
        CHECK (!(doubledouble::nan() < doubledouble(0)));
        CHECK (!(doubledouble(0)     < doubledouble::nan()));
        CHECK (!(doubledouble::nan() < doubledouble::nan()));
    }
    SUBCASE("Greater") {

        for (int i = 0; p[i].x[0]; i++) {
            CHECK ((doubledouble(p[i].x) > doubledouble(p[i].y)) == p[i].g);
        }
        CHECK (!(doubledouble::nan() > doubledouble(0)));
        CHECK (!(doubledouble(0)     > doubledouble::nan()));
        CHECK (!(doubledouble::nan() > doubledouble::nan()));
    }
    SUBCASE("Less or equal") {

        for (int i = 0; p[i].x[0]; i++) {
            CHECK ((doubledouble(p[i].x) <= doubledouble(p[i].y)) == p[i].le);
        }
        CHECK (!(doubledouble::nan() <= doubledouble(0)));
        CHECK (!(doubledouble(0)     <= doubledouble::nan()));
        CHECK (!(doubledouble::nan() <= doubledouble::nan()));
    }
    SUBCASE("Greater or equal") {

        for (int i = 0; p[i].x[0]; i++) {
            CHECK ((doubledouble(p[i].x) >= doubledouble(p[i].y)) == p[i].ge);
        }
        CHECK (!(doubledouble::nan() >= doubledouble(0)));
        CHECK (!(doubledouble(0)     >= doubledouble::nan()));
        CHECK (!(doubledouble::nan() >= doubledouble::nan()));
    }
}
