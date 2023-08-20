#include "main.h"
#include <numbers>

TEST_CASE("Constants") {

    SUBCASE("float") {

        CHECK(doublefloat::e.to_string(14)              == "2.71828182845904");
        CHECK(doublefloat::log2e.to_string(14)          == "1.44269504088896");
        CHECK(doublefloat::log10e.to_string(14)         == "0.43429448190325");
        CHECK(doublefloat::pi.to_string(14)             == "3.14159265358979");
        CHECK(doublefloat::inv_pi.to_string(14)         == "0.31830988618379");
        CHECK(doublefloat::inv_sqrtpi.to_string(14)     == "0.56418958354775");
        CHECK(doublefloat::ln2.to_string(14)            == "0.69314718055994");
        CHECK(doublefloat::ln10.to_string(14)           == "2.30258509299404");
        CHECK(doublefloat::sqrt2.to_string(14)          == "1.41421356237309");
        CHECK(doublefloat::inv_sqrt3.to_string(14)      == "0.57735026918962");
        CHECK(doublefloat::egamma.to_string(14)         == "0.57721566490153");
        CHECK(doublefloat::phi.to_string(14)            == "1.61803398874989");
    }

    SUBCASE("double") {

        CHECK(doubledouble::e.to_string(30)             == "2.718281828459045235360287471352");
        CHECK(doubledouble::log2e.to_string(30)         == "1.442695040888963407359924681001");
        CHECK(doubledouble::log10e.to_string(30)        == "0.434294481903251827651128918916");
        CHECK(doubledouble::pi.to_string(30)            == "3.141592653589793238462643383279");
        CHECK(doubledouble::inv_pi.to_string(30)        == "0.318309886183790671537767526745");
        CHECK(doubledouble::inv_sqrtpi.to_string(30)    == "0.564189583547756286948079451560");
        CHECK(doubledouble::ln2.to_string(30)           == "0.693147180559945309417232121458");
        CHECK(doubledouble::ln10.to_string(30)          == "2.302585092994045684017991454684");
        CHECK(doubledouble::sqrt2.to_string(30)         == "1.414213562373095048801688724209");
        CHECK(doubledouble::inv_sqrt3.to_string(30)     == "0.577350269189625764509148780501");
        CHECK(doubledouble::egamma.to_string(30)        == "0.577215664901532860606512090082");
        CHECK(doubledouble::phi.to_string(30)           == "1.618033988749894848204586834365");
    }

}
