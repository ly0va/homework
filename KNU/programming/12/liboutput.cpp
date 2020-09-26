#include <string>
#include <cstdio>

typedef unsigned uint;
using namespace std;

string spectre2string(uint *spectre, uint Q, uint axes) {
    string output = "<link href=style.css rel=stylesheet><table>";
    uint *powers = new uint[axes+1]{1};
    for (uint i = 1; i <= axes; i++) {
        powers[i] = Q*powers[i-1];
    }
    for (uint row = 0; row < powers[axes]; row++) {
        output += "<tr>";
        for (int power = powers[axes-1]; power > 0; power /= Q) {
            if (row % power == 0) {
                output += "<td rowspan=" + to_string(power) + ">";
                output += to_string(spectre[row]) + "</td>";
            }
        }
        output += "</tr>";
    }
    delete[] powers;
    return output + "</table>";
}

uint spectre2stdout(uint *spectre, uint Q, uint axes) {
    return puts(spectre2string(spectre, Q, axes).c_str());
}

uint spectre2file(char *filename, uint *spectre, uint Q, uint axes) {
    FILE *file = fopen(filename, "w");
    return file == NULL ? 0 :
        fputs(spectre2string(spectre, Q, axes).c_str(), file);
}
