# XDouble

XDouble is a lightweight double-double arithmetic library written in C++. Double-double arithmetic increases the precision of floating-point operations by representing numbers as an unevaluated sum of two floating-point numbers of lower precision. The result is a floating-point format with nearly twice the accuracy of the base format and a performance considerably exceeding that of arbitrary-precision floating-point formats.

## Features

- Easy to integrate (header-only library).
- Interchangable base types due to a template-based design.
- Published under the MIT license.

## References:

- Hida, Y., Li, X. S., Bailey, D. H. (2000), *Quad-Double Arithmetic: Algorithms, Implementation, and Application*, Technical Report LBNL-46996

- double-double Python library by Juraj Sukop
  https://github.com/sukop/doubledouble/tree/master

- Fork of QD (2.3.17) by scibuilder
  https://github.com/scibuilder/QD

- David H. Bailey: High-Precision Software Directory
  https://www.davidhbailey.com/dhbsoftware

## Usage

The following example code demonstrates the basic usage of the XDouble library:

```C++
#include "xdouble.h"

typedef xdb::XDouble<double> doubledouble;

int main(int argc, char *argv[])
{
    doubledouble x = 0;

    for (int i = 1; i < 1000000; i += 4) {

        x += (doubledouble)4.0 / (doubledouble)i;
        x -= (doubledouble)4.0 / (doubledouble)(i + 2);
    }

    std::cout << x.to_string(40) << std::endl;
}
```
Output:
```
3.1415906535897932404626433832467923686464
```

## APIs

The new `DoubleX` types are intended to be usable similar to the standard types `float`, `double` and `long double`. However, they differ from the standard types in being real objects. So if `x` is one of the new `DoubleX` types, you can write a statement such as `x.sqrt()`, which is not possible with the standard types.

To simplify the substitution of standard types, the DoubleX library also provides a non-OOP API that is mostly compatible with the standard math library. Therefore, it is also possible to write `sqrt(x)` instead of `x.sqrt()`. 

The following examples demonstrate the usage of the non-OOP API:

```C++
#include "xdouble.h"

typedef xdb::XDouble<double> doubledouble;

int main(int argc, char *argv[])
{
    double x1(2.0);
    double x2 = std::sqrt(x1);

    doubledouble y1(2.0);
    doubledouble y2 = xdb::sqrt(y1);

    std::cout << "double:       " << std::setprecision(41) << x2 << std::endl;
    std::cout << "doubledouble: " << y2.to_string(40) << std::endl;
    std::cout << "Exact:        1.4142135623730950488016887242096980785696..." << std::endl;
}
``````

Output:
```
double:       1.4142135623730951454746218587388284504414
doubledouble: 1.4142135623730950488016887242096791487523
Exact:        1.4142135623730950488016887242096980785696...
```

## Project status

Please do not use the library in production code, as it is not sufficiently tested. Arithmetic libraries must provide a high degree of correctness, which I cannot guarantee at the moment. Although there are a lot of regression tests in the test folder, more testing is absolutely necessary before the library can be trusted.

## Open issues

The XDouble type is generic enough such that one XDouble type can be used as a base type for another XDouble type. The following code line shows how such a nested type can be setup:
```C++
typedef xdb::XDouble<xdb::XDouble<double>> quaddouble;
``````
Theoretically, this kind of type-nesting should lead to ever growing accuracies. However, it turns out that nesting XDouble types inside each other leads to accuracy problems when performing certain calculations. At the moment, I'm unsure where these accuracy problems are coming from. They may be due to a bug, or they may be due to a mathematical property the base type must satisfy but the DoubleX types do not.
