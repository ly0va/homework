#include <stdio.h>

int f(int &a) {
    return ++a;
}

void log_result(int l2r, int r2l, int b) {
    if (b == l2r) {
        puts("Conclusion: expressions calculated left to right\n");
    } else if (b == r2l) {
        puts("Conclusion: expressions calculated right to left\n");
    } else {
        puts("Conclusion: this compiler has a bug\n");
    }
}


int main(int argc, char **argv) {
    int b, a = 1;

    b = (a--) - (a--);
    printf("Performing: (a--) - (a--)\n"
           "Result: %d\n", b);

    log_result(1, -1, b);

    a = 1;
    b = f(a) - a;
    printf("Performing: f(a) - a\n" 
           "(a is passed into f by reference, f returns ++a)\n"
           "Result: %d\n", b);

    log_result(0, 1, b);

    return 0;
}

