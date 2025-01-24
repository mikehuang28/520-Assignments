#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
    double real;
    double im;
} complex;

// Function prototypes
complex add(complex a, complex b);
complex negate(complex a);
complex multiply(complex a, complex b);
double magnitude(complex a);

#endif // COMPLEX_H
