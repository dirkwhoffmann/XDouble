#include "doctest.h"
#include "double-double.h"

TEST_CASE("Running basic tests") {

    doubledouble d;

    CHECK(d.getFoo() != 42);
}
