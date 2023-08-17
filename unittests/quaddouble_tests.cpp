#include "main.h"

TEST_CASE("Quad-double tests") {

    srand(0);

    SUBCASE("Experimental") {

        Double<doubledouble> x = Double<doubledouble>(3.15);
        x.ceil();
        
        CHECK(doubledouble(0.0).isfinite() == std::isfinite(0.0));
    }
}
