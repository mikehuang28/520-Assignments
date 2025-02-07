#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
    public:
    // Constructors
    Complex(double x, double y) : re(x), im(y) {}
    Complex(double a) : re(a), im(0) {};

    // Methods
    double real() const { return re; }
    double imaginary() const { return im; }
    Complex conjugate() const { return Complex(re, -im); }
    double magnitude() const;

    private:
    double re, im;
};

// overloaded operators
bool operator<(const Complex& a, const Complex& b);
Complex operator+(const Complex& a, const Complex& b);
Complex operator*(const Complex& a, const Complex& b);
bool operator==(const Complex& a, const Complex& b);

#endif