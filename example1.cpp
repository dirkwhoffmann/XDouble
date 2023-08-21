#include "xdouble.h"

typedef xdb::XDouble<double> doubledouble;

int main(int argc, char *argv[])
{
    doubledouble x = 0;

    for (int i = 1; i < 1000000; i += 4) {

        x += (doubledouble)4.0 / (doubledouble)i;
        x -= (doubledouble)4.0 / (doubledouble)(i + 2);
    }

    std::cout << x.to_string(40) << std::endl;
}
