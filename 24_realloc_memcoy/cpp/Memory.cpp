#include "Memory.h"


void Memset(void *src, uint_64 val, uint_64 num) {
    if (num <= 8) {
        uint_8 * valPtr = (uint_8*)&val;
        for (uint_8* ptr = (uint_8*)src; ptr < (uint_8*)((uint_64)src + num); ptr++) {
            *ptr = *valPtr;
            valPtr++;
        }
        return;
    }
    
    uint_64 proceedingBytes = num % 8;
    uint_64 newnum = num - proceedingBytes;

    for (uint_64* ptr = (uint_64*)src; ptr < (uint_64*)((uint_64)src + newnum); ptr++) {
        *ptr = val;
    }

    uint_8 *valPtr = (uint_8*)&val;
    for (uint_8* ptr = (uint_8*)((uint_64)src + newnum); ptr < (uint_8*)((uint_64)src + num); ptr++) {
        *ptr = *valPtr;
        valPtr++;
    }
}

void Memcpy(void* dst, void* src, uint_64 num) {
    if (num < 8) {
        uint_8 *valPtr = (uint_8*)src;
        for (uint_8* ptr =  (uint_8*)dst; ptr < (uint_8*)((uint_64)dst + num); ptr++) {
            *ptr = *valPtr;
            valPtr++;
        }
        return;
    }

    uint_64 proceedingBytes = num % 8;
    uint_64 newnum = num - proceedingBytes;
    uint_64* srcPtr = (uint_64*)src;

    for (uint_64* dstPtr = (uint_64*)dst; dstPtr < (uint_64*)((uint_64)dst + newnum); dstPtr++) {
        *dstPtr = *srcPtr;
        srcPtr++;
    }

    uint_8* srcPtr8 = (uint_8*)((uint_64)src + newnum);
    for (uint_8* dstPtr8 = (uint_8*)((uint_64)dst + newnum); dstPtr8 < (uint_8*)((uint_64)dst+num); dstPtr8++) {
        *dstPtr8 = *srcPtr8;
        srcPtr8++;
    }
}

