#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
// #include "point.h"
#include "gtest/gtest.h"
#include "complex.h"

namespace {


    // TEST(TypedArray, Construction) {
    //     TypedArray<Point> b;
    //     b.set(0, Point(1,2,3));
    //     b.set(1, Point(2,3,4));
    //     b.set(20, Point(3,4,5));
    //     EXPECT_EQ(b.get(0).x, 1);
    //     EXPECT_EQ(b.get(1).y, 3);
    //     EXPECT_EQ(b.get(20).z, 5);
    // }

    // TEST(TypedArray, Defaults) {
    //     TypedArray<Point> x;
    //     Point& y = x.get(3);
    //     std::cout << x << "\n";
    //     EXPECT_DOUBLE_EQ(y.magnitude(), 0.0);
    // }

    // TEST(TypedArray, Matrix) {

    //     TypedArray<TypedArray<double>> m;

    //     for (int i=0; i<3; i++) {
    //         for (int j=0; j<3; j++) {
    //             m.get(i).set(j,3*i+j);
    //         }
    //     }

    //     std::cout << m << "\n";

    //     for (int i=0; i<3; i++) {
    //         for (int j=0; j<3; j++) {
    //             EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
    //         }
    //     }

    // }

    // TEST(TypedArray,CopyElementsInSet1) {
    //     TypedArray<Point> b;
    //     Point p(1,2,3);
    //     b.set(0, p);
    //     p.x = 4;
    //     EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    // }

    // TEST(TypedArray,CopyElementsInSet2) {
    //     TypedArray<TypedArray<double>> m;
    //     TypedArray<double> x;
    //     x.set(0,0);
    //     m.set(0,x);
    //     x.set(0,-1);
    //     EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
    //                                            // then we would expect m[0][0]
    //                                            // to be x[0], which we changed
    //                                            // to -1.
    // }


    // hw4
    // printf("Testing typed array\n");
    TEST(TypedArray, PushAndPopElements) {
        TypedArray<int> arr;

        // push
        arr.push(10);
        arr.push(20);
        arr.push(30);
        EXPECT_EQ(arr.size(), 3);

        // pop
        EXPECT_EQ(arr.pop(), 30);
        EXPECT_EQ(arr.size(), 2);
        EXPECT_EQ(arr.pop(), 20);
        EXPECT_EQ(arr.size(), 1);
        EXPECT_EQ(arr.pop(), 10);
        EXPECT_EQ(arr.size(), 0);
    }

    TEST(TypedArray, PushAndPopFront) {
        TypedArray<int> arr;

        arr.push_front(10);
        arr.push_front(20);
        arr.push_front(30);

        // Check size after pushing elements to the front
        EXPECT_EQ(arr.size(), 3);

        // Pop elements from the front and check if the values match
        EXPECT_EQ(arr.pop_front(), 30);
        EXPECT_EQ(arr.size(), 2);
        EXPECT_EQ(arr.pop_front(), 20);
        EXPECT_EQ(arr.size(), 1);
        EXPECT_EQ(arr.pop_front(), 10);
        EXPECT_EQ(arr.size(), 0);
    }

    TEST(TypedArray, PushFrontAfterPushBack) {
        TypedArray<int> arr;

        // Push elements to the back
        arr.push(10);
        arr.push(20);

        // Push an element to the front
        arr.push_front(30);

        // Check the size and the order of elements
        EXPECT_EQ(arr.size(), 3);
        EXPECT_EQ(arr.pop_front(), 30); // Front should be 30
        EXPECT_EQ(arr.pop(), 20);       // Then 20 from the back
        EXPECT_EQ(arr.pop(), 10);       // And finally 10
    }

    TEST(TypedArray, PopBackAfterPushFront) {
        TypedArray<int> arr;

        // Push an element to the front
        arr.push_front(10);
        arr.push_front(20);

        // Push elements to the back
        arr.push(30);
        arr.push(40);

        // Pop elements from the back and check the values
        EXPECT_EQ(arr.pop(), 40);  // Last pushed to back
        EXPECT_EQ(arr.pop(), 30);  // Second last pushed to back

        // Pop from the front
        EXPECT_EQ(arr.pop_front(), 20); // First pushed to front
        EXPECT_EQ(arr.pop_front(), 10); // Second pushed to front

        EXPECT_EQ(arr.size(), 0);
    }

    TEST(TypedArray, Concat) {
        TypedArray<int> a;
        a.set(0, 0);
        a.set(1, 1);

        // Concatenate a with itself
        TypedArray<int> b = a.concat(a);
        EXPECT_EQ(b.size(), 4);  // [0, 1, 0, 1]
        EXPECT_EQ(b.safe_get(0), 0);
        EXPECT_EQ(b.safe_get(1), 1);
        EXPECT_EQ(b.safe_get(2), 0);
        EXPECT_EQ(b.safe_get(3), 1);

        // Concatenate the result with itself again
        TypedArray<int> c = b.concat(b);
        EXPECT_EQ(c.size(), 8);  // [0, 1, 0, 1, 0, 1, 0, 1]
        EXPECT_EQ(c.safe_get(0), 0);
        EXPECT_EQ(c.safe_get(1), 1);
        EXPECT_EQ(c.safe_get(2), 0);
        EXPECT_EQ(c.safe_get(3), 1);
        EXPECT_EQ(c.safe_get(4), 0);
        EXPECT_EQ(c.safe_get(5), 1);
        EXPECT_EQ(c.safe_get(6), 0);
        EXPECT_EQ(c.safe_get(7), 1);

        // Ensure the original arrays are unchanged
        EXPECT_EQ(a.size(), 2);  // Array a should still have 2 elements: [0, 1]
        EXPECT_EQ(b.size(), 4);  // Array b should still have 4 elements: [0, 1, 0, 1]
    }

    TEST(TypedArray, Reverse) {
        TypedArray<int> arr;
        arr.set(0, 1);
        arr.set(1, 2);
        arr.set(2, 3);
        arr.set(3, 4);

        arr.reverse();

        // Check if the array has been reversed
        EXPECT_EQ(arr.get(0), 4);
        EXPECT_EQ(arr.get(1), 3);
        EXPECT_EQ(arr.get(2), 2);
        EXPECT_EQ(arr.get(3), 1);

        // Verify that chaining works as expected
        TypedArray<int> reversedArr = arr.reverse();
        EXPECT_EQ(reversedArr.get(0), 1);
        EXPECT_EQ(reversedArr.get(1), 2);
        EXPECT_EQ(reversedArr.get(2), 3);
        EXPECT_EQ(reversedArr.get(3), 4);
    }

    TEST(TypedArray, OperatorPlus) {
        TypedArray<int> a;
        a.set(0, 0);
        a.set(1, 1);

        TypedArray<int> b = a + a + a;

        // Check if the concatenated array has the expected elements
        EXPECT_EQ(b.get(0), 0);
        EXPECT_EQ(b.get(1), 1);
        EXPECT_EQ(b.get(2), 0);
        EXPECT_EQ(b.get(3), 1);
        EXPECT_EQ(b.get(4), 0);
        EXPECT_EQ(b.get(5), 1);
    }


    // test complex
    // printf("Testing complex\n");
    TEST(Examples,Complex) {
        Complex x(1,2), y(3);
    }

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }

    // TEST(Examples,Templates) {
    //     EXPECT_EQ(compare(1.0, 2.0), -1);
    //     EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
    // }

    // TEST(ComplexTest, RealImaginaryConjugate) {
    //     Complex c1(3.0, 4.0);
    //     EXPECT_DOUBLE_EQ(c1.real(), 3.0);
    //     EXPECT_DOUBLE_EQ(c1.imaginary(), 4.0);

    //     Complex c2 = c1.conjugate();
    //     EXPECT_DOUBLE_EQ(c2.real(), 3.0);
    //     EXPECT_DOUBLE_EQ(c2.imaginary(), -4.0);
    // }

    TEST(ComplexTest, Addition) {
        Complex c1(3.0, 4.0);
        Complex c2(1.0, 2.0);
        Complex result = c1 + c2;
        EXPECT_DOUBLE_EQ(result.real(), 4.0);
        EXPECT_DOUBLE_EQ(result.imaginary(), 6.0);
    }

    TEST(ComplexTest, Multiplication) {
        Complex c1(3.0, 4.0);
        Complex c2(1.0, 2.0);
        Complex result = c1 * c2;
        EXPECT_DOUBLE_EQ(result.real(), -5.0);
        EXPECT_DOUBLE_EQ(result.imaginary(), 10.0);
    }

    TEST(ComplexTest, Equality) {
        Complex c1(3.0, 4.0);
        Complex c2(3.0, 4.0);
        Complex c3(1.0, 2.0);

        EXPECT_TRUE(c1 == c2);
        EXPECT_FALSE(c1 == c3);
    }

    TEST(ComplexTest, Magnitude) {
        Complex c(3.0, 4.0);
        EXPECT_DOUBLE_EQ(c.magnitude(), 5.0);
    }
}