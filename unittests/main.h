#pragma once

#include "doctest.h"
#include "double-double.h"

#define NUM_TESTS 100000

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
