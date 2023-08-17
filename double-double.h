// -----------------------------------------------------------------------------
// double-double - A lightweight double-double arithmetic library in C++
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Published under the terms of the MIT License
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// DISCLAIMER: THIS IS AN EARLY BETA-VERSION. THE CODE IS NOT PRODUCTION-READY.
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

namespace dbl {

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

template <class T> Double<T> ceil(const Double<T> &x);
template <class T> Double<T> ceil(const Double<T> &x, int fracdigits);
template <class T> Double<T> floor(const Double<T> &x);
template <class T> Double<T> floor(const Double<T> &x, int fracdigits);
template <class T> Double<T> fmod(const Double<T> &numer, Double<T> denom);
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

template <class T> class Double {

    constexpr static bool useFma = true;

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
        return static_cast<long double>(x) + static_cast<long double>(y);
    }

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
        for (int i = 0; i < ldigits && l.abs() >= 1; i++) {

            l /= 10;
            Double<T> digit = l.modf(&l) * 10;
            result = digit.to_character() + result;
        }

        // Create a decimal point of necessary
        if (rdigits) result += '.';

        // Compute fractional digits
        for (int i = 0; i < rdigits; i++) {

            r *= 10;
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

        // std::cout << "   a = " << a << " b = " << b << std::endl;
        // std::cout << "   s = " << s << " v = " << v << " e = " << e << std::endl;
        return Double<T>(s,e);
    }

    static Double<T> split(T a) {

        auto digits = std::numeric_limits<T>::digits / 2 + 1;

        T t = (std::ldexp(T(1),digits) + 1) * a;
        T h = t - (t - a);
        T l = a - h;

        return Double<T>(h,l);
    }

    static Double<T> twoProd(T a, T b) {

        if constexpr (useFma) {

            auto p =  a * b;
            auto e = std::fma(a, b, -p);

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

            *this = signbit() ^ rhs.signbit() ? -0.0 : 0.0;
            return *this;
        }

        auto r = x / rhs.x;
        auto val = twoProd(r, rhs.x);
        auto e = (x - val.x - val.y + y - r * rhs.y) / rhs.x;

        *this = quickTwoSum(r, e);
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

    Double<T> exp() const
    {
        return dbl::exp(*this);
        /*
        auto n = std::round(x);
        auto w = *this - n;

        auto u = (((((((((((w +
                            156) * w + 12012) * w +
                          600600) * w + 21621600) * w +
                        588107520) * w + 12350257920) * w +
                      201132771840) * w + 2514159648000) * w +
                    23465490048000) * w + 154872234316800) * w +
                  647647525324800) * w + 1295295050649600;

        auto v = (((((((((((w -
                            156) * w + 12012) * w -
                          600600) * w + 21621600) * w -
                        588107520) * w + 12350257920) * w -
                      201132771840) * w + 2514159648000) * w -
                    23465490048000) * w + 154872234316800) * w -
                  647647525324800) * w + 1295295050649600;

        return e.pow(n) * (u / v);
        */
    }

    Double<T> frexp(int *exp) const
    {
        auto r = std::frexp(x, exp);
        auto e = std::ldexp(y, -(*exp));

        return Double<T>(r, e);
    }

    Double<T> frexp10(int *exp) const
    {
        *exp = iszero() ? 0 : 1 + (fabs().log10().floor().to_int());
        return *this * Double<T>(10).pow(-(*exp));
    }

    Double<T> ldexp(int exp) const
    {
        return Double<T>(std::ldexp(x, exp), std::ldexp(y, exp));
    }

    Double<T> ldexp10(int exp) const
    {
        return *this * Double<T>(10).pow(exp);
    }

    Double<T> log() const
    {
        if (isnegative()) return nan();
        if (iszero()) return -inf();

        auto r = Double<T>(std::log(x));
        auto u = r.exp();
        r -= 2.0 * (u - *this) / (u + *this);

        return r;
    }

    Double<T> log10() const
    {
        return log() / ln10;
    }

    Double<T> modf(Double<T> *iptr) const
    {
        auto nearby = trunc();
        auto result = (isinf() ? Double<T>(0.0) : *this - nearby).copysign(*this);

        *iptr = nearby;
        return result;
    }

    Double<T> exp2() const
    {
        return ((*this) * ln2).exp();
    }

    Double<T> log2() const
    {
        return log() * log2e;
    }


    //
    // Power functions
    //

    Double<T> pow(int n) const
    {
        Double<T> result = 1;
        auto b = *this;

        for (int i = std::abs(n); i; i >>= 1) {

            if (i & 1) result *= b;
            b *= b;
        }

        return n < 0 ? (1.0 / result) : result;
    }

    Double<T> pow(const Double<T> &rhs) const
    {
        return (log() * rhs).exp();
    }

    Double<T> sqr() const
    {
        return (*this) * (*this);
    }

    Double<T> sqrt() const
    {
        if (iszero()) return 0.0;
        if (isnegative()) return nan();

        auto r = Double<T>(1.0 / std::sqrt(x));
        auto h = *this * 0.5;

        r += (0.5 - h * r.sqr()) * r;
        r += (0.5 - h * r.sqr()) * r;
        r += (0.5 - h * r.sqr()) * r;

        return r * (*this);
    }


    //
    // Error and gamma functions
    //

    // Not implemented


    //
    // Rounding and remainder functions
    //

    Double<T> ceil() const
    {
        T hi = std::ceil(x);

        if (hi == x) {

            // Upper part is an integer
            T lo = std::ceil(y);
            return quickTwoSum(hi, lo);
            
        } else {

            return Double<T>(hi);
        }
    }

    Double<T> ceil(int fracdigits) const
    {
        return ldexp10(fracdigits).ceil().ldexp10(-fracdigits);
    }

    Double<T> floor() const
    {
        T hi = std::floor(x);

        if (hi == x) {

            // Upper part is an integer
            T lo = std::floor(y);
            return quickTwoSum(hi, lo);

        } else {

            return Double<T>(hi);
        }
    }

    Double<T> floor(int fracdigits) const
    {
        return ldexp10(fracdigits).floor().ldexp10(-fracdigits);
    }

    Double<T> fmod(Double<T> denom) const
    {
        if (denom.iszero()) return Double<T>::nan();
        if (isfinite() && denom.isinf()) return *this;

        Double<T> tquot = (*this / denom).trunc();
        return (*this) - tquot * denom;
    }

    Double<T> trunc() const
    {
        return isnegative() ? ceil() : floor();
    }

    Double<T> trunc(int fracdigits) const
    {
        return ldexp10(fracdigits).trunc().ldexp10(-fracdigits);
    }

    Double<T> round() const
    {
        if (isnegative()) {
            return (*this - Double<T>(0.5)).ceil();
        } else {
            return (*this + Double<T>(0.5)).floor();
        }
    }

    Double<T> round(int fracdigits) const
    {
        return ldexp10(fracdigits).round().ldexp10(-fracdigits);
    }

    Double<T> roundEven() const
    {
        if (isnegative()) {

            auto v1 = *this - Double<T>(0.5);
            auto v2 = v1.ceil();

            if (v1 != v2) return v2;
            return fmod(2.0) < -1 ? v2 : v2 + 1;

        } else {

            auto v1 = *this + Double<T>(0.5);
            auto v2 = v1.floor();

            if (v1 != v2) return v2;
            return fmod(2.0) < 1 ? v2 - 1 : v2;
        }
    }

    Double<T> roundEven(int fracdigits) const
    {
        return ldexp10(fracdigits).roundEven().ldexp10(-fracdigits);
    }

    long lround() const
    {
        return round().to_long();
    }

    long long llround() const
    {
        return round().to_long_double();
    }

    Double<T> rint() const
    {
        auto result = nearbyint();

        // TODO:
        // The rint() functions do the same [as nearbyint], but will raise the
        // inexact exception (FE_INEXACT, checkable via fetestexcept(3)) when
        // the result differs in value from the argument.

        return result;
    }

    Double<T> rint(int fracdigits) const
    {
        auto result = nearbyint(fracdigits);

        // TODO:
        // The rint() functions do the same [as nearbyint], but will raise the
        // inexact exception (FE_INEXACT, checkable via fetestexcept(3)) when
        // the result differs in value from the argument.

        return result;
    }

    long lrint() const
    {
        return rint().to_long();
    }

    long long llrint() const
    {
        return rint().to_long_long();
    }

    Double<T> nearbyint() const
    {
        switch (fegetround()) {

            case FE_DOWNWARD:   return floor();
            case FE_TONEAREST:  return roundEven();
            case FE_TOWARDZERO: return trunc();
            default:            return ceil();
        }
    }

    Double<T> nearbyint(int fracdigits) const
    {
        switch (fegetround()) {

            case FE_DOWNWARD:   return floor(fracdigits);
            case FE_TONEAREST:  return roundEven(fracdigits);
            case FE_TOWARDZERO: return trunc(fracdigits);
            default:            return ceil(fracdigits);
        }
    }


    //
    // Floating-point manipulation functions
    //

    Double<T> copysign(const Double<T> y) const
    {
        return (y.signbit()) ? -(*this) : (*this);
    }

    static Double<T> nan()
    {
        return std::numeric_limits<double>::quiet_NaN();
    }
    
    static Double<T> inf()
    {
        return std::numeric_limits<double>::infinity();
    }


    //
    // Minimum, maximum, difference functions
    //

    Double<T> fdim(const Double<T> y) const
    {
        return ((*this) > y) ? (*this) - y : Double<T>();
    }

    Double<T> fmax(const Double<T> y) const
    {
        if (isnan()) return y;
        if (y.isnan()) return *this;

        return *this > y ? *this : y;
    }

    Double<T> fmin(const Double<T> y) const
    {
        if (isnan()) return y;
        if (y.isnan()) return *this;

        return *this < y ? *this : y;
    }


    //
    // Other functions
    //

    Double<T> fabs() const
    {
        return isnegative() ? -(*this) : (*this);
    }

    Double<T> abs() const
    {
        return fabs();
    }


    //
    // Classification functions
    //

    bool isfinite() const { return std::isfinite(x); }
    bool isinf() const { return std::isinf(x); }
    bool isnan() const { return std::isnan(x); }
    bool isnormal() const { return std::isnormal(x); }
    bool signbit() const { return x != 0 || y == 0 ? std::signbit(x) : std::signbit(y); }

    bool iszero() const { return x == 0.0 && y == 0.0; }
    bool isone() const { return x == 1.0 && y == 0.0; }
    bool ispositive() const {  return x > 0.0; }
    bool isnegative() const {  return x < 0.0; }
};

//
// Exponential and logarithmic functions
//

template <class T> inline Double<T>
exp(const Double<T> &op)
{
    auto n = std::round(op.x);
    auto w = op - n;

    auto u = (((((((((((w +
                        156) * w + 12012) * w +
                      600600) * w + 21621600) * w +
                    588107520) * w + 12350257920) * w +
                  201132771840) * w + 2514159648000) * w +
                23465490048000) * w + 154872234316800) * w +
              647647525324800) * w + 1295295050649600;

    auto v = (((((((((((w -
                        156) * w + 12012) * w -
                      600600) * w + 21621600) * w -
                    588107520) * w + 12350257920) * w -
                  201132771840) * w + 2514159648000) * w -
                23465490048000) * w + 154872234316800) * w -
              647647525324800) * w + 1295295050649600;

    return Double<T>::e.pow(n) * (u / v);
}

template <class T> inline Double<T>
frexp(const Double<T> &op, int *exp)
{
    auto r = std::frexp(op.x, exp);
    auto e = std::ldexp(op.y, -(*exp));

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
    return Double<T>(std::ldexp(op.x, exp), std::ldexp(op.y, exp));
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

    auto r = Double<T>(std::log(op.x));
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

template <class T> inline Double<T>
ceil(const Double<T> &x)
{
    return x.ceil();
}

template <class T> inline Double<T>
ceil(const Double<T> &x, int fracdigits)
{
    return x.ceil(fracdigits);
}

template <class T> inline Double<T>
floor(const Double<T> &x)
{
    return x.floor();
}

template <class T> inline Double<T>
floor(const Double<T> &x, int fracdigits)
{
    return x.floor(fracdigits);
}





template <class T>
std::ostream& operator<<(std::ostream& os, const Double<T>& obj)
{
    os << obj.getX();
    os << (obj.getY() < 0 ? " - " : " + ");
    os << std::abs(obj.getY());

    return os;
}

typedef Double<float> doublefloat;
typedef Double<double> doubledouble;
typedef Double<long double> longdoubledouble;

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

}
