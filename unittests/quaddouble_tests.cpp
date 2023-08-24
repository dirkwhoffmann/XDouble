#include "main.h"

TEST_CASE("Quad-double tests") {

    /* This test case verifies that XDouble types can be defines with other
     * XDouble types as base types. Theoretically, this should lead to ever
     * growing accuracies. However, building an XDouble type on top of another
     * XDouble type causes precision problems when performing certain
     * calculations. At the moment, I am unsure where those precision problems
     * come from and how they can be tackled. Any help on this issue is highly
     * appreciated.
     */

    typedef XDouble<XDouble<XDouble<long double>>> multidouble;

    srand(0);

    SUBCASE("Constructors") {

        multidouble x1;
        multidouble x2(1e-10);
        multidouble x3(multidouble::pi.h);
        multidouble x4(multidouble::pi.h, x2.h);
        multidouble x5("3.1415");
        multidouble x6("3", "1415");
        multidouble x7 = multidouble::nan();
        multidouble x8 = multidouble::inf();

        CHECK (x1.to_string(2) == "0.00");
        CHECK (x2.to_string(2) == "0.00");
        CHECK (x3.to_string(2) == "3.14");
        CHECK (x4.to_string(2) == "3.14");
        CHECK (x5.to_string(2) == "3.14");
        CHECK (x6.to_string(2) == "3.14");
        CHECK (x7.to_string(2) == "nan");
        CHECK (x8.to_string(2) == "inf");
    }

    SUBCASE("Conversion functions") {

        CHECK ((int)multidouble(3.14) == 3);
        CHECK ((long)multidouble(3.6) == 3);
        CHECK ((long long)multidouble(3.6) == 3);
        CHECK ((float)multidouble(3.5) == 3.5);
        CHECK ((double)multidouble(3.5) == 3.5);
        CHECK ((long double)multidouble(3.5) == 3.5);
        CHECK (multidouble(3.1415).to_string(4) == "3.1415");
    }

    SUBCASE("Comparison operators") {

        auto pi = multidouble::pi;
        auto e = multidouble::e;

        CHECK (pi == pi);
        CHECK (pi != e);
        CHECK (e < pi);
        CHECK (e <= pi);
        CHECK (pi > e);
        CHECK (pi >= e);
    }

    SUBCASE("Arithmetic") {

        multidouble x(3.14);

        CHECK (-x == multidouble(-3.14));
        CHECK (x + x == multidouble(6.28));
        CHECK (x + x == multidouble(6.28));
        CHECK (x - x == multidouble(0.0));
        CHECK (x * x > multidouble(9.0));
        CHECK (x / x == multidouble(1.0));
    }

    SUBCASE("Other functions") {

        multidouble x(3.14);
        multidouble y(2.0);
        int exp;

        CHECK (x.exp().isfinite());
        CHECK (x.frexp(&exp).isfinite());
        CHECK (x.frexp10(&exp).isfinite());
        CHECK (x.ldexp(2).isfinite());
        CHECK (x.ldexp10(2).isfinite());
        CHECK (x.log().isfinite());
        CHECK (x.log10().isfinite());
        CHECK (x.modf(&y).isfinite());
        CHECK (x.exp2().isfinite());
        CHECK (x.log2().isfinite());

        CHECK (x.pow(2).isfinite());
        CHECK (x.pow(y).isfinite());
        CHECK (x.sqr().isfinite());
        CHECK (x.sqrt().isfinite());
    }

    SUBCASE("Classification functions") {

        multidouble x(3.14);

        CHECK (x.isfinite());
        CHECK (multidouble::inf().isinf());
        CHECK (multidouble::nan().isnan());
        CHECK (x.isnormal());
        CHECK (!x.signbit());
        CHECK (!x.iszero());
        CHECK (!x.isone());
        CHECK (!x.isnegative());
    }
}
