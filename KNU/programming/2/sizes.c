#include <stdio.h>
#include <math.h>

int sizeOfInt() {
    long tmp = 1;
    int bitCounter = 1;
    while (tmp > 0) {
        tmp <<= 1;
        bitCounter++;
    }
    printf("Size of int: %d\n", bitCounter);
    return bitCounter;
}

int sizeOfFloat() {
    // mantissa
    float tmp = 1.0;
    float prevTmp;
    int mantissa = 0;
    do {
        prevTmp = tmp;
        tmp = tmp/2 + 1;
        mantissa++;
    } while (tmp != prevTmp);
    mantissa -= 2;

    // counter <- 2**(exponent-1) + mantissa
    // exponent-1 because exponent also has a sign bit
    tmp = 1;
    int counter = 1;
    do {
        counter++;
        tmp /= 2;
    } while (tmp > 0);

    // sign bit
    tmp = 1;
    int sign = (int)(tmp != -tmp);
    
    int exponent = round(log2(counter-mantissa))+1;
    int total = mantissa + exponent + sign;
    printf("Size of float: %d\n", total);
    printf("  mantissa: %d\n  exponent: %d\n  sign: %d\n", mantissa, exponent, sign);
    return total; 
}

int sizeOfDouble() {
    // mantissa
    double tmp = 1.0;
    double prevTmp;
    int mantissa = 0;
    do {
        prevTmp = tmp;
        tmp = tmp/2 + 1;
        mantissa++;
    } while (tmp != prevTmp);
    mantissa -= 2;

    // counter <- 2**(exponent-1) + mantissa
    // exponent-1 because exponent also has a sign bit
    tmp = 1;
    int counter = 1;
    do {
        counter++;
        tmp /= 2;
    } while (tmp > 0);

    // sign bit
    tmp = 1;
    int sign = (int)(tmp != -tmp);
    
    int exponent = round(log2(counter-mantissa))+1;
    int total = mantissa + exponent + sign;
    printf("Size of double: %d\n", total);
    printf("  mantissa: %d\n  exponent: %d\n  sign: %d\n", mantissa, exponent, sign);
    return total; 
}

int main(int argc, char **argv) {
    sizeOfInt();
    sizeOfFloat();
    sizeOfDouble();
    return 0;
}

