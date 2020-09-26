#ifndef _SPECTRE_HPP_
#define _SPECTRE_HPP_

#include "generator.hpp"
#include <fstream>

using std::ostream;

class Spectre {
    Generator gen;
    uint *spectre;
    uint axes;
    uint len;
    friend ostream& operator<<(ostream& os, const Spectre& s);
  public:
    Spectre(Generator gen);
    uint get(uint length, uint axes);
    operator std::string() const;
    bool operator==(const Spectre& other) const;
    void to_file(const char *filename) const;
    ~Spectre();
};

#endif
