#include "doctest.h"
#include "double-double.h"

TEST_CASE("Running more tests...") {

    doubledouble d;

    CHECK(d.getBar() == 84);
}
