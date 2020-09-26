#include <cstdio>

struct MyInt {} a;

int operator-(MyInt a, MyInt b) {
    return 1;
}

int main(int argc, char **argv) {
    int b;
    b = a-a;
    printf("%d\n", b);
    return 0;
}

