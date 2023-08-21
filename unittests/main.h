#pragma once

// #define DBL_DEBUG
#define NUM_TESTS 1000
#pragma STDC FENV_ACCESS ON

#include "doctest.h"
#include "xdouble.h"

using namespace xdb;

typedef XDouble<float> doublefloat;
typedef XDouble<double> doubledouble;
typedef XDouble<long double> longdoubledouble;

extern double posnan;
extern double negnan;
extern double posinf;
extern double neginf;

#define COMPARE(x,y) { \
CHECK(signbit(x) == signbit(y)); \
if (isnan(x)) { CHECK(isnan(y)); } else { CHECK(x == y); } \
}

double rand_int();
double rand_int_pos();
double rand_frac();
double rand_double();
double rand_double_pos();
