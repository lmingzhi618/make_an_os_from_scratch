#include "Memory.h"


void Memset(void *src, uint_64 val, uint_64 num) {
    if (num <= 8) {
        uint_8 * valPtr = (uint_8*)&val;
        for (uint_8* ptr = (uint_8*)start; ptr < (uint_8*)((uint_64)start = num); ptr++) {
            *ptr = *valPtr;
            valPtr++;
        }
        return;
    }
    
    uint_64 proceedingBytes = num % 8;
    uint_64 newnum = num - proceedingBytes;

    for (uint_64* ptr = (uint_64*)start; ptr < (uint_64*)((uint_64)start + newnum); ptr++) {
        *ptr = val;
    }

    uint_8 *valPtr = (uint_8)&val;
    for (uint_8* ptr = (uint_8*)((uint_64)start + newnum); ptr < (uint_8*)((uint_64)start + num); ptr++) {
        *ptr = *valPtr;
        valPtr++;
    }
}
