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
 */

#pragma once

#include <cstdio>
#include <limits>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>

template <class T>
class Double {

    constexpr static bool useFma = false;

    T x, y;

public:

    //
    // Constructing
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

    friend void swap(Double<T>& first, Double<T>& second) noexcept
    {
        std::swap(first.x, second.x);
        std::swap(first.y, second.y);
    }

    Double<T>& operator=(Double<T> rhs)
    {
        swap(*this, rhs);
        return *this;
    }


    //
    // Constants
    //

    static const Double<T> e;
    static const Double<T> ln2;
    static const Double<T> ln10;
    static const Double<T> pi;


    //
    // Accessors
    //

    T getX() const { return x; }
    T getY() const { return y; }


    //
    // Analyzers
    //

    bool signbit() const { return x < 0.0; }

    bool is_zero() const { return (x == 0.0); }
    bool is_one() const { return x == 1.0 && y == 0.0; }
    bool is_positive() const {  return x > 0.0; }
    bool is_negative() const {  return x < 0.0; }


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

        // std::cout << "left: " << l << " right: " << r << std::endl;

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
            // std::cout << "ii = " << ii << std::endl;
            result = result + std::to_string(int((double)ii));
        }

        return result;
    }


    //
    // Comparison functions
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

        return e().power(n) * (u / v);
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

    Double<T> modf(Double<T> *iptr) const
    {
        T ix, iy;

        auto fx = std::modf(x, &ix);
        auto fy = std::modf(y, &iy);

        *iptr = Double<T>(ix, iy);
        return Double<T>(fx, fy);
    }


    //
    // Power functions
    //

    Double<T> pow(const Double<T> &rhs) const
    {
        return exp(log() * rhs);
    }

    Double<T> power(int n) const
    {
        Double<T> result = 1;
        auto b = *this;

        for (int i = std::abs(n); i; i >>= 1) {

            if (i & 1) result *= b;
            b *= b;
        }

        return n < 0 ? 1.0 / result : result;
    }


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


    //
    // Other functions
    //

    Double<T> abs() const
    {
        return is_negative() ? -(*this) : (*this);
    }

    Double<T> fabs() const
    {
        return abs();
    }

    Double<T> fma(const Double<T> &y, const Double<T> &z) const
    {
        return (*this) * y + z;
    }

    Double<T> nearbyInt() const
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
