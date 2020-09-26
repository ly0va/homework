#include "libspectre.hpp"
#include <unordered_set>

typedef unsigned uint;

uint gcd(uint a, uint b) {
    return b == 0 ? a : gcd(b, a % b);
}

uint univ_spectre(
    uint (&func)(void),  // the function to get the spectre of
    uint length,         // number of samples
    uint max_value,      // maximum value that func() can return
    uint axes,           // values per sample
    uint *spectre        // output array
) {
    uint Q = max_value + 1;
    std::unordered_set<uint> non_zero;
    /* length *= axes / gcd(length, axes); */
    while (length--) {
        uint index = 0;
        for (uint i = 0; i < axes; i++) {
            index = index*Q + (func() % Q);
        }
        spectre[index]++;
        non_zero.insert(index);
    }
    return non_zero.size();
}




