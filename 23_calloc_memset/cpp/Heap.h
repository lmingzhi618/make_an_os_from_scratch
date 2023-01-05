#pragma once
#include "TypeDefs.h"

struct MemorySegmentHeader {
    uint_64 MemoryLength;
    MemorySegmentHeader* NextSegment;
    MemorySegmentHeader* PrevSegment;
    MemorySegmentHeader* NextFreeSegment;
    MemorySegmentHeader* PrevFreeSegment;
    bool Free;
};

void InitializeHeap(uint_64 heapAddr, uint_64 heapLength);
void* Malloc(uint_64 size);
void* Calloc(uint_64 size);
void* Calloc(uint_64 num, uint_64 size);
void Free(void* addr);
