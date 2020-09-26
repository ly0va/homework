#include <stdio.h>
#ifndef N
    #define N 5
#endif
#define s (1<<N)

const int xinc[] = {2, 0, -2, 0};
const int yinc[] = {0, -1, 0, 1};
int prevD = 1, x = 0, y = 0;

char buffer[s][2*s] = {};
char *strokes[4][4] = {
    {"__", "| ", "  ", "  "}, 
    {" _", "| ", "  ", "  "}, 
    {"  ", "|_", "__", " _"}, 
    {"|_", "| ", "| ", "| "}
};

int l(int d) {
    d &= 3;
    buffer[y][x] = strokes[prevD][d][0];
    buffer[y][x+1] = strokes[prevD][d][1];
    prevD = d;
    x += xinc[d];
    y += yinc[d];
    return 1;
}

int h(  int d // d is the direction: 0, 1, 2, or 3
      , int r // r is the rotation: either 1 (clockwise) or -1 (counter-clockwise)
      , int n // n is the order
) {
    if (n == 0) return 0;
    return 
        h(d+r, -r, n-1) +
        l(d+r) + 
        h(d, r, n-1) + 
        l(d) +
        h(d, r, n-1) +
        l(d-r) +
        h(d-r, -r, n-1);
}

int main() {
    if (N == 0) {
        puts(".");
        return 0;
    }
    x = 0;
    y = s-1;
    h(0, 1, N);
    l(3);
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < 2*s; j++)
            putchar(buffer[i][j]);
        putchar('\n');
    }
}
