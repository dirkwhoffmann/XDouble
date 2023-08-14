// -----------------------------------------------------------------------------
// double-double - A lightweight double-double arithmetic library in C++
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Published under the terms of the MIT License
// -----------------------------------------------------------------------------

/* Double-double arithmetic increases the accuracy of floating-point operations
 * by representing numbers as an unevaluated sum of two floating-point numbers
 * of lower precision.
 *
 * References:
 *
 *   Hida, Y., Li, X. S., Bailey, D. H. (2000), "Quad-Double Arithmetic:
 *   Algorithms, Implementation, and Application", Technical Report LBNL-46996
 *
 *   double-double Python library by Juraj Sukop:
 *   https://github.com/sukop/doubledouble/tree/master
 *
 *   Fork of QD (2.3.17) by scibuilder:
 *   https://github.com/scibuilder/QD
 */

#pragma once

#include <cstdio>
#include <limits>
#include <cmath>
#include <cfenv>
#include <iostream>
#include <algorithm>
#include <iomanip>

template <class T>
class Double {

    constexpr static bool useFma = false;

    T x, y;

public:

    //
    // Constructors
    //

    Double<T>() noexcept : x(0), y(0) { }
    Double<T>(T x) noexcept : x(x), y(0) { }
    Double<T>(T x, T y) noexcept : x(x), y(y) { }
    Double<T>(const Double<T>& other) noexcept : Double<T>() { x = other.x; y = other.y; }
    Double<T>(Double<T>&& other) noexcept : Double<T>() { swap(*this, other); }

    Double<T>(const std::string &s) noexcept : Double<T>()
    {
        Double<T> l, r;
        bool neg = false;

        std::string copy(s);

        for (auto &ch : copy) {

            if (ch == '-') neg = !neg;
            if (ch == '.') break;
            if (ch >= '0' && ch <= '9') l = l * Double<T>(10) + Double<T>(ch - '0');
        }

        if (auto pos = copy.find("."); pos != std::string::npos) {

            std::reverse(copy.begin() + pos + 1, copy.end());
            for (auto &ch : copy) {

                if (ch >= '0' && ch <= '9') r = (r + Double<T>(ch - '0')) / Double<T>(10);
            }
        }
        *this = neg ? -(l + r) : (l + r);
    }

    Double<T>& operator=(Double<T> rhs)
    {
        swap(*this, rhs);
        return *this;
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

    // DEPRECATED
    static const Double<T> e;
    static const Double<T> ln2;
    static const Double<T> ln10;
    static const Double<T> pi;

    static const Double<T> e_v;
    static const Double<T> log2e_v;
    static const Double<T> log10e_v;
    static const Double<T> pi_v;
    static const Double<T> inv_pi_v;
    static const Double<T> inv_sqrtpi_v;
    static const Double<T> ln2_v;
    static const Double<T> ln10_v;
    static const Double<T> sqrt2_v;
    static const Double<T> sqrt3_v;
    static const Double<T> inv_sqrt3_v;
    static const Double<T> egamma_v;
    static const Double<T> phi_v;

    // static const Double<T> nan;


    //
    // Accessors
    //

    T getX() const { return x; }
    T getY() const { return y; }


    //
    // Cast operators and conversion functions
    //

    operator int() const { return static_cast<int>(static_cast<long double>(*this)); }
    operator long() const { return static_cast<long>(static_cast<long double>(*this)); }
    operator float() const { return static_cast<float>(static_cast<long double>(*this)); }
    operator double() const { return static_cast<double>(static_cast<long double>(*this)); }
    operator long double() const { return static_cast<long double>(x) + static_cast<long double>(y); }

    std::string to_string(int digits) const
    {
        std::string result;


        // Split number l.r into pre-decimal and fractional part
        Double<T> l;
        Double<T> r = modf(&l);

        for (int i = 0; i < 100; i++) {

            Double<T> ii;
            if (l.abs() < Double<T>(1)) break;
            l /= 10;
            ii = l.modf(&l);
            result = std::to_string(int(std::round((double)ii * 10))) + result;
        }

        result += '.';
        for (int i = 0; i < digits; i++) {

            Double<T> ii;
            r *= 10;
            r = r.modf(&ii);
            result = result + std::to_string(int((double)ii));
        }

        return result;
    }


    //
    // Comparison operators
    //

    bool operator==(const Double<T>& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const Double<T>& rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const Double<T>& rhs) const
    {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }

    bool operator>(const Double<T>& rhs) const
    {
        return rhs < *this;
    }

    bool operator<=(const Double<T>& rhs) const
    {
        return !(*this > rhs);
    }

    bool operator>=(const Double<T>& rhs) const
    {
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
        auto sum = twoSum(x, rhs.x);
        sum.y += y + rhs.y;
        *this = quickTwoSum(sum.x, sum.y);
        return *this;
    }

    Double<T> operator+(const Double<T> &rhs) const
    {
        Double<T> result;
        result = *this;
        result += rhs;

        return result;
    }

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

    Double<T> &operator*=(const Double<T> &rhs)
    {
        auto val = twoProd(x, rhs.x);
        val.y += x * rhs.y + y * rhs.x;

        *this = quickTwoSum(val.x, val.y);
        return *this;
    }

    Double<T> operator*(const Double<T> &rhs) const
    {
        auto result = *this;
        result *= rhs;

        return result;
    }

    Double<T> &operator/=(const Double<T> &rhs)
    {
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
        auto result = *this;
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

        return e.power(n) * (u / v);
    }

    Double<T> frexp(int *exp) const
    {
        auto r = std::frexp(x, exp);
        auto e = y.ldexp(-(*exp));

        return Double<T>(r, e);
    }

    Double<T> frexp10(int *exp) const
    {
        *exp = is_zero() ? 0 : 1 + int(fabs().log10().floor());
        return pow(static_cast<Double<T>>(10.0), -(*exp));
    }

    Double<T> ldexp(int exp) const
    {
        return Double<T>(std::ldexp(x, exp), std::ldexp(y, exp));
    }

    Double<T> log() const
    {
        auto r = Double<T>(std::log(x));
        auto u = r.exp();
        r -= 2.0 * (u - *this) / (u + *this);

        return r;
    }

    Double<T> log10() const
    {
        return log() / ln10_v;
    }

    Double<T> modf(Double<T> *iptr) const
    {
        auto nearby = nearbyint(FE_TOWARDZERO);
        auto result = (isinf() ? Double<T>(0.0) : *this - nearby).copysign(*this);

        *iptr = nearby;
        return result;
    }

    Double<T> exp2() const
    {
        return ((*this) * ln2_v).exp();
    }

    Double<T> log2() const
    {
        return log() * log2e_v;
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

        return n < 0 ? 1.0 / result : result;
    }

    Double<T> pow(const Double<T> &rhs) const
    {
        return exp(log() * rhs);
    }

    Double<T> sqr() const
    {
        return (*this) * (*this);
    }

    Double<T> sqrt() const
    {
        if (is_zero()) return 0.0;
        if (is_negative()) return nan;

        auto r = Double<T>(1.0) / Double<T>(std::sqrt(x));
        auto h = *this * Double<T>(0.5);

        r += ((0.5 - h * r.sqr()) * r);
        r += ((0.5 - h * r.sqr()) * r);
        r += ((0.5 - h * r.sqr()) * r);
        return r;
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

            T lo = std::ceil(y);
            return quickTwoSum(hi, lo);

        } else {

            return Double<T>(hi);
        }
    }

    Double<T> floor() const
    {
        T hi = std::floor(x);

        if (hi == x) {

            T lo = std::floor(y);
            return quickTwoSum(hi, lo);

        } else {

            return Double<T>(hi);
        }
    }

    Double<T> fmod(Double<T> denom) const
    {
        Double<T> tquot = (*this / denom).trunc();
        return (*this) - tquot * denom;
    }

    Double<T> trunc() const
    {
        return is_negative() ? ceil() : floor();
    }

    Double<T> round() const
    {
        return (*this + Double<T>(0.5)).floor();
    }

    long lround() const
    {
        return (long)round();
    }

    long long llround() const
    {
        return (long long)round();
    }

    Double<T> rint() const
    {
        switch (fegetround()) {

            case FE_DOWNWARD:   return floor();
            case FE_TONEAREST:  return round();
            case FE_TOWARDZERO: return trunc();
            case FE_UPWARD:     return ceil();

            default:
                assert(false);
                return 0;
        }
    }

    long lrint() const
    {
        return (long)rint();
    }

    long long llrint() const
    {
        return (long long)rint();
    }

    Double<T> nearbyint() const
    {
        T hi = std::nearbyint(x);

        if (hi == x) {

            // Upper part is an integer
            T lo = std::nearbyint(y);
            return quickTwoSum(hi, lo);

        } else {

            // Upper part is not an integer
            if (std::abs(hi - x) == 0.5 && y < 0.0) hi -= 1.0;
            return Double<T>(hi);
        }
    }

    Double<T> nearbyint(int mode) const
    {
        int save_round = std::fegetround();
        std::fesetround(mode);
        auto result = nearbyint();
        std::fesetround(save_round);

        return result;
    }


    //
    // Floating-point manipulation functions
    //

    Double<T> copysign(const Double<T> y) const
    {
        return (y.signbit()) ? -(*this) : (*this);
    }

    Double<T> nan() const
    {
        return std::numeric_limits<double>::quiet_NaN();
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
        return y.fmax(*this);
    }


    //
    // Other functions
    //

    Double<T> fabs() const
    {
        return is_negative() ? -(*this) : (*this);
    }

    Double<T> abs() const
    {
        return fabs();
    }

    Double<T> fma(const Double<T> &y, const Double<T> &z) const
    {
        return (*this) * y + z;
    }


    //
    // Classification functions
    //

    bool isfinite() const { return std::isfinite(x); }
    bool isinf() const { return std::isinf(x); }
    bool isnan() const { return std::isnan(x); }
    bool isnormal() const { return std::isnormal(x); }
    bool signbit() const { return x < 0.0; }

    bool is_zero() const { return (x == 0.0); }
    bool is_one() const { return x == 1.0 && y == 0.0; }
    bool is_positive() const {  return x > 0.0; }
    bool is_negative() const {  return x < 0.0; }
};

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
Double<T>::e   ("2.71828182 84590452 35360287 47135266 24977572 47093699 95957496 69676277");
template <class T> inline const Double<T>
Double<T>::ln2 ("0.69314718 05599453 09417232 12145817 65680755 00134360 25525412 06800195");
template <class T> inline const Double<T>
Double<T>::ln10("2.30258509 29940456 84017991 45468436 42076011 01488628 77297603 33279010");
template <class T> inline const Double<T>
Double<T>::pi  ("3.14159265 35897932 38462643 38327950 28841971 69399375 10582097 49445923");

template <class T> inline const Double<T>
Double<T>::ln10_v  ("2.3025 85092994 04568401 79914546 84364207 60110148 86287729 76033328");
