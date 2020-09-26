#ifndef _GENERATOR_HPP_
#define _GENERATOR_HPP_

typedef unsigned uint;

class Generator {
    uint *fibs;
    uint N;
    uint Q;
  public:
    Generator(uint N = 2, uint Q = 2);
    Generator(const Generator& gen);
    uint next();
    uint getQ() const;
    ~Generator();
};

#endif
