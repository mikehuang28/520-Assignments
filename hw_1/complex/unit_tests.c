#include <stdio.h>
#include <assert.h>
#include "complex.h"

// Function to print complex numbers for debugging purposes
void print_complex(complex c) {
    printf("%.2f + %.2fi\n", c.real, c.im);
}

// Test for adding two complex numbers
void test_addition() {
    complex a = { 2.0, 3.0 };
    complex b = { 4.0, 5.0 };
    complex result = add(a, b);
    assert(result.real == 6.0); // (2+4) + (3+5) = 6 + 8i
    assert(result.im == 8.0);
    printf("Addition test passed!\n");
}

// Test for negating a complex number
void test_negation() {
    complex a = { 2.0, 3.0 };
    complex result = negate(a);
    assert(result.real == -2.0); // Negating (2+3i) should give (-2 - 3i)
    assert(result.im == -3.0);
    printf("Negation test passed!\n");
}

// Test for multiplying two complex numbers
void test_multiplication() {
    complex a = { 2.0, 3.0 };
    complex b = { 4.0, 5.0 };
    complex result = multiply(a, b);
    assert(result.real == -7.0);  // (2 + 3i)(4 + 5i) = -7 + 22i
    assert(result.im == 22.0);
    printf("Multiplication test passed!\n");
}

// Test for computing the magnitude of a complex number
void test_magnitude() {
    complex a = { 3.0, 4.0 };
    double result = magnitude(a);
    assert(result == 5.0);  // Magnitude of (3 + 4i) = sqrt(3^2 + 4^2) = 5
    printf("Magnitude test passed!\n");
}



