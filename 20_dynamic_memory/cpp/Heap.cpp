#include "Heap.h"

MemorySegmentHeader* FirstFreeMemorySegment;

void InitializeHeap(uint_64 heapAddr, uint_64 heapLength) {
    FirstFreeMemorySegment = (MemorySegmentHeader*)heapAddr;
    FirstFreeMemorySegment->MemoryLength = heapLength - sizeof(MemorySegmentHeader);
    FirstFreeMemorySegment->NextSegment = 0;
    FirstFreeMemorySegment->PrevSegment = 0;
    FirstFreeMemorySegment->NextFreeSegment = 0;
    FirstFreeMemorySegment->PrevFreeSegment = 0;
    FirstFreeMemorySegment->Free = true;
}

void* Malloc(uint_64 size) {
    uint_64 remainder = size % 8;
    size -= remainder;
    if (remainder != 0) {
        size += 8;
    }
    MemorySegmentHeader* curSeg = FirstFreeMemorySegment;
    while (true) {
        if (curSeg->MemoryLength >= size) {
            return curSeg + 1;
        }
    }

    return nullptr;
}
