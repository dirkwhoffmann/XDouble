#include "main.h"

TEST_CASE("Quad-double tests") {

    /* This test case verifies that double-double types can be used as the base
     * type of another double-double type. Theoretically, this should lead to
     * ever growing accuracies. However, inserting a double-double type into
     * another double-double type causes precision problems when performing
     * certain calculations. At the moment, I am not sure where these precision
     * problems come from and how they can be avoided. Any help on this is
     * greatly appreciated.
     */

    // typedef Double<doubledouble> quaddouble;
    typedef Double<Double<Double<long double>>> quaddouble;

    srand(0);

    SUBCASE("Constructors") {

        quaddouble x1;
        quaddouble x2(1e-10);
        quaddouble x3(quaddouble::pi.h);
        quaddouble x4(quaddouble::pi.h, x2.h);
        quaddouble x5("3.1415");
        quaddouble x6("3", "1415");
        quaddouble x7 = quaddouble::nan();
        quaddouble x8 = quaddouble::inf();

        CHECK(x1.to_string(2) == "0.00");
        CHECK(x2.to_string(2) == "0.00");
        CHECK(x3.to_string(2) == "3.14");
        CHECK(x4.to_string(2) == "3.14");
        CHECK(x5.to_string(2) == "3.14");
        CHECK(x6.to_string(2) == "3.14");
        CHECK(x7.to_string(2) == "nan");
        CHECK(x8.to_string(2) == "inf");
    }

    SUBCASE("Conversion functions") {

        CHECK((int)quaddouble(3.14) == 3);
        CHECK((long)quaddouble(3.6) == 3);
        CHECK((long long)quaddouble(3.6) == 3);
        CHECK((float)quaddouble(3.5) == 3.5);
        CHECK((double)quaddouble(3.5) == 3.5);
        CHECK((long double)quaddouble(3.5) == 3.5);
        CHECK(quaddouble(3.1415).to_string(4) == "3.1415");
    }

    SUBCASE("Comparison operators") {

        auto pi = quaddouble::pi;
        auto e = quaddouble::e;

        CHECK(pi == pi);
        CHECK(pi != e);
        CHECK(e < pi);
        CHECK(e <= pi);
        CHECK(pi > e);
        CHECK(pi >= e);
    }

    SUBCASE("Arithmetic") {

        quaddouble x(3.14);

        CHECK(-x == quaddouble(-3.14));
        CHECK(x + x == quaddouble(6.28));
        CHECK(x + x == quaddouble(6.28));
        CHECK(x - x == quaddouble(0.0));
        CHECK(x * x > quaddouble(9.0));
        CHECK(x / x == quaddouble(1.0));
    }

    SUBCASE("Other functions") {

        quaddouble x(3.14);
        quaddouble y(2.0);
        int exp;

        CHECK(x.exp().isfinite());
        CHECK(x.frexp(&exp).isfinite());
        CHECK(x.frexp10(&exp).isfinite());
        CHECK(x.ldexp(2).isfinite());
        CHECK(x.ldexp10(2).isfinite());
        CHECK(x.log().isfinite());
        CHECK(x.log10().isfinite());
        CHECK(x.modf(&y).isfinite());
        CHECK(x.exp2().isfinite());
        CHECK(x.log2().isfinite());

        CHECK(x.pow(2).isfinite());
        CHECK(x.pow(y).isfinite());
        CHECK(x.sqr().isfinite());
        CHECK(x.sqrt().isfinite());
    }

    SUBCASE("Classification functions") {

        quaddouble x(3.14);

        CHECK(x.isfinite());
        CHECK(quaddouble::inf().isinf());
        CHECK(quaddouble::nan().isnan());
        CHECK(x.isnormal());
        CHECK(x.signbit() == 0);
        CHECK(!x.iszero());
        CHECK(!x.isone());
        CHECK(!x.isnegative());
    }
}
