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

struct AlignedMemorySegmentHeader {
    uint_64 MemorySegmentHeaderAddr : 63;
    bool IsAligned : 1;
};

void InitializeHeap(uint_64 heapAddr, uint_64 heapLength);
void* Malloc(uint_64 size);
void* Calloc(uint_64 size);
void* Calloc(uint_64 num, uint_64 size);
void* Realloc(void* addr, uint_64 newSize);
void* AlignedAlloc(uint_64 alignment, uint_64 size);
void Free(void* addr);
