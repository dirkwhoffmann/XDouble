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
}
