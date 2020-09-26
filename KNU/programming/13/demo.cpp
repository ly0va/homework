#include "generator.hpp"
#include "spectre.hpp"
#include <fstream>
#include <iostream>

void demo_stdout() {
    Generator fib2(2, 3);
    Spectre s(fib2);
    s.get(15, 3);
    std::cout << s;
}

void demo_html() {
    Generator fib2(2, 3);
    Spectre s(fib2);
    s.get(15, 3);
    s.to_file("index.html");
}

void demo_fail() {
    Generator fib2(2, 3);
    Spectre s(fib2);
    s.get(100, 100);
}


