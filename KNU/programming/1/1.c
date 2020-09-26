#include <stdio.h>

int main(int argc, char **argv) {
    unsigned f0 = 1, f1 = 1;
    unsigned long long counter = 0;
    do {
        f1 = f0 + f1;
        f0 = f1 - f0;
        counter++;
    } while (f0 != 1 || f1 != 1);
    printf("%llu\n", counter);
    return 0;
}

