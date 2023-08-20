#include "main.h"

TEST_CASE("Classification functions") {

    srand(0);

    SUBCASE("isfinite") {

        CHECK(doubledouble(0.0).isfinite() == std::isfinite(0.0));
        CHECK(doubledouble(-0.0).isfinite() == std::isfinite(-0.0));
        CHECK((-doubledouble(0.0)).isfinite() == std::isfinite(-0.0));
        CHECK(doubledouble(42.0).isfinite() == std::isfinite(42.0));
        CHECK(doubledouble(-42.0).isfinite() == std::isfinite(-42.0));
        CHECK((-doubledouble(42.0)).isfinite() == std::isfinite(-42.0));
        CHECK(doubledouble::nan().isfinite() == std::isfinite(std::numeric_limits<double>::quiet_NaN()));
        CHECK((-doubledouble::nan()).isfinite() == std::isfinite(-std::numeric_limits<double>::quiet_NaN()));
        CHECK(doubledouble::inf().isfinite() == std::isfinite(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).isfinite() == std::isfinite(-std::numeric_limits<double>::infinity()));
    }

    SUBCASE("isinf") {

        CHECK(doubledouble(0.0).isinf() == std::isinf(0.0));
        CHECK(doubledouble(-0.0).isinf() == std::isinf(-0.0));
        CHECK((-doubledouble(0.0)).isinf() == std::isinf(-0.0));
        CHECK(doubledouble(42.0).isinf() == std::isinf(42.0));
        CHECK(doubledouble(-42.0).isinf() == std::isinf(-42.0));
        CHECK((-doubledouble(42.0)).isinf() == std::isinf(-42.0));
        CHECK(doubledouble::nan().isinf() == std::isinf(std::numeric_limits<double>::quiet_NaN()));
        CHECK((-doubledouble::nan()).isinf() == std::isinf(-std::numeric_limits<double>::quiet_NaN()));
        CHECK(doubledouble::inf().isinf() == std::isinf(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).isinf() == std::isinf(-std::numeric_limits<double>::infinity()));
    }

    SUBCASE("isnan") {

        CHECK(doubledouble(0.0).isnan() == std::isnan(0.0));
        CHECK(doubledouble(-0.0).isnan() == std::isnan(-0.0));
        CHECK((-doubledouble(0.0)).isnan() == std::isnan(-0.0));
        CHECK(doubledouble(42.0).isnan() == std::isnan(42.0));
        CHECK(doubledouble(-42.0).isnan() == std::isnan(-42.0));
        CHECK((-doubledouble(42.0)).isnan() == std::isnan(-42.0));
        CHECK(doubledouble::nan().isnan() == std::isnan(std::numeric_limits<double>::quiet_NaN()));
        CHECK((-doubledouble::nan()).isnan() == std::isnan(-std::numeric_limits<double>::quiet_NaN()));
        CHECK(doubledouble::inf().isnan() == std::isnan(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).isnan() == std::isnan(-std::numeric_limits<double>::infinity()));
    }

    SUBCASE("isnormal") {

        CHECK(doubledouble(0.0).isnormal() == std::isnormal(0.0));
        CHECK(doubledouble(-0.0).isnormal() == std::isnormal(-0.0));
        CHECK((-doubledouble(0.0)).isnormal() == std::isnormal(-0.0));
        CHECK(doubledouble(42.0).isnormal() == std::isnormal(42.0));
        CHECK(doubledouble(-42.0).isnormal() == std::isnormal(-42.0));
        CHECK((-doubledouble(42.0)).isnormal() == std::isnormal(-42.0));
        CHECK(doubledouble::nan().isnormal() == std::isnormal(std::numeric_limits<double>::quiet_NaN()));
        CHECK((-doubledouble::nan()).isnormal() == std::isnormal(-std::numeric_limits<double>::quiet_NaN()));
        CHECK(doubledouble::inf().isnormal() == std::isnormal(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).isnormal() == std::isnormal(-std::numeric_limits<double>::infinity()));
    }

    SUBCASE("signbit") {

        CHECK(doubledouble(0.0).signbit() == std::signbit(0.0));
        CHECK(doubledouble(-0.0).signbit() == std::signbit(-0.0));
        CHECK((-doubledouble(0.0)).signbit() == std::signbit(-0.0));
        CHECK(doubledouble(42.0).signbit() == std::signbit(42.0));
        CHECK(doubledouble(-42.0).signbit() == std::signbit(-42.0));
        CHECK((-doubledouble(42.0)).signbit() == std::signbit(-42.0));
        CHECK(doubledouble::nan().signbit() == std::signbit(std::numeric_limits<double>::quiet_NaN()));
        CHECK((-doubledouble::nan()).signbit() == std::signbit(-std::numeric_limits<double>::quiet_NaN()));
        CHECK(doubledouble::inf().signbit() == std::signbit(std::numeric_limits<double>::infinity()));
        CHECK((-doubledouble::inf()).signbit() == std::signbit(-std::numeric_limits<double>::infinity()));
    }

    SUBCASE("iszero") {

        CHECK(doubledouble(0.0).iszero() == true);
        CHECK(doubledouble(-0.0).iszero() == true);
        CHECK((-doubledouble(0.0)).iszero() == true);
        CHECK(doubledouble(1.0).iszero() == false);
        CHECK(doubledouble(-1.0).iszero() == false);
        CHECK((-doubledouble(1.0)).iszero() == false);
        CHECK(doubledouble::nan().iszero() == false);
        CHECK((-doubledouble::nan()).iszero() == false);
        CHECK(doubledouble::inf().iszero() == false);
        CHECK((-doubledouble::inf()).iszero() == false);
    }

    SUBCASE("isone") {

        CHECK(doubledouble(0.0).isone() == false);
        CHECK(doubledouble(-0.0).isone() == false);
        CHECK((-doubledouble(0.0)).isone() == false);
        CHECK(doubledouble(1.0).isone() == true);
        CHECK(doubledouble(-1.0).isone() == false);
        CHECK((-doubledouble(1.0)).isone() == false);
        CHECK(doubledouble::nan().isone() == false);
        CHECK((-doubledouble::nan()).isone() == false);
        CHECK(doubledouble::inf().isone() == false);
        CHECK((-doubledouble::inf()).isone() == false);
    }

    SUBCASE("ispositive") {

        CHECK(doubledouble(0.0).ispositive() == false);
        CHECK(doubledouble(-0.0).ispositive() == false);
        CHECK((-doubledouble(0.0)).ispositive() == false);
        CHECK(doubledouble(1.0).ispositive() == true);
        CHECK(doubledouble(-1.0).ispositive() == false);
        CHECK((-doubledouble(1.0)).ispositive() == false);
        CHECK(doubledouble::nan().ispositive() == false);
        CHECK((-doubledouble::nan()).ispositive() == false);
        CHECK(doubledouble::inf().ispositive() == true);
        CHECK((-doubledouble::inf()).ispositive() == false);
    }

    SUBCASE("isnegative") {

        CHECK(doubledouble(0.0).isnegative() == false);
        CHECK(doubledouble(-0.0).isnegative() == false);
        CHECK((-doubledouble(0.0)).isnegative() == false);
        CHECK(doubledouble(1.0).isnegative() == false);
        CHECK(doubledouble(-1.0).isnegative() == true);
        CHECK((-doubledouble(1.0)).isnegative() == true);
        CHECK(doubledouble::nan().isnegative() == false);
        CHECK((-doubledouble::nan()).isnegative() == false);
        CHECK(doubledouble::inf().isnegative() == false);
        CHECK((-doubledouble::inf()).isnegative() == true);
    }
}
