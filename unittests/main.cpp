#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "main.h"

#include <exception>

double posnan = std::numeric_limits<double>::quiet_NaN();
double negnan = -std::numeric_limits<double>::quiet_NaN();
double posinf = std::numeric_limits<double>::infinity();
double neginf = -std::numeric_limits<double>::infinity();

void clearFlags()
{
    std::feclearexcept(FE_ALL_EXCEPT);
}

fexcept_t getFlags()
{
    fexcept_t result;

    if (fegetexceptflag(&result, FE_ALL_EXCEPT)) {
        throw std::runtime_error("Failed to read floating-point exception flags");
    }
    return result;
}

std::pair<fexcept_t, fexcept_t> execute(std::function<void()> f, std::function<void()> g)
{
    clearFlags();
    f();
    auto flags1 = getFlags();

    clearFlags();
    g();
    auto flags2 = getFlags();

    return { flags1, flags2 };
}

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
