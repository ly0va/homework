// fib.hpp

#ifndef _FIB_HPP_
#define _FIB_HPP_

struct Fib {
    unsigned f[3];
    unsigned m;
    Fib(unsigned newm=2);
    unsigned next();
    void reset(unsigned newm=2);
};

#endif
