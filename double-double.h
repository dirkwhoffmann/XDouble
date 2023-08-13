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

#include <stdio.h>
#include <limits>
#include <cmath>
#include <iostream>

template <class T>
class Double {

    constexpr static bool useFma = true;

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

    // TODO: How can we treat T properly here?
    Double<T> e() const {
        return { (T)3.141592653589793, (T)1.2246467991473532e-16 };
    }


    //
    // Accessing
    //

    T getX() const { return x; }
    T getY() const { return y; }


    //
    // Converting
    //

    float asFloat() const
    {
        return (float)asLongDouble();
    }

    double asDouble() const
    {
        return (double)asLongDouble();
    }

    long double asLongDouble() const
    {
        return (long double)x + (long double)y;
    }


    //
    // Comparing
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

    /*
    operator bool() const
    {
        return x && y;
    }
    */

    //
    // Calculating
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
        sum.y = y + rhs.y;
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

    Double<T> log() const
    {
        auto r = Double<T>(std::log(x));
        auto u = r.exp();
        r -= 2.0 * (u - *this) / (u + *this);

        return r;
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

template <class T>
std::istream& operator>>(std::istream& is, Double<T>& obj)
{
    // read obj from stream

    // if( /* no valid object of T found in stream */ )
    //  is.setstate(std::ios::failbit);

    return is;
}

typedef Double<double> doubledouble; 
typedef Double<long double> longdoubledouble;
