#include <stdio.h>
#include <assert.h>
#include "dynamic_array.h"

int main() {
    DynamicArray *da = DynamicArray_new();
    DynamicArray_push(da, 5.0);
    DynamicArray_push(da, -2.0);
    DynamicArray_push(da, 8.0);
    DynamicArray_push(da, 3.0);
    DynamicArray_push(da, 10.0);
    DynamicArray_push(da, 4.0);
    DynamicArray_push(da, 1.0);
    DynamicArray_push(da, -1.0);
    DynamicArray_push(da, 8.0);

    // part 1
    printf("Part 1: Methods _min, _max, _mean, _median and _sum\n");
    printf("Original Min: %lf\n", DynamicArray_min(da));
    printf("Original Max: %lf\n", DynamicArray_max(da));
    printf("Original Sum: %lf\n", DynamicArray_sum(da));
    printf("Original Mean: %lf\n", DynamicArray_mean(da));
    printf("Original Median: %lf\n", DynamicArray_median(da));
    assert(DynamicArray_min(da) == -2.0);  // Expected: -2.0
    assert(DynamicArray_max(da) == 10.0);  // Expected: 10.0
    assert(DynamicArray_sum(da) == 36.0);  // Expected: 36.0
    assert(DynamicArray_mean(da) == 4.0);  // Expected: 4.00
    assert(DynamicArray_median(da) == 4.0);  // Expected: 4.00

    // part 2
    printf("\nPart 2: Methods _first, and _last\n");
    printf("Last Element: %lf\n", DynamicArray_last(da));
    printf("First Element: %lf\n", DynamicArray_first(da));
    assert(DynamicArray_last(da) == 8.0);  // Expected: 8.00
    assert(DynamicArray_first(da) == 5.0);  // Expected: 5.00


    // part 3
    printf("\nPart 3: Method _copy\n");
    DynamicArray *copy = DynamicArray_copy(da);
    if (copy == NULL) {
        printf("Failed to copy the dynamic array.\n");
        DynamicArray_destroy(da);
        return 1;
    }
    printf("Copy Min: %lf\n", DynamicArray_min(copy));  // Expected: -2.0
    printf("Copy Max: %lf\n", DynamicArray_max(copy));  // Expected: 10.0
    printf("Copy Sum: %lf\n", DynamicArray_sum(copy));  // Expected: 36.0
    printf("Copy Mean: %lf\n", DynamicArray_mean(copy));  // Expected: 4.0
    printf("Copy Median: %lf\n", DynamicArray_median(copy));  // Expected: 4.00

    // Modify the copy to ensure it's independent of the original
    DynamicArray_push(copy, 9.0);
    printf("After modifying copy:\n");
    printf("Original Sum: %lf\n", DynamicArray_sum(da));
    printf("Copy Sum: %lf\n", DynamicArray_sum(copy));
    assert(DynamicArray_sum(da) == 36.0);  // Expected: 36.0 (unchanged)
    assert(DynamicArray_sum(copy) == 45.0);    // Expected: 45.0 (changed)


    // part 4
    printf("\nPart 4: Method _range\n");
    DynamicArray *a = DynamicArray_range(0, 1, 0.1);
    for (int i = 0; i < DynamicArray_size(a); i++) {
        printf("%lf ", DynamicArray_get(a, i)); // 0.000000 0.100000 0.200000 0.300000 0.400000 0.500000 0.600000 0.700000 0.800000 0.900000 1.000000
    }
    printf("\n");



    // part 5
    printf("\nPart 5: Method _concat\n");
    DynamicArray *d1 = DynamicArray_range(0, 10, 1);
    DynamicArray *d2 = DynamicArray_range(0, 1, 0.1);
    DynamicArray *concat = DynamicArray_concat(d1, d2);


    for (int i = 0; i < DynamicArray_size(concat); i++) {
        printf("%f ", DynamicArray_get(concat, i));
    }
    printf("\n");

    assert(DynamicArray_size(concat) == DynamicArray_size(d1) + DynamicArray_size(d2));

    // part 6
    printf("\nPart 6: Method _take\n");
    DynamicArray * t1 = DynamicArray_range(1, 5, 1);
    DynamicArray * t2 = DynamicArray_take(t1, 2);  /* yields [ 1, 2 ] */
    DynamicArray * t3 = DynamicArray_take(t1, -2); /* yields [ 4, 5 ] */
    DynamicArray * t4 = DynamicArray_take(t1, 7);  /* yields [ 1, 2, 3, 4, 5, 0, 0 ] */
    DynamicArray * t5 = DynamicArray_take(t1, -8);

    printf("t2 = "); //1 2
    for (int i = 0; i < DynamicArray_size(t2); i++) {
        printf("%f ", DynamicArray_get(t2, i));
    }
    printf("\n");
    assert(DynamicArray_get(t2, 0) == 1.0);
    assert(DynamicArray_get(t2, 1) == 2.0);

    printf("t3 = "); // 4 5
    for (int i = 0; i < DynamicArray_size(t3); i++) {
        printf("%f ", DynamicArray_get(t3, i));
    }
    printf("\n");
    assert(DynamicArray_get(t3, 0) == 4.0);
    assert(DynamicArray_get(t3, 1) == 5.0);

    printf("t4 = "); // 1 2 3 4 5 0 0
    for (int i = 0; i < DynamicArray_size(t4); i++) {
        printf("%f ", DynamicArray_get(t4, i));
    }
    printf("\n");
    assert(DynamicArray_get(t4, 6) == 0.0);

    printf("t5 = "); // 1 2 3 4 5 0 0 0
    for (int i = 0; i < DynamicArray_size(t5); i++) {
        printf("%f ", DynamicArray_get(t5, i));
    }
    printf("\n");
    assert(DynamicArray_get(t5, 7) == 0.0);



    DynamicArray_destroy(da);
    DynamicArray_destroy(copy);
    DynamicArray_destroy(a);
    DynamicArray_destroy(d1);
    DynamicArray_destroy(d2);
    DynamicArray_destroy(concat);
    DynamicArray_destroy(t1);
    DynamicArray_destroy(t2);
    DynamicArray_destroy(t3);
    DynamicArray_destroy(t4);
    DynamicArray_destroy(t5);

    return 0;
}
