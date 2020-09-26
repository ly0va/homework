// loops.cpp

#include <cstdio>
#include <cstring>
#include <algorithm>
#include "fib.hpp"
#include "loops.hpp"

void printRow(int m, int l, int *s) {
    printf("<tr><td>%d</td><td>%d</td>", m, l);
    /* int maximum = *std::max_element(s, s+m); */
    for (int i = 0; i < m; i++) {
        printf("<td style='background:#%2$02x%2$02x%2$02x'>%1$d</td>", 
                s[i], s[i]);//255*s[i]/maximum);
    }
    printf("</tr>");
}

int cycle(int m) {
    Fib rnd(m);
    int a = rnd.next(), b = rnd.next(), c = rnd.next();
    int counter = 0;
    do {
        a = b;
        b = c;
        c = rnd.next();
        counter++;
    } while (a != 0 || b != 0 || c != 1);
    return counter;
}

int *spectre(int m) {
    Fib rnd(m);
    int l = cycle(m);
    int *s = new int[m]{};
    for (int i = 0; i < l; i++) {
        s[rnd.next()]++;
    }
    return s;
}

void printTable(unsigned from, unsigned upto) {
    printf("<link href=style.css rel=stylesheet>"
           "<table><tr><th rowspan=2>M</th><th rowspan=2>L</th>"
           "<th colspan=%d>Spectre</th></tr><tr>", upto);
    for (int i = 0; i < upto; i++) {
        printf("<th>%d</th>", i);
    }
    printf("</tr>");
    for (int m = from; m <= upto; m++) {
        int *s = spectre(m);
        printRow(m, cycle(m), s);
        delete[] s;
    }
    printf("</table>\n");
}
