#include "double-double.h"

typedef xd::XDouble<double> doubledouble;

int main(int argc, char *argv[])
{
    double x1(2.0);
    double x2 = std::sqrt(x1);

    doubledouble y1(2.0);
    doubledouble y2 = xd::sqrt(y1);

    std::cout << "double:       " << std::setprecision(41) << x2 << std::endl;
    std::cout << "doubledouble: " << y2.to_string(40) << std::endl;
    std::cout << "Exact:        1.4142135623730950488016887242096980785696" << std::endl;
}
