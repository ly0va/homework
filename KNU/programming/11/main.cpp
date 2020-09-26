#include <cstdio>
#include <random>
#include <cmath>
#include "fib.hpp"
// L = 2*10^6
// my figure: 
// outer circle: x^2 + y^2 = (10^6)^2 
// inner circle: x^2 + y^2 = (10^5)^2
// bounding figure: squaure with sidelength = L, center in (0, 0)

#define OUTER_R 1e12
#define INNER_R 1e10
#define L       2000000LL
#define HALF_L  (L/2)

bool is_inside(long x, long y) {
    long radius2 = x*x + y*y;
    return INNER_R <= radius2 && radius2 <= OUTER_R;
}

template <int N>
int rand() {
    static Fib<N> fib(L);
    return fib.next();
}

double monte_carlo(int (*rand_func)(), long hits) {
    long counter = 0;
    for (long h = 0; h < hits; h++) {
        long x = (*rand_func)() % L - HALF_L;
        long y = (*rand_func)() % L - HALF_L;
        counter += is_inside(x, y);
    }
    return (counter + .0)/hits;
}

double calc_area(int (*rand_func)(), long hits=3*L) {
    double area = M_PI*(OUTER_R - INNER_R);
    double mc_area = monte_carlo(rand_func, hits)*L*L;
    double deviation = fabs(area - mc_area)/area;
    printf("\nReal area: %lf\nEstimated area: %lf\nDeviation: %lf\n", 
            area, mc_area, deviation);
    return deviation; 
}

void check_deviation() {
    for (long h = 2*L; h <= 5*L; h += (3*L/100)) {
        fprintf(stderr, "%ld\n", (long)(L*calc_area(&rand, h)));
    }
}

int main(int argc, char **argv) {
    calc_area(&rand);
    calc_area(&rand<2>);
    calc_area(&rand<3>);
    /* check_deviation(); */
    return 0;
}

