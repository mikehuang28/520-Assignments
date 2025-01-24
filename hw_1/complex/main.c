#include "complex.h"
// #include "unit_tests.c"
#include <stdio.h>

int main() {
    // Run tests for all complex number functions

    // Test for adding two complex numbers
    test_addition();

    // Test for negating a complex number
    test_negation();

    // Test for multiplying two complex numbers
    test_multiplication();

    // Test for computing the magnitude of a complex number
    test_magnitude();

    printf("All tests passed!\n");
    return 0;
}

// #include <stdio.h>
// #include "complex.h"
// #include "gtest/gtest.h"

// GTEST_API_ int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
