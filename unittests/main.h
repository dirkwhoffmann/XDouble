#pragma once

// #define DBL_DEBUG
#define NUM_TESTS 1000
#pragma STDC FENV_ACCESS ON

#include "doctest.h"
#include "xdouble.h"
#include <functional>

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

void clearFlags();
fexcept_t getFlags();

std::pair<fexcept_t, fexcept_t> execute(std::function<void()> f, std::function<void()> g);

double rand_int();
double rand_int_pos();
double rand_frac();
double rand_double();
double rand_double_pos();
