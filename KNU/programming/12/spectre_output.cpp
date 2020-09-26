#include "liboutput.hpp"
#include "libspectre.hpp"

// function that yields fibonacci numbers
uint fib(void) {
    static uint a = 0;
    static uint b = 1;
    return a = (b += a) - a;
}


int main() {
    // array that will store the spectre
    uint spectre[27] = {};

    // test the fib function (shouldn't fail)
    uint non_zero = univ_spectre(fib, 15, 2, 3, spectre);
    
    // output the result
    spectre2stdout(spectre, 3, 3);

    return 0;
}
