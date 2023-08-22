#include "main.h"

#define FUNC(x) [](){ x }

TEST_CASE("Error flags") {

    std::pair<fexcept_t, fexcept_t> flags;

    SUBCASE("division by zero") {

        flags = execute(FUNC( (void)(2.0 / 0.0); ),
                        FUNC( (void)(doubledouble(2.0) / 0.0); ));
        CHECK(flags.first == flags.second);
    }

    SUBCASE("log") {

        flags = execute(FUNC( (void)log(-2.0); ),
                        FUNC( (void)log(doubledouble(-2.0)); ));
        CHECK(flags.first == flags.second);

        flags = execute(FUNC( (void)log(0.0); ),
                        FUNC( (void)log(doubledouble(0.0)); ));
        CHECK(flags.first == flags.second);

        flags = execute(FUNC( (void)log10(-2.0); ),
                        FUNC( (void)log10(doubledouble(-2.0)); ));
        CHECK(flags.first == flags.second);

        flags = execute(FUNC( (void)log10(0.0); ),
                        FUNC( (void)log10(doubledouble(0.0)); ));
        CHECK(flags.first == flags.second);
    }

    SUBCASE("pow") {

        flags = execute(FUNC( (void)pow(-2.0, 2.5); ),
                        FUNC( (void)pow(doubledouble(-2.0), doubledouble(2.5)); ));
        CHECK(flags.first == flags.second);

        flags = execute(FUNC( (void)pow(0, 0); ),
                        FUNC( (void)pow(doubledouble(0), doubledouble(0)); ));
        CHECK(flags.first == flags.second);

        flags = execute(FUNC( (void)pow(0, -2); ),
                        FUNC( (void)pow(doubledouble(0), doubledouble(-2)); ));
        CHECK(flags.first == flags.second);
    }

    SUBCASE("sqrt") {

        flags = execute(FUNC( (void)sqrt(-2.0); ),
                        FUNC( (void)sqrt(doubledouble(-2.0)); ));
        CHECK(flags.first == flags.second);
    }
}
