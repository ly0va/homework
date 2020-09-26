#ifndef _LIBOUTPUT_HPP_
#define _LIBOUTPUT_HPP_

#include <string>

typedef unsigned uint;

std::string spectre2string(uint *spectre, uint Q, uint axes);
uint spectre2stdout(uint *spectre, uint Q, uint axes);
uint spectre2file(char *filename, uint *spectre, uint Q, uint axes);



#endif
