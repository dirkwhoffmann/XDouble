#pragma once

#define DBL_DEBUG
#define NUM_TESTS 10000
#pragma STDC FENV_ACCESS ON

#include "doctest.h"
#include "double-double.h"

using namespace dbl;

static inline double rand_int()
{
    return double((rand() % 128) - 64.0);
}

static inline double rand_int_pos()
{
    return double((rand() % 128) + 1);
}

static inline double rand_frac()
{
    double r = rand_int(); return r == 0.0 ? 0.0 : 1.0 / r;
}

static inline double rand_double()
{
    return rand_int() + rand_frac();
}

static inline double rand_double_pos()
{
    return rand_int_pos() + rand_frac();
}
