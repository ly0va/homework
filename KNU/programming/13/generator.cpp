#include "generator.hpp"
#include <cstring>

Generator::Generator(uint N, uint Q): N(N), Q(Q) {
    fibs = new uint[N]{};
    fibs[N-1] = 1;
}

Generator::Generator(const Generator& gen) {
    Q = gen.Q;
    N = gen.N;
    fibs = new uint[N]{};
    memcpy(fibs, gen.fibs, N*sizeof(uint));
}

uint Generator::next() {
    uint tmp = fibs[0];
    uint sum = fibs[0];
    for (uint i = 1; i < N; i++) {
        sum = (sum + fibs[i]) % Q;
        fibs[i-1] = fibs[i];
    }
    return fibs[N-1] = sum;
}

Generator::~Generator() {
    delete[] fibs;
}

uint Generator::getQ() const {
    return Q;
}
