#include "main.h"

TEST_CASE("Classification functions") {

    srand(0);

    SUBCASE("isfinite") {

        CHECK (doubledouble(0.0).isfinite() == std::isfinite(0.0));
        CHECK (doubledouble(-0.0).isfinite() == std::isfinite(-0.0));
        CHECK ((-doubledouble(0.0)).isfinite() == std::isfinite(-0.0));
        CHECK (doubledouble(42.0).isfinite() == std::isfinite(42.0));
        CHECK (doubledouble(-42.0).isfinite() == std::isfinite(-42.0));
        CHECK ((-doubledouble(42.0)).isfinite() == std::isfinite(-42.0));
        CHECK (doubledouble::posnan().isfinite() == std::isfinite(posnan));
        CHECK (doubledouble::negnan().isfinite() == std::isfinite(negnan));
        CHECK (doubledouble::posinf().isfinite() == std::isfinite(posinf));
        CHECK (doubledouble::neginf().isfinite() == std::isfinite(neginf));
    }

    SUBCASE("isinf") {

        CHECK (doubledouble(0.0).isinf() == std::isinf(0.0));
        CHECK (doubledouble(-0.0).isinf() == std::isinf(-0.0));
        CHECK ((-doubledouble(0.0)).isinf() == std::isinf(-0.0));
        CHECK (doubledouble(42.0).isinf() == std::isinf(42.0));
        CHECK (doubledouble(-42.0).isinf() == std::isinf(-42.0));
        CHECK ((-doubledouble(42.0)).isinf() == std::isinf(-42.0));
        CHECK (doubledouble::posnan().isinf() == std::isinf(posnan));
        CHECK (doubledouble::negnan().isinf() == std::isinf(negnan));
        CHECK (doubledouble::posinf().isinf() == std::isinf(posinf));
        CHECK (doubledouble::neginf().isinf() == std::isinf(neginf));
    }

    SUBCASE("isposinf") {

        CHECK (doubledouble(0.0).isposinf() == false);
        CHECK (doubledouble(-0.0).isposinf() == false);
        CHECK ((-doubledouble(0.0)).isposinf() == false);
        CHECK (doubledouble(42.0).isposinf() == false);
        CHECK (doubledouble(-42.0).isposinf() == false);
        CHECK ((-doubledouble(42.0)).isposinf() == false);
        CHECK (doubledouble::posnan().isposinf() == false);
        CHECK (doubledouble::negnan().isposinf() == false);
        CHECK (doubledouble::posinf().isposinf() == true);
        CHECK (doubledouble::neginf().isposinf() == false);
    }

    SUBCASE("isneginf") {

        CHECK (doubledouble(0.0).isneginf() == false);
        CHECK (doubledouble(-0.0).isneginf() == false);
        CHECK ((-doubledouble(0.0)).isneginf() == false);
        CHECK (doubledouble(42.0).isneginf() == false);
        CHECK (doubledouble(-42.0).isneginf() == false);
        CHECK ((-doubledouble(42.0)).isneginf() == false);
        CHECK (doubledouble::posnan().isneginf() == false);
        CHECK (doubledouble::negnan().isneginf() == false);
        CHECK (doubledouble::posinf().isneginf() == false);
        CHECK (doubledouble::neginf().isneginf() == true);
    }

    SUBCASE("isnan") {

        CHECK (doubledouble(0.0).isnan() == std::isnan(0.0));
        CHECK (doubledouble(-0.0).isnan() == std::isnan(-0.0));
        CHECK ((-doubledouble(0.0)).isnan() == std::isnan(-0.0));
        CHECK (doubledouble(42.0).isnan() == std::isnan(42.0));
        CHECK (doubledouble(-42.0).isnan() == std::isnan(-42.0));
        CHECK ((-doubledouble(42.0)).isnan() == std::isnan(-42.0));
        CHECK (doubledouble::posnan().isnan() == std::isnan(posnan));
        CHECK (doubledouble::negnan().isnan() == std::isnan(negnan));
        CHECK (doubledouble::posinf().isnan() == std::isnan(posinf));
        CHECK (doubledouble::neginf().isnan() == std::isnan(neginf));
    }

    SUBCASE("isnormal") {

        CHECK(doubledouble(0.0).isnormal() == std::isnormal(0.0));
        CHECK(doubledouble(-0.0).isnormal() == std::isnormal(-0.0));
        CHECK((-doubledouble(0.0)).isnormal() == std::isnormal(-0.0));
        CHECK(doubledouble(42.0).isnormal() == std::isnormal(42.0));
        CHECK(doubledouble(-42.0).isnormal() == std::isnormal(-42.0));
        CHECK((-doubledouble(42.0)).isnormal() == std::isnormal(-42.0));
        CHECK (doubledouble::posnan().isnormal() == std::isnormal(posnan));
        CHECK (doubledouble::negnan().isnormal() == std::isnormal(negnan));
        CHECK (doubledouble::posinf().isnormal() == std::isnormal(posinf));
        CHECK (doubledouble::neginf().isnormal() == std::isnormal(neginf));
    }

    SUBCASE("signbit") {

        CHECK (doubledouble(0.0).signbit() == std::signbit(0.0));
        CHECK (doubledouble(-0.0).signbit() == std::signbit(-0.0));
        CHECK ((-doubledouble(0.0)).signbit() == std::signbit(-0.0));
        CHECK (doubledouble(42.0).signbit() == std::signbit(42.0));
        CHECK (doubledouble(-42.0).signbit() == std::signbit(-42.0));
        CHECK ((-doubledouble(42.0)).signbit() == std::signbit(-42.0));
        CHECK (doubledouble::posnan().signbit() == std::signbit(posnan));
        CHECK (doubledouble::negnan().signbit() == std::signbit(negnan));
        CHECK (doubledouble::posinf().signbit() == std::signbit(posinf));
        CHECK (doubledouble::neginf().signbit() == std::signbit(neginf));
    }

    SUBCASE("iszero") {

        CHECK (doubledouble(0.0).iszero() == true);
        CHECK (doubledouble(-0.0).iszero() == true);
        CHECK ((-doubledouble(0.0)).iszero() == true);
        CHECK (doubledouble(1.0).iszero() == false);
        CHECK (doubledouble(-1.0).iszero() == false);
        CHECK ((-doubledouble(1.0)).iszero() == false);
        CHECK (doubledouble::posnan().iszero() == false);
        CHECK (doubledouble::negnan().iszero() == false);
        CHECK (doubledouble::posinf().iszero() == false);
        CHECK (doubledouble::neginf().iszero() == false);
    }

    SUBCASE("isposzero") {

        CHECK (doubledouble(0.0).isposzero() == true);
        CHECK (doubledouble(-0.0).isposzero() == false);
        CHECK ((-doubledouble(0.0)).isposzero() == false);
        CHECK (doubledouble(1.0).isposzero() == false);
        CHECK (doubledouble(-1.0).isposzero() == false);
        CHECK ((-doubledouble(1.0)).isposzero() == false);
        CHECK (doubledouble::posnan().isposzero() == false);
        CHECK (doubledouble::negnan().isposzero() == false);
        CHECK (doubledouble::posinf().isposzero() == false);
        CHECK (doubledouble::neginf().isposzero() == false);
    }

    SUBCASE("isnegzero") {

        CHECK (doubledouble(0.0).isnegzero() == false);
        CHECK (doubledouble(-0.0).isnegzero() == true);
        CHECK ((-doubledouble(0.0)).isnegzero() == true);
        CHECK (doubledouble(1.0).isnegzero() == false);
        CHECK (doubledouble(-1.0).isnegzero() == false);
        CHECK ((-doubledouble(1.0)).isnegzero() == false);
        CHECK (doubledouble::posnan().isnegzero() == false);
        CHECK (doubledouble::negnan().isnegzero() == false);
        CHECK (doubledouble::posinf().isnegzero() == false);
        CHECK (doubledouble::neginf().isnegzero() == false);
    }

    SUBCASE("isone") {

        CHECK (doubledouble(0.0).isone() == false);
        CHECK (doubledouble(-0.0).isone() == false);
        CHECK ((-doubledouble(0.0)).isone() == false);
        CHECK (doubledouble(1.0).isone() == true);
        CHECK (doubledouble(-1.0).isone() == false);
        CHECK ((-doubledouble(1.0)).isone() == false);
        CHECK (doubledouble::posnan().isone() == false);
        CHECK (doubledouble::negnan().isone() == false);
        CHECK (doubledouble::posinf().isone() == false);
        CHECK (doubledouble::neginf().isone() == false);
    }

    SUBCASE("ispositive") {

        CHECK (doubledouble(0.0).ispositive() == true);
        CHECK (doubledouble(-0.0).ispositive() == false);
        CHECK ((-doubledouble(0.0)).ispositive() == false);
        CHECK (doubledouble(1.0).ispositive() == true);
        CHECK (doubledouble(-1.0).ispositive() == false);
        CHECK ((-doubledouble(1.0)).ispositive() == false);
        CHECK (doubledouble::posnan().ispositive() == true);
        CHECK (doubledouble::negnan().ispositive() == false);
        CHECK (doubledouble::posinf().ispositive() == true);
        CHECK (doubledouble::neginf().ispositive() == false);
    }

    SUBCASE("isnegative") {

        CHECK (doubledouble(0.0).isnegative() == false);
        CHECK (doubledouble(-0.0).isnegative() == true);
        CHECK ((-doubledouble(0.0)).isnegative() == true);
        CHECK (doubledouble(1.0).isnegative() == false);
        CHECK (doubledouble(-1.0).isnegative() == true);
        CHECK ((-doubledouble(1.0)).isnegative() == true);
        CHECK (doubledouble::posnan().isnegative() == false);
        CHECK (doubledouble::negnan().isnegative() == true);
        CHECK (doubledouble::posinf().isnegative() == false);
        CHECK (doubledouble::neginf().isnegative() == true);
    }
}
