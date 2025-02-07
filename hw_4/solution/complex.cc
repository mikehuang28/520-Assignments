#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

//============================================================================
// hw4
//============================================================================

Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.real() + b.real(), a.imaginary() + b.imaginary());
}

Complex operator*(const Complex& a, const Complex& b) {
    double result_real = a.real() * b.real() - a.imaginary() * b.imaginary();
    double result_imag = a.real() * b.imaginary() + a.imaginary() * b.real();
    return Complex(result_real, result_imag);
}


bool operator==(const Complex& a, const Complex& b) {
    return (a.real() == b.real()) && (a.imaginary() == b.imaginary());
}