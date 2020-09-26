#ifndef _LIBSPECTRE_HPP_
#define _LIBSPECTRE_HPP_

typedef unsigned uint;

uint univ_spectre(
    uint (&func)(void), 
    uint length, 
    uint max_value, 
    uint axes, 
    uint *spectre
);


#endif
