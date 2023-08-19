// -----------------------------------------------------------------------------
// double-double - A lightweight double-double arithmetic library in C++
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Published under the terms of the MIT License
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//         THIS IS A BETA-VERSION. THE CODE IS NOT PRODUCTION-READY
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Double-double arithmetic increases the precision of floating point operations
// by representing numbers as an unevaluated sum of two floating point numbers
// with lower precision. This results in a floating point format with almost
// twice the precision of the base format without sacrificing speed too much.
//
// This library is a lightweight implementation of double-double arithetics
// written in C++20.
//
// Highlights:
//
//   - Easy to use in your own application (header-only library).
//
//   - Interchangable base types due to a template-based design.
//
// References:
//
//   - Hida, Y., Li, X. S., Bailey, D. H. (2000), "Quad-Double Arithmetic:
//     Algorithms, Implementation, and Application", Technical Report LBNL-46996
//
//   - double-double Python library by Juraj Sukop
//     https://github.com/sukop/doubledouble/tree/master
//
//   - Fork of QD (2.3.17) by scibuilder
//     https://github.com/scibuilder/QD
//
//   - David H. Bailey: High-Precision Software Directory
//     https://www.davidhbailey.com/dhbsoftware
// -----------------------------------------------------------------------------

#pragma once

#include <cstdio>
#include <cassert>
#include <cmath>
#include <cfenv>
#include <limits>
#include <algorithm>
#include <utility>
#include <iostream>
#include <iomanip>

// REMOVE ASAP
// #include <typeinfo>

#ifdef DBL_DEBUG
#include "gmpxx.h"
#endif

namespace dbl {

// Import cmath API into namespace
using std::exp;
using std::frexp;
using std::ldexp;
using std::log;
using std::log10;
using std::modf;
using std::exp2;
using std::log2;

using std::pow;
using std::sqrt;

using std::ceil;
using std::floor;
using std::fmod;
using std::trunc;
using std::round;
using std::lround;
using std::llround;
using std::rint;
using std::lrint;
using std::nearbyint;

using std::copysign;
using std::nan;
using std::fdim;
using std::fmax;
using std::fmin;

using std::fabs;
using std::abs;
using std::fma;

using std::isfinite;
using std::isinf;
using std::isnan;
using std::isnormal;
using std::signbit;

// Forward declaration of external API
template <class T> class Double;

template <class T> Double<T> exp(const Double<T> &op);
template <class T> Double<T> frexp(const Double<T> &op, int *exp);
template <class T> Double<T> frexp10(const Double<T> &op, int *exp);
template <class T> Double<T> ldexp(const Double<T> &op, int exp);
template <class T> Double<T> ldexp10(const Double<T> &op, int exp);
template <class T> Double<T> log(const Double<T> &op);
template <class T> Double<T> log10(const Double<T> &op);
template <class T> Double<T> modf(const Double<T> &op, Double<T> *iptr);
template <class T> Double<T> exp2(const Double<T> &op);
template <class T> Double<T> log2(const Double<T> &op);

template <class T> Double<T> pow(const Double<T> &base, int exponent);
template <class T> Double<T> pow(const Double<T> &base, const Double<T> &exponent);
template <class T> Double<T> sqr(const Double<T> &x);
template <class T> Double<T> sqrt(const Double<T> &x);

template <class T> Double<T> ceil(const Double<T> &x);
template <class T> Double<T> ceil(const Double<T> &x, int fracdigits);
template <class T> Double<T> floor(const Double<T> &x);
template <class T> Double<T> floor(const Double<T> &x, int fracdigits);
template <class T> Double<T> fmod(const Double<T> &numer, const Double<T> &denom);
template <class T> Double<T> trunc(const Double<T> &x);
template <class T> Double<T> trunc(const Double<T> &x, int fracdigits);
template <class T> Double<T> round(const Double<T> &x);
template <class T> Double<T> round(const Double<T> &x, int fracdigits);
template <class T> Double<T> roundEven(const Double<T> &x);
template <class T> Double<T> roundEven(const Double<T> &x, int fracdigits);
template <class T> long lround(const Double<T> &x);
template <class T> long long llround(const Double<T> &x);
template <class T> Double<T> rint(const Double<T> &x);
template <class T> Double<T> rint(const Double<T> &x, int fracdigits);
template <class T> long lrint(const Double<T> &x);
template <class T> long long llrint(const Double<T> &x);
template <class T> Double<T> nearbyint(const Double<T> &x);
template <class T> Double<T> nearbyint(const Double<T> &x, int fracdigits);

template <class T>  Double<T> copysign(const Double<T> &x, const Double<T> &y);
template <class T> Double<T> fdim(const Double<T> &x, const Double<T> &y);
template <class T> Double<T> fmax(const Double<T> &x, const Double<T> &y);
template <class T> Double<T> fmin(const Double<T> &x, const Double<T> &y);

template <class T> Double<T> fabs(const Double<T> &x);
template <class T> Double<T> abs(const Double<T> &x);
template <class T> Double<T> fma(const Double<T> &x, const Double<T> &y, const Double<T> &z);

template <class T> bool isfinite(const Double<T> &x);
template <class T> bool isinf(const Double<T> &x);
template <class T> bool isnan(const Double<T> &x);
template <class T> bool isnormal(const Double<T> &x);
template <class T> bool signbit(const Double<T> &x);

template <class T> bool iszero(const Double<T> &x);
template <class T> bool isone(const Double<T> &x);
template <class T> bool ispositive(const Double<T> &x);
template <class T> bool isnegative(const Double<T> &x);

template <class T> class Double {

    constexpr static bool useFma = false;

public:

    T x, y;

public:

    //
    // Constructors
    //

    Double() noexcept : x(0), y(0) { }
    Double(T x) noexcept : x(x), y(0) { }
    Double(T x, T y) noexcept : x(x), y(y) { }
    Double(const Double<T>& other) noexcept : x(other.x), y(other.y) { }
    Double(Double<T>&& other) noexcept : Double() { swap(*this, other); }

    Double(const std::string &s) noexcept : Double()
    {
        std::string left = s;
        std::string right = "";

        if (auto pos = s.find("."); pos != std::string::npos) {

            left = s.substr(0, pos);
            right = s.substr(pos + 1, std::string::npos);
        }

        *this = Double(left, right);
    }

    Double(const std::string &left, const std::string &right) noexcept : Double()
    {
        Double<T> l, r;

        // Check if the number is positive or negative
        bool neg = left.empty() ? false : left[0] == '-';

        // Parse the integral digits
        for (auto it = left.begin() ; it != left.end(); ++it) {
            if (*it >= '0' && *it <= '9') l = l * Double<T>(10) + Double<T>(*it - '0');
        }

        // Parse the fractional digits (in reverse order)
        for (auto it = right.crbegin() ; it != right.crend(); ++it) {
            if (*it >= '0' && *it <= '9') r = (r + Double<T>(*it - '0')) / Double<T>(10);
        }

        // Assemble the result
        *this = neg ? -(l + r) : (l + r);
    }

private:

    friend void swap(Double<T>& first, Double<T>& second) noexcept
    {
        std::swap(first.x, second.x);
        std::swap(first.y, second.y);
    }


    //
    // Constants
    //

public:

    static const Double<T> e;
    static const Double<T> log2e;
    static const Double<T> log10e;
    static const Double<T> pi;
    static const Double<T> inv_pi;
    static const Double<T> inv_sqrtpi;
    static const Double<T> ln2;
    static const Double<T> ln10;
    static const Double<T> sqrt2;
    static const Double<T> sqrt3;
    static const Double<T> inv_sqrt3;
    static const Double<T> egamma;
    static const Double<T> phi;

    static Double<T> nan()
    {
        return Double<T>(std::numeric_limits<double>::quiet_NaN());
    }

    static Double<T> inf()
    {
        return Double<T>(std::numeric_limits<double>::infinity());
    }

    static int digits();


    //
    // Accessors
    //

    T getX() const { return x; }
    T getY() const { return y; }


    //
    // Basic operators
    //

    Double<T>& operator=(Double<T> rhs)
    {
        swap(*this, rhs);
        return *this;
    }


    //
    // Cast operators
    //

    operator int() const { return static_cast<int>(to_long_double()); }
    operator long() const { return static_cast<long>(to_long_double()); }
    operator long long() const { return static_cast<long long>(to_long_double()); }
    operator float() const { return static_cast<float>(to_long_double()); }
    operator double() const { return static_cast<float>(to_long_double()); }
    operator long double() const { return to_long_double(); }

    //
    // Conversion functions
    //

    int to_int() const
    {
        return static_cast<int>(to_long_double());
    }

    long to_long() const
    {
        return static_cast<long>(to_long_double());
    }

    long long to_long_long() const
    {
        return static_cast<long long>(to_long_double());
    }

    float to_float() const
    {
        return static_cast<float>(to_long_double());
    }

    double to_double() const
    {
        return static_cast<double>(to_long_double());
    }

    long double to_long_double() const
    {
        // printf("long double to_long_double() const\n");
        return static_cast<long double>(x) + static_cast<long double>(y);
    }

#ifdef DBL_DEBUG
    mpf_class to_mpf() const
    {
        constexpr int precision = 256;

        mpf_class result = 0.0;

        if constexpr (std::is_same<T, float>::value) {
            result = mpf_class(x, precision) + mpf_class(y, precision);
        } else if constexpr (std::is_same<T, double>::value) {
            result = mpf_class(x, precision) + mpf_class(y, precision);
        } else {
            result = x.to_mpf() + y.to_mpf();
        }
        return result;
    }
#endif

    char to_character() const
    {
        auto digit = round().to_long() + '0';
        return digit >= '0' && digit <= '9' ? char(digit) : '?';
    }

    std::string to_string(int digits) const
    {
        return to_string(128, digits);
    }

    std::string to_string(int ldigits, int rdigits) const
    {
        std::string result;

        // Catch NaN and infinity
        if (isnan()) return "nan";
        if (isinf()) return signbit() ? "-inf" : "inf";

        // Split number into its integral (l) and fractional (r) part
        Double<T> l; Double<T> r = modf(&l);

        // Compute integral digits
        for (int i = 0; i < ldigits && l.abs() >= Double<T>(1.0); i++) {

            l /= Double<T>(10.0);
            Double<T> digit = l.modf(&l) * Double<T>(10.0);
            result = digit.to_character() + result;
        }

        // Create a decimal point of necessary
        if (rdigits) result += '.';

        // Compute fractional digits
        for (int i = 0; i < rdigits; i++) {

            r *= Double<T>(10.0);
            Double<T> digit; r = r.modf(&digit);
            result = result + digit.to_character();
        }

        return (isnegative() ? "-" : "") + result;
    }


    //
    // Comparison operators
    //

    bool operator==(const Double<T>& rhs) const
    {
        if (isnan() || rhs.isnan()) return false;
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const Double<T>& rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const Double<T>& rhs) const
    {
        if (isnan() || rhs.isnan()) return false;
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }

    bool operator>(const Double<T>& rhs) const
    {
        if (isnan() || rhs.isnan()) return false;
        return rhs < *this;
    }

    bool operator<=(const Double<T>& rhs) const
    {
        if (isnan() || rhs.isnan()) return false;
        return !(*this > rhs);
    }

    bool operator>=(const Double<T>& rhs) const
    {
        if (isnan() || rhs.isnan()) return false;
        return !(*this < rhs);
    }


    //
    // Basic arithmetic functions
    //

    static Double<T> quickTwoSum(T a, T b) {

        T s = a + b;
        T e = b - (s - a);

        return Double<T>(s,e);
    }

    static Double<T> twoSum(T a, T b) {

        T s = a + b;
        T v = s - a;
        T e = (a - (s - v)) + (b - v);
        return Double<T>(s,e);
    }

    static Double<T> split(T a) {

        /*
        int digits;

        if (std::is_same<T, Double<float>>::value) {
            digits = std::numeric_limits<float>::digits - 6;
        } else if (std::is_same<T, Double<double>>::value) {
            digits = std::numeric_limits<double>::digits - 6;
        } else {
            digits = std::numeric_limits<T>::digits / 2 + 1;
        }
        // printf("digits = %d %f\n", digits, (double)(dbl::ldexp(T(1),digits) + T(1)));
         */

        T t = (dbl::ldexp(T(1), digits()) + T(1)) * a;
        T h = t - (t - a);
        T l = a - h;

        return Double<T>(h,l);
    }

    static void split3(T a, T *s1, T *s2, T *s3) {

        if (std::is_same<T, Double<float>>::value || std::is_same<T, Double<double>>::value) {

            auto s = split(a);
            *s1 = s.x;
            *s2 = s.y;
            *s3 = 0.0;
            return;
        }

        T t = (dbl::ldexp(T(1), 18) + T(1)) * a;
        T h = t - (t - a);
        *s1 = h;

        T l = a - h;
        T t2 = (dbl::ldexp(T(1), 18) + T(1)) * l;
        T h2 = t2 - (t2 - l);
        *s2 = h2;

        T l2 = l - h2;
        *s3 = l2;
    }

    static Double<T> twoProd(T a, T b) {

        if constexpr (useFma) {

            auto p =  a * b;
            auto e = dbl::fma(a, b, -p);

            return Double<T>(p,e);

        } else {

            auto p =  a * b;
            auto aa = split(a);
            auto bb = split(b);
            auto e = ((aa.x * bb.x - p) + aa.x * bb.y + aa.y * bb.x) + aa.y * bb.y;

            return Double<T>(p,e);
        }
    }

    Double<T> operator-() const
    {
        return Double<T>(-x, -y);
    }

    Double<T> &operator+=(const Double<T> &rhs)
    {
        if (isfinite() && rhs.isfinite()) {


            auto sum = twoSum(x, rhs.x);
            sum.y += y + rhs.y;
            *this = quickTwoSum(sum.x, sum.y);
            /*
            T xl = x;
            T xh = y;
            T yl = rhs.x;
            T yh = rhs.y;

            //const [sl,sh] = twoSum(xh,yh);
            T sh = xh + yh; T _1 = sh - xh; T sl = (xh - (sh - _1)) + (yh - _1);
            //const [tl,th] = twoSum(xl,yl);
            T th = xl + yl; T _2 = th - xl; T tl = (xl - (th - _2)) + (yl - _2);
            T c = sl + th;
            //const [vl,vh] = fastTwoSum(sh,c)
            T vh = sh + c; T vl = c - (vh - sh);
            T w = tl + vl;
            //const [zl,zh] = fastTwoSum(vh,w)
            T zh = vh + w; T zl = w - (zh - vh);
            *this = Double<T>(zh, zl);
            */

        } else if (isnan() || rhs.isnan()) {

            *this = nan();

        } else if (isinf() && rhs.isinf()) {

            if (signbit() ^ rhs.signbit()) *this = nan();

        } else if (rhs.isinf()) {

            *this = rhs;
        }

        return *this;
    }

    Double<T> operator+(const Double<T> &rhs) const
    {
        Double<T> result;
        result = *this;
        result += rhs;

        return result;
    }

    friend Double<T> operator+(double lhs, Double<T> rhs) { return Double<T>(lhs) + rhs; }
    friend Double<T> operator+(Double<T> lhs, double rhs) { return lhs + Double<T>(rhs); }

    Double<T> &operator-=(const Double<T> &rhs)
    {
        *this += -rhs;
        return *this;
    }

    Double<T> operator-(const Double<T> &rhs) const
    {
        auto result = *this;
        result -= rhs;

        return result;
    }

    friend Double<T> operator-(double lhs, Double<T> rhs) { return Double<T>(lhs) - rhs; }
    friend Double<T> operator-(Double<T> lhs, double rhs) { return lhs - Double<T>(rhs); }

    Double<T> &operator*=(const Double<T> &rhs)
    {
        if (isfinite() && rhs.isfinite()) {

            auto val = twoProd(x, rhs.x);
            val.y += x * rhs.y + y * rhs.x;
            *this = quickTwoSum(val.x, val.y);

        } else if (isnan() || rhs.isnan()) {

            *this = nan();

        } else {

            *this = (signbit() ^ rhs.signbit()) ? -inf() : inf();
        }

        return *this;
    }

    Double<T> operator*(const Double<T> &rhs) const
    {
        auto result = *this;
        result *= rhs;

        return result;
    }

    friend Double<T> operator*(double lhs, Double<T> rhs) { return Double<T>(lhs) * rhs; }
    friend Double<T> operator*(Double<T> lhs, double rhs) { return lhs * Double<T>(rhs); }

    Double<T> &operator/=(const Double<T> &rhs)
    {
        if (rhs.iszero()) {

            *this = (iszero() || isnan()) ? nan() : signbit() ? -inf() : inf();
            return *this;
        }
        if (isnan() || rhs.isnan()) {

            *this = nan();
            return *this;
        }
        if (isinf() && rhs.isinf()) {

            *this = nan();
            return *this;
        }
        if (isinf()) {

            *this = signbit() ^ rhs.signbit() ? -inf() : inf();
            return *this;
        }
        if (rhs.isinf()) {

            *this = signbit() ^ rhs.signbit() ? -Double<T>() : Double<T>();
            return *this;
        }

        /*
        auto r = x / rhs.x;

        auto val = twoProd(r, rhs.x);
        auto e = (x - val.x - val.y + y - r * rhs.y) / rhs.x;

        *this = quickTwoSum(r, e);
        return *this;
        */

        Double<T> r = *this;
        T q1 = r.x / rhs.x;

        r -= Double<T>(q1) * rhs;
        T q2 = r.x / rhs.x;

        r -= Double<T>(q2) * rhs;
        T q3 = r.x / rhs.x;

        *this = Double<T>(q1) + Double<T>(q2) + Double<T>(q3);
        return *this;
    }

    Double<T> operator/(const Double<T> &rhs) const
    {
        auto result = *this;
        result /= rhs;

        return result;
    }

    friend Double<T> operator/(double lhs, Double<T> rhs) { return Double<T>(lhs) / rhs; }
    friend Double<T> operator/(Double<T> lhs, double rhs) { return lhs / Double<T>(rhs); }

    void operator++()
    {
        *this += 1.0;
    }

    void operator++(int)
    {
        *this += 1.0;
    }

    void operator--()
    {
        *this -= 1.0;
    }

    void operator--(int)
    {
        *this -= 1.0;
    }


    //
    // Trigonometric functions
    //

    // Not implemented, yet


    //
    // Exponential and logarithmic functions
    //

    Double<T> exp() const { return dbl::exp(*this); }
    Double<T> frexp(int *exp) const { return dbl::frexp(*this, exp); }
    Double<T> frexp10(int *exp) const { return dbl::frexp10(*this, exp); }
    Double<T> ldexp(int exp) const { return dbl::ldexp(*this, exp); }
    Double<T> ldexp10(int exp) const { return dbl::ldexp10(*this, exp); }
    Double<T> log() const { return dbl::log(*this); }
    Double<T> log10() const  { return dbl::log10(*this); }
    Double<T> modf(Double<T> *iptr) const { return dbl::modf(*this, iptr); }
    Double<T> exp2() const { return dbl::exp2(*this); }
    Double<T> log2() const { return dbl::log2(*this); }


    //
    // Power functions
    //

    Double<T> pow(int exponent) const { return dbl::pow(*this, exponent); }
    Double<T> pow(const Double<T> &exponent) const { return dbl::pow(*this, exponent); }
    Double<T> sqr() const { return dbl::sqr(*this); }
    Double<T> sqrt() const { return dbl::sqrt(*this); }


    //
    // Error and gamma functions
    //

    // Not implemented


    //
    // Rounding and remainder functions
    //

    Double<T> ceil() const { return dbl::ceil(*this); }
    Double<T> ceil(int fracdigits) const { return dbl::ceil(*this, fracdigits); }
    Double<T> floor() const { return dbl::floor(*this); }
    Double<T> floor(int fracdigits) const { return dbl::floor(*this, fracdigits); }
    Double<T> fmod(Double<T> denom) const { return dbl::fmod(*this, denom); }
    Double<T> trunc() const { return dbl::trunc(*this); }
    Double<T> trunc(int fracdigits) const { return dbl::trunc(*this, fracdigits); }
    Double<T> round() const { return dbl::round(*this); }
    Double<T> round(int fracdigits) const { return dbl::round(*this, fracdigits); }
    Double<T> roundEven() const { return dbl::roundEven(*this); }
    Double<T> roundEven(int fracdigits) const  { return dbl::roundEven(*this, fracdigits); }
    long lround() const { return dbl::lround(*this); }
    long long llround() const { return dbl::llround(*this); }
    Double<T> rint() const { return dbl::rint(*this); }
    Double<T> rint(int fracdigits) const { return dbl::rint(*this, fracdigits); }
    long lrint() const { return dbl::lrint(*this); }
    long long llrint() const { return dbl::llrint(*this); }
    Double<T> nearbyint() const { return dbl::nearbyint(*this); }
    Double<T> nearbyint(int fracdigits) const { return dbl::nearbyint(*this, fracdigits); }


    //
    // Floating-point manipulation functions
    //

    Double<T> copysign(const Double<T> &y) const { return dbl::copysign(*this, y); }


    //
    // Minimum, maximum, difference functions
    //

    Double<T> fdim(const Double<T> &y) const { return dbl::fdim(*this, y); }
    Double<T> fmax(const Double<T> &y) const { return dbl::fmax(*this, y); }
    Double<T> fmin(const Double<T> &y) const { return dbl::fmin(*this, y); }


    //
    // Other functions
    //

    Double<T> fabs() const { return dbl::fabs(*this); }
    Double<T> abs() const { return dbl::abs(*this); }
    Double<T> fma() const { return dbl::fma(*this); }


    //
    // Classification functions
    //

    bool isfinite() const { return dbl::isfinite(*this); }
    bool isinf() const { return dbl::isinf(*this); }
    bool isnan() const { return dbl::isnan(*this); }
    bool isnormal() const { return dbl::isnormal(*this); }
    bool signbit() const { return dbl::signbit(*this); }

    bool iszero() const { return dbl::iszero(*this); }
    bool isone() const { return dbl::isone(*this); }
    bool ispositive() const { return dbl::ispositive(*this); }
    bool isnegative() const { return dbl::isnegative(*this); }
};


//
// Exponential and logarithmic functions
//

template <class T> inline Double<T>
exp(const Double<T> &op)
{
    auto n = dbl::round(op.x);
    auto w = op - Double<T>(n);

    auto u = (((((((((((w +
                        156.0) * w + 12012.0) * w +
                      600600.0) * w + 21621600.0) * w +
                    588107520.0) * w + 12350257920.0) * w +
                  201132771840.0) * w + 2514159648000.0) * w +
                23465490048000.0) * w + 154872234316800.0) * w +
              647647525324800.0) * w + 1295295050649600.0;

    auto v = (((((((((((w -
                        156.0) * w + 12012.0) * w -
                      600600.0) * w + 21621600.0) * w -
                    588107520.0) * w + 12350257920.0) * w -
                  201132771840.0) * w + 2514159648000.0) * w -
                23465490048000.0) * w + 154872234316800.0) * w -
              647647525324800.0) * w + 1295295050649600.0;

    return Double<T>::e.pow((int)n) * (u / v);
}

template <class T> inline Double<T>
frexp(const Double<T> &op, int *exp)
{
    auto r = dbl::frexp(op.x, exp);
    auto e = dbl::ldexp(op.y, -(*exp));

    return Double<T>(r, e);
}

template <class T> inline Double<T>
frexp10(const Double<T> &op, int *exp)
{
    *exp = op.iszero() ? 0 : 1 + (op.fabs().log10().floor().to_int());
    return op * Double<T>(10).pow(-(*exp));
}

template <class T> inline Double<T>
ldexp(const Double<T> &op, int exp)
{
    return Double<T>(dbl::ldexp(op.x, exp), dbl::ldexp(op.y, exp));
}

template <class T> inline Double<T>
ldexp10(const Double<T> &op, int exp)
{
    return op * Double<T>(10).pow(exp);
}

template <class T> inline Double<T>
log(const Double<T> &op)
{
    if (op.isnegative()) return Double<T>::nan();
    if (op.iszero()) return -Double<T>::inf();

    auto r = Double<T>(dbl::log(op.x));
    auto u = r.exp();
    r -= 2.0 * (u - op) / (u + op);

    return r;
}

template <class T> inline Double<T>
log10(const Double<T> &op)
{
    return op.log() / Double<T>::ln10;
}

template <class T> inline Double<T>
modf(const Double<T> &op, Double<T> *iptr)
{
    auto nearby = op.trunc();
    auto result = (op.isinf() ? Double<T>(0.0) : op - nearby).copysign(op);

    *iptr = nearby;
    return result;
}

template <class T> inline Double<T>
exp2(const Double<T> &op)
{
    return (op * Double<T>::ln2).exp();
}

template <class T> inline Double<T>
log2(const Double<T> &op)
{
    return op.log() * Double<T>::log2e;
}

//
// Power functions
//

template <class T> inline Double<T>
pow(const Double<T> &base, int exponent)
{
    Double<T> result = Double<T>(1);
    auto b = base;

    for (int i = dbl::abs(exponent); i; i >>= 1) {

        if (i & 1) result *= b;
        b *= b;
    }

    return exponent < 0 ? (1.0 / result) : result;
}

template <class T> inline Double<T>
pow(const Double<T> &base, const Double<T> &exponent)
{
    return (log(base) * exponent).exp();
}

template <class T> inline Double<T>
sqr(const Double<T> &x)
{
    return x * x;
}

template <class T> inline Double<T>
sqrt(const Double<T> &x)
{
    if (x.iszero()) return Double<T>(0.0);
    if (x.isnegative()) return Double<T>::nan();

    auto r = Double<T>(1.0 / dbl::sqrt(x.x));
    auto h = x * 0.5;

    r += (0.5 - h * r.sqr()) * r;
    r += (0.5 - h * r.sqr()) * r;
    r += (0.5 - h * r.sqr()) * r;

    return r * x;
}


//
// Error and gamma functions
//

// Not implemented


//
// Rounding and remainder functions
//

template <class T> inline Double<T>
ceil(const Double<T> &x)
{
    T hi = dbl::ceil(x.x);

    if (hi == x.x) {

        // Upper part is an integer
        T lo = dbl::ceil(x.y);
        return Double<T>::quickTwoSum(hi, lo);

    } else {

        return Double<T>(hi);
    }
}

template <class T> inline Double<T>
ceil(const Double<T> &x, int fracdigits)
{
    return x.ldexp10(fracdigits).ceil().ldexp10(-fracdigits);
    // return x.ceil(fracdigits);
}

template <class T> inline Double<T>
floor(const Double<T> &x)
{
    T hi = dbl::floor(x.x);

    if (hi == x.x) {

        // Upper part is an integer
        T lo = dbl::floor(x.y);
        return Double<T>::quickTwoSum(hi, lo);

    } else {

        return Double<T>(hi);
    }
}

template <class T> inline Double<T>
floor(const Double<T> &x, int fracdigits)
{
    return x.ldexp10(fracdigits).floor().ldexp10(-fracdigits);
    // return x.floor(fracdigits);
}

template <class T> inline Double<T>
fmod(const Double<T> &numer, const Double<T> &denom)
{
    if (denom.iszero()) return Double<T>::nan();
    if (numer.isfinite() && denom.isinf()) return numer;

    Double<T> tquot = (numer / denom).trunc();
    return numer - tquot * denom;
}

template <class T> inline Double<T>
trunc(const Double<T> &x)
{
    return dbl::isnegative(x) ? ceil(x) : floor(x);
}

template <class T> inline Double<T>
trunc(const Double<T> &x, int fracdigits)
{
    return x.ldexp10(fracdigits).trunc().ldexp10(-fracdigits);
}

template <class T> inline Double<T>
round(const Double<T> &x)
{
    if (x.isnegative()) {
        return (x - Double<T>(0.5)).ceil();
    } else {
        return (x + Double<T>(0.5)).floor();
    }
}

template <class T> inline Double<T>
round(const Double<T> &x, int fracdigits)
{
    return x.ldexp10(fracdigits).round().ldexp10(-fracdigits);
}

template <class T> inline Double<T>
roundEven(const Double<T> &x)
{
    if (x.isnegative()) {

        auto v1 = x - Double<T>(0.5);
        auto v2 = v1.ceil();

        if (v1 != v2) return v2;
        return x.fmod(2.0) < Double<T>(-1.0) ? v2 : v2 + Double<T>(1);

    } else {

        auto v1 = x + Double<T>(0.5);
        auto v2 = v1.floor();

        if (v1 != v2) return v2;
        return x.fmod(2.0) < Double<T>(1.0) ? v2 - Double<T>(1.0) : v2;
    }
}

template <class T> inline Double<T>
roundEven(const Double<T> &x, int fracdigits)
{
    return x.ldexp10(fracdigits).roundEven().ldexp10(-fracdigits);
}

template <class T> inline long
lround(const Double<T> &x)
{
    return round(x).to_long();
}

template <class T> inline long long
llround(const Double<T> &x)
{
    return round(x).to_long_double();
}

template <class T> inline Double<T>
rint(const Double<T> &x)
{
    auto result = dbl::nearbyint(x);

    // TODO:
    // The rint() functions do the same [as nearbyint], but will raise the
    // inexact exception (FE_INEXACT, checkable via fetestexcept(3)) when
    // the result differs in value from the argument.

    return result;
}

template <class T> inline Double<T>
rint(const Double<T> &x, int fracdigits)
{
    auto result = dbl::nearbyint(x, fracdigits);

    // TODO:
    // The rint() functions do the same [as nearbyint], but will raise the
    // inexact exception (FE_INEXACT, checkable via fetestexcept(3)) when
    // the result differs in value from the argument.

    return result;
}

template <class T> inline long
lrint(const Double<T> &x)
{
    return x.rint().to_long();
}

template <class T> inline long long
llrint(const Double<T> &x)
{
    return x.rint().to_long_long();
}

template <class T> inline Double<T>
nearbyint(const Double<T> &x)
{
    switch (fegetround()) {

        case FE_DOWNWARD:   return floor(x);
        case FE_TONEAREST:  return roundEven(x);
        case FE_TOWARDZERO: return trunc(x);
        default:            return ceil(x);
    }
}

template <class T> inline Double<T>
nearbyint(const Double<T> &x, int fracdigits)
{
    switch (fegetround()) {

        case FE_DOWNWARD:   return floor(x, fracdigits);
        case FE_TONEAREST:  return roundEven(x, fracdigits);
        case FE_TOWARDZERO: return trunc(x, fracdigits);
        default:            return ceil(x, fracdigits);
    }
}


//
// Floating-point manipulation functions
//

template <class T> inline Double<T>
copysign(const Double<T> &x, const Double<T> &y)
{
    return dbl::signbit(y) ? -x : x;
}


//
// Minimum, maximum, difference functions
//

template <class T> inline Double<T>
fdim(const Double<T> &x, const Double<T> &y)
{
    return (x > y) ? x - y : Double<T>();
}

template <class T> inline Double<T>
fmax(const Double<T> &x, const Double<T> &y)
{
    if (x.isnan()) return y;
    if (y.isnan()) return x;

    return x > y ? x : y;
}

template <class T> inline Double<T>
fmin(const Double<T> &x,const Double<T> &y)
{
    if (x.isnan()) return y;
    if (y.isnan()) return x;

    return x < y ? x : y;
}


//
// Other functions
//

template <class T> inline Double<T>
fabs(const Double<T> &x)
{
    return dbl::isnegative(x) ? -x : x;
}

template <class T> inline Double<T>
abs(const Double<T> &x)
{
    return fabs(x);
}

template <class T> inline Double<T>
fma(const Double<T> &x, const Double<T> &y, const Double<T> &z)
{
    return x * y + z;
}


//
// Classification functions
//

template <class T> inline bool
isfinite(const Double<T> &x)
{
    return isfinite(x.x);
}

template <class T> inline bool
isinf(const Double<T> &x)
{
    return isinf(x.x);
}

template <class T> inline bool
isnan(const Double<T> &x)
{
    return isnan(x.x);
}

template <class T> inline bool
isnormal(const Double<T> &x)
{
    return isnormal(x.x);
}

template <class T> inline bool
signbit(const Double<T> &x)
{
    return x.x != T(0.0) || x.y == T(0.0) ? dbl::signbit(x.x) : dbl::signbit(x.y);
}

template <class T> inline bool
iszero(const Double<T> &x)
{
    return x.x == T(0.0) && x.y == T(0.0);
}

template <class T> inline bool
isone(const Double<T> &x)
{
    return x.x == 1.0 && x.y == 0.0;
}

template <class T> inline bool
ispositive(const Double<T> &x)
{
    return x.x > 0.0;
}

template <class T> inline bool
isnegative(const Double<T> &x)
{
    return x.x < T(0.0);
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Double<T>& obj)
{
    os << "(" << obj.getX();
    os << ",";
    // os << (obj.getY() < T(0.0) ? " - " : " + ");
    // os << dbl::abs(obj.getY());
    os << obj.getY();
    os << ")";

    return os;
}

template <class T> inline const Double<T>
Double<T>::e          ("2.71828182 84590452 35360287 47135266 24977572 47093699 95957496 69676277");
template <class T> inline const Double<T>
Double<T>::log2e      ("1.44269504 08889634 07359924 68100189 21374266 45954152 98593413 54494069");
template <class T> inline const Double<T>
Double<T>::log10e     ("0.43429448 19032518 27651128 91891660 50822943 97005803 66656611 44537831");
template <class T> inline const Double<T>
Double<T>::pi         ("3.14159265 35897932 38462643 38327950 28841971 69399375 10582097 49445923");
template <class T> inline const Double<T>
Double<T>::inv_pi     ("0.31830988 61837906 71537767 52674502 87240689 19291480 91289749 53346881");
template <class T> inline const Double<T>
Double<T>::inv_sqrtpi ("0.56418958 35477562 86948079 45156077 25858440 50629328 99885684 4085a722");
template <class T> inline const Double<T>
Double<T>::ln2        ("0.69314718 05599453 09417232 12145817 65680755 00134360 25525412 06800195");
template <class T> inline const Double<T>
Double<T>::ln10       ("2.30258509 29940456 84017991 45468436 42076011 01488628 77297603 33279009");
template <class T> inline const Double<T>
Double<T>::sqrt2      ("1.41421356 23730950 48801688 72420969 80785696 71875376 94807317 66797379");
template <class T> inline const Double<T>
Double<T>::sqrt3      ("1.73205080 75688772 93527446 34150587 23669428 05253810 38062805 58069794");
template <class T> inline const Double<T>
Double<T>::inv_sqrt3  ("0.57735026 91896257 64509148 78050195 74556476 01751270 12687601 86023264");
template <class T> inline const Double<T>
Double<T>::egamma     ("0.57721566 49015328 60606512 09008240 24310421 59335939 92359880 57672349");
template <class T> inline const Double<T>
Double<T>::phi        ("1.61803398 87498948 48204586 83436563 81177203 09179805 76286213 54486227");

typedef Double<float> doublefloat;
typedef Double<double> doubledouble;
typedef Double<long double> longdoubledouble;
typedef Double<doublefloat> quadfloat;
typedef Double<doubledouble> quaddouble;

template<class T> inline int Double<T>::digits() {
    return T::digits() - 6;
}
template<> inline int Double<float>::digits() {
    return std::numeric_limits<float>::digits/ 2 + 1;
}
template<> inline int Double<double>::digits() {
    return std::numeric_limits<double>::digits/ 2 + 1;
}

}
