#include <bits/stdc++.h>

using std::cout;

typedef uint16_t CRC;

// CRC-16/XMODEM
const CRC POLYNOMIAL = 0x1021;

const unsigned WIDTH = sizeof(CRC) * 8;
const unsigned N = 125;

CRC crcTable[256];

void initCrcTable() {
    for (unsigned i = 0; i < 256; ++i) {
        CRC c = i << (WIDTH - 8);
        for (unsigned j = 0; j < 8; ++j) {
            if (c & (1 << (WIDTH - 1))) {
                c = (c << 1) ^ POLYNOMIAL;
            } else {
                c <<= 1;
            }
        }
        crcTable[i] = c;
    }
}

CRC fastCRC(uint8_t data[]) {
    CRC crc = 0;
    for (unsigned i = 0; i < N; ++i) {
        crc = (crc << 8) ^ crcTable[(crc >> (WIDTH - 8)) ^ data[i]];
    }
    return crc;
}

CRC simpleCRC(uint8_t data[]) {
    CRC crc = 0;
    for (unsigned i = 0; i < N; ++i) {
        crc ^= data[i] << (WIDTH - 8);
        for (unsigned j = 0; j < 8; ++j) {
            if (crc & (1 << (WIDTH - 1))) {
                crc = (crc << 1) ^ POLYNOMIAL;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

// Check: 0x31C3
// const unsigned N = 9;
// uint8_t data[N] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

uint8_t data[N];

int main(int argc, char **argv) {
    for (int i = 0; i < N; ++i) {
        data[i] = rand();
    }

    initCrcTable();
    

    std::clock_t now = clock();

    for (int i = 0; i < 1000000; ++i) {
        simpleCRC(data);
    }

    cout << "simpleCRC: " << (clock() - now) / (double)CLOCKS_PER_SEC << '\n';
    cout << "Result: " << std::hex << "0x" << simpleCRC(data) << std::dec << '\n';

    now = clock();
    for (int i = 0; i < 1000000; ++i) {
        fastCRC(data);
    }

    cout << "fastCRC: " << (clock() - now) / (double)CLOCKS_PER_SEC << '\n';
    cout << "Result: " << std::hex << "0x" << fastCRC(data) << std::dec << '\n';

    return 0;
}

