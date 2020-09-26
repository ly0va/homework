#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "demo.hpp"

using namespace std;

void help(char *name) {
    printf("USAGE: %s <command>\n"
           "<command>:\n"
           "    test1 - output spectre to stdout\n"
           "    test2 - output spectre to index.html\n"
           "    test3 - test on incorrect data\n"
           "    all   - run test1 test2 test3\n"
           "    help  - display this message and exit\n",
           name);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        help(argv[0]);
        exit(0);
    }
    char *command = argv[1];
    if (!strcmp(command, "test1")) {
        demo_stdout();
    } else if (!strcmp(command, "test2")) {
        demo_html();
    } else if (!strcmp(command, "test3")) {
        demo_fail();
    } else if (!strcmp(command, "all")) {
        demo_stdout();
        demo_html();
        demo_fail();
    } else {
        help(argv[0]);
    }
    return 0;
}

