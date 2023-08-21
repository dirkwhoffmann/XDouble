#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "main.h"

double posnan = std::numeric_limits<double>::quiet_NaN();
double negnan = -std::numeric_limits<double>::quiet_NaN();
double posinf = std::numeric_limits<double>::infinity();
double neginf = -std::numeric_limits<double>::infinity();

double rand_int()
{
    return double((rand() % 128) - 64.0);
}

double rand_int_pos()
{
    return double((rand() % 128) + 1);
}

double rand_frac()
{
    double r = rand_int(); return r == 0.0 ? 0.0 : 1.0 / r;
}

double rand_double()
{
    return rand_int() + rand_frac();
}

double rand_double_pos()
{
    return rand_int_pos() + rand_frac();
}
