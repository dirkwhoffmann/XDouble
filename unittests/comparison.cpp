#include "doctest.h"
#include "double-double.h"

TEST_CASE("Comparison") {
    
    SUBCASE("Less") {
        
        SUBCASE("double") {
            
            doubledouble x = 1.0;
            doubledouble y = 2.0;
            
            for (int i = 0; i < 100; i++, x += .1, y -= .1) {
                
                CHECK((x < y) == (x.asDouble() < y.asDouble()));
            }
        }
        SUBCASE("long double") {
            
            longdoubledouble x = 1.0;
            longdoubledouble y = 2.0;

            for (int i = 0; i < 100; i++, x += .1, y -= .1) {

                CHECK((x < y) == (x.asLongDouble() < y.asLongDouble()));
            }
        }
    }
}
