#include "complex.h"
#include <math.h>

// Add two complex numbers
complex add(complex a, complex b) {
    complex result;
    result.real = a.real + b.real;
    result.im = a.im + b.im;
    return result;
}

// Negate a complex number
complex negate(complex a) {
    complex result;
    result.real = -a.real;
    result.im = -a.im;
    return result;
}

// Multiply two complex numbers
complex multiply(complex a, complex b) {
    complex result;
    result.real = a.real * b.real - a.im * b.im;
    result.im = a.real * b.im + a.im * b.real;
    return result;
}

// Compute the magnitude of a complex number
double magnitude(complex a) {
    return sqrt(a.real * a.real + a.im * a.im);
}
