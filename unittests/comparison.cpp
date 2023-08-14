#include "doctest.h"
#include "double-double.h"

TEST_CASE("Comparison") {
    
    SUBCASE("Less") {
        
        SUBCASE("double") {
            
            doubledouble x = 1.0;
            doubledouble y = 2.0;
            
            for (int i = 0; i < 100; i++, x += .1, y -= .1) {
                
                CHECK((x < y) == ((double)x < (double)y));
            }
        }
        SUBCASE("long double") {
            
            longdoubledouble x = 1.0;
            longdoubledouble y = 2.0;

            for (int i = 0; i < 100; i++, x += .1, y -= .1) {

                CHECK((x < y) == ((long double)x < (long double)y));
            }
        }
    }

    SUBCASE("Less or equal") {

        SUBCASE("double") {

            doubledouble x = 1.0;
            doubledouble y = 2.0;

            for (int i = 0; i < 100; i++, x += .1, y -= .1) {

                CHECK((x <= y) == ((double)x <= (double)y));
            }
        }
        SUBCASE("long double") {

            longdoubledouble x = 1.0;
            longdoubledouble y = 2.0;

            for (int i = 0; i < 100; i++, x += .1, y -= .1) {

                CHECK((x <= y) == ((long double)x <= (long double)y));
            }
        }
    }
}
