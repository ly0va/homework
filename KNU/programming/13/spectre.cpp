#include "spectre.hpp"
#include "generator.hpp"
#include <unordered_set>

using namespace std;

uint binpow(uint a, uint n) {
    uint res = 1;
    while (n) {
        if (n & 1) res = res * a;
        a = a * a;
        n >>= 1;
    }
    return res;
}

Spectre::Spectre(Generator gen): 
    gen(gen), spectre(nullptr), axes(0), len(0) {}

uint Spectre::get(uint length, uint axes) {
    uint Q = gen.getQ();
    if (spectre != nullptr) {
        delete[] spectre;
    }
    len = binpow(Q, axes);
    spectre = new uint[len];
    this->axes = axes;
    std::unordered_set<uint> non_zero;
    /* length *= axes / gcd(length, axes); */
    while (length--) {
        uint index = 0;
        for (uint i = 0; i < axes; i++) {
            index = index*Q + gen.next();
        }
        spectre[index]++;
        non_zero.insert(index);
    }
    return non_zero.size();
}

Spectre::operator string() const {
    uint Q = gen.getQ();
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

void Spectre::to_file(const char *filename) const {
    ofstream(filename) << *this;
}

Spectre::~Spectre() {
    if (spectre != nullptr) {
        delete[] spectre;
    }
}

ostream& operator<<(ostream& os, const Spectre& s) {
    return os << string(s);
}

uint gcd(uint a, uint b) {
    if (a < b) swap(a, b);
    return b == 0 ? a : gcd(b, a % b);
}

bool Spectre::operator==(const Spectre& b) const {
    uint a_gcd = 0, b_gcd = 0;
    for (int i = 0; i < len; i++) {
        a_gcd = gcd(a_gcd, spectre[i]);
    }
    for (int i = 0; i < b.len; i++) {
        b_gcd = gcd(b_gcd, b.spectre[i]);
    }
    for (int i = 0; i < len; i++) {
        spectre[i] /= a_gcd;
    }
    for (int i = 0; i < b.len; i++) {
        b.spectre[i] /= b_gcd;
    }
    uint minlen = min(len, b.len);
    uint maxlen = max(len, b.len);
    uint *other = len < b.len ? b.spectre : spectre;
    for (int i = 0; i < minlen; i++) {
        if (spectre[i] != b.spectre[i]) {
            return false;
        }
    }
    for (int i = minlen; i < maxlen; i++) {
        if (other[i] != 0) {
            return false;
        }
    }
    return true;
}

