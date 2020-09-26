#include "libspectre.hpp"
#include <cstdio>

typedef unsigned uint;

// function that yields fibonacci numbers
uint fib(void) {
    static uint a = 0;
    static uint b = 1;
    return a = (b += a) - a;
}


// function that yields powers of 2
uint fail(void) {
    static uint a = 1;
    return a *= 2;
}

int main() {
    // array that will store the spectre
    uint spectre[10] = {};

    // test the fib function (shouldn't fail)
    uint non_zero = univ_spectre(fib, 6, 8, 1, spectre);
    printf("Non zero values: %d\nFibonacci spectre: ", non_zero);
    for (int i = 0; i < 10; i++) {
        printf("%d ", spectre[i]);
    }

    // maxF (100) is larger than array size (10); fails
    printf("\n\nThis will fail:\n");
    univ_spectre(fail, 30, 100, 1, spectre);
}


