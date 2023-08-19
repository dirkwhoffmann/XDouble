#include "main.h"

TEST_CASE("Quad-double tests") {

    srand(0);

    SUBCASE("Experimental") {

        std::cout << std::setprecision(75);
        mpf_set_default_prec (500);

        doublefloat df(1.0);
        doubledouble dd(1.0);
        quaddouble qd(1.0);
        mpf_class mpf(1.0);

        for (int i = 0; i < 40; i++) {

            if (i == 39) break;

            df += doublefloat(i % 10);
            dd += doubledouble(i % 10);
            qd += quaddouble(i % 10);
            mpf += double(i % 10);

            std::cout << "+= " << i % 10 << ":" << std::endl;
            std::cout << "mpf : " << std::setprecision(50) << mpf << std::endl;
            std::cout << "qd  : " << qd.to_mpf() << std::endl;
            std::cout << "    : " << qd << std::endl;
            std::cout << std::endl;

            df /= doublefloat(10.0);
            dd /= doubledouble(10.0);
            qd /= quaddouble(10.0);
            mpf /= mpf_class("10.0");

            std::cout << "/= 10.0:" << std::endl;
            std::cout << "mpf : " << std::setprecision(50) << mpf << std::endl;
            // std::cout << "df  : " << df.to_mpf() << std::endl;
            // std::cout << "dd  : " << dd.to_mpf() << std::endl;
            std::cout << "qd  : " << qd.to_mpf() << std::endl;
            std::cout << "    : " << qd << std::endl;
            // std::cout << "    : " << qd << std::endl;
            std::cout << std::endl;
        }


        std::cout << "BREAK" << std::endl;
        std::cout << "qd  : " << qd.to_mpf() << std::endl;
        std::cout << "qdx : " << qd.x.to_mpf() << std::endl;
        std::cout << "qdy : " << qd.y.to_mpf() << std::endl;

        std::cout << "+= 9:" << std::endl;

        auto x = qd.x;
        auto y = qd.y;
        auto rhs = quaddouble(9.0);
        std::cout << "rhs : " << rhs << std::endl;

        auto sum = quaddouble::twoSum(x, rhs.x);
        auto sum2 = quaddouble::twoSum(rhs.x, x);
        // auto sum = quaddouble::quickTwoSum(rhs.x, x);
        std::cout << "qdx : " << qd.x.to_mpf() << std::endl;
        std::cout << "sum : " << sum.to_mpf() << std::endl;
        std::cout << "sum2: " << sum2.to_mpf() << std::endl;
        std::cout << std::endl;

        // twoSum
        std::cout << "sum:" << std::endl;
        auto a1 = x;
        auto b1 = rhs.x;
        doubledouble s1 = a1 + b1;
        doubledouble v1 = s1 - a1;
        doubledouble e1 = (a1 - (s1 - v1)) + (b1 - v1);
        std::cout << "a1  : " << a1.to_mpf() << std::endl;
        std::cout << "    : " << a1 << std::endl;
        std::cout << "b1  : " << b1.to_mpf() << std::endl;
        std::cout << "s1  : " << s1.to_mpf() << std::endl;
        // std::cout << "    :" << s1 << std::endl;
        std::cout << "v1  : " << v1.to_mpf() << std::endl;
        // std::cout << "    :" << v1 << std::endl;
        std::cout << "s1v1: " << (s1 - v1).to_mpf() << std::endl;
        std::cout << "    : " << (s1 - v1) << std::endl;
        std::cout << "ab1v1:" << (a1 - (s1 - v1)).to_mpf() << std::endl;
        std::cout << "b1v1: " << (b1 - v1).to_mpf() << std::endl;
        std::cout << "e1  : " << e1.to_mpf() << std::endl;
        std::cout << std::endl;

        // twoSum
        std::cout << "sum2:" << std::endl;
        auto a2 = rhs.x;
        auto b2 = x;
        doubledouble s2 = a2 + b2;
        doubledouble v2 = s2 - a2;
        doubledouble e2 = (a2 - (s2 - v2)) + (b2 - v2);
        std::cout << "a2  : " << a2.to_mpf() << std::endl;
        std::cout << "b2  : " << b2.to_mpf() << std::endl;
        std::cout << "s2  : " << s2.to_mpf() << std::endl;
        std::cout << "v2  : " << v2.to_mpf() << std::endl;
        std::cout << "s2v2: " << (s2 - v2).to_mpf() << std::endl;
        std::cout << "ab2v2:" << (a2 - (s2 - v2)).to_mpf() << std::endl;
        std::cout << "b2v2: " << (b2 - v2).to_mpf() << std::endl;
        std::cout << "e2  : " << e2.to_mpf() << std::endl;
        std::cout << std::endl;

/*
        df = doublefloat::pi;
        dd = doubledouble::pi;
        qd = quaddouble::pi;

        std::cout << "pi df: " << df.to_mpf() << std::endl;
        std::cout << "   df: " << df.to_string(100) << std::endl;
        std::cout << "pi dd: " << dd.to_mpf() << std::endl;
        std::cout << "   dd: " << dd.to_string(100) << std::endl;
        std::cout << "pi qd: " << qd.to_mpf() << std::endl;
        std::cout << "   qd: " << qd.to_string(100) << std::endl;
        std::cout << "pi   : 3.1415926535897932384626433832795028841971693993751058209749445923" << "" << std::endl;
 */
        CHECK(doubledouble(0.0).isfinite() == std::isfinite(0.0));
    }
}
