#include "libspectre.hpp"
#include "liboutput.hpp"

// function that yields fibonacci numbers
uint fib(void) {
    static uint a = 0;
    static uint b = 1;
    return a = (b += a) - a;
}

int64_t index(int axes, int Q, int *ijk) {
    int index = 0;
    for (int i = 0; i < axes; i++) {
        index = index*Q + (ijk[i] % Q);
    }
    return index;
}

void demo_stdout() {
    uint spectre[27] = {};
    univ_spectre(fib, 15, 2, 3, spectre);
    spectre2stdout(spectre, 3, 3);
}

void demo_html() {
    uint spectre[27] = {};
    univ_spectre(fib, 15, 2, 3, spectre);
    spectre2file((char *)"index.html", spectre, 3, 3);
}

void demo_index_fail() {
    int indexes[] = {1, 2, 3};
    int i = index(1000000, 5, indexes);
}


