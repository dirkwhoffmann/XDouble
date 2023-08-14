#include "doctest.h"
#include "double-double.h"
#include <iomanip>

TEST_CASE("Parsing") {

    SUBCASE("Experimental") {

        SUBCASE("strings") {

            doublefloat df("3.141592653589793238462643383279502884197169399375");
            doubledouble dd("3.141592653589793238462643383279502884197169399375");
            double d = 3.141592653589793238462643383279502884197169399375;
            float f = 3.141592653589793238462643383279502884197169399375;

            printf("\npi = 3.141592653589793238462643383279502884197169399375\n");
            printf("dd = %s\n", dd.to_string(35).c_str());
            printf("df = %s\n", df.to_string(35).c_str());
            printf("d  = %.20f\n", d);
            printf("f  = %.20f\n", f);

            /*
            auto y = doublefloat(1) / doublefloat(10);
            printf("str   = %s\n", y.asString(30).c_str());
            printf("real  = %.15f\n", 0.1);

            auto x = doublefloat::PI;
            auto str = x.asString(30);

            double pi2 = 3.1415926535897932384626433832795028;
            printf("str = %s\n", str.c_str());
            printf("pi  = %.15f\n", pi2);


            std::cout << std::setprecision(20);
            auto z = doublefloat(3141592) / doublefloat(1e6);
            std::cout << z; printf(" z = %s %.15f\n", z.asString(15).c_str(), z.asDouble());
            z += doublefloat(653589) / doublefloat(1e12);
            std::cout << z; printf(" z = %s %.15f\n", z.asString(15).c_str(), z.asDouble());
            z += doublefloat(793238) / doublefloat(1e18);
            std::cout << z; printf(" z = %s %.15f\n", z.asString(15).c_str(), z.asDouble());

            auto zz = double(3.141592);
            printf(" zz = %.15f\n", zz);
            zz += double(653589) / double(1e12);
            printf(" zz = %.15f\n", zz);
            zz += double(793238) / double(1e18);
            printf(" zz = %.15f\n", zz);
            */
            /*
            std::cout << z; printf(" z = %s %.15f\n", z.asString(15).c_str(), z.asDouble());
            z += doublefloat(462643) / doublefloat(10e24);
            std::cout << z; printf(" z = %s %.15f\n", z.asString(15).c_str(), z.asDouble());
            z += doublefloat(383279) / doublefloat(10e30);
            std::cout << z; printf(" z = %s %.15f\n", z.asString(15).c_str(), z.asDouble());
            z += doublefloat(502884) / doublefloat(10e36);
            std::cout << z; printf(" z = %s %.15f\n", z.asString(15).c_str(), z.asDouble());
            z += doublefloat(197169) / doublefloat(10e42);
            std::cout << z; printf(" z = %s %.15f\n", z.asString(15).c_str(), z.asDouble());
            */
            /*
            z += doublefloat(0.399375e-42);
            printf("z = %s %.15f\n", z.asString(15).c_str(), z.asDouble());
            z += doublefloat(0.105820e-48);
            printf("z = %s %.15f\n", z.asString(15).c_str(), z.asDouble());
            z += doublefloat(0.974944e-54);
            printf("z = %s %.15f\n", z.asString(15).c_str(), z.asDouble());
            */
            CHECK(1 == 1);

        }
    }
}
