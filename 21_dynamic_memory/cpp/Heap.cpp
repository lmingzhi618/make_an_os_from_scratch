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
        if (curSeg->MemoryLength >= size)  {
            if (curSeg->MemoryLength > (size + sizeof(MemorySegmentHeader))) {
                MemorySegmentHeader* newSegHeader = 
                    (MemorySegmentHeader*)((uint_64)curSeg + sizeof(MemorySegmentHeader) + size);
                newSegHeader->Free = true;
                newSegHeader->MemoryLength = 
                    ((uint_64)curSeg->MemoryLength) - (sizeof(MemorySegmentHeader) + size);
                newSegHeader->NextFreeSegment = curSeg->NextFreeSegment;
                newSegHeader->NextSegment = curSeg->NextSegment;
                newSegHeader->PrevSegment = curSeg;
                newSegHeader->PrevFreeSegment = curSeg->PrevFreeSegment;
                curSeg->NextFreeSegment = newSegHeader;
                curSeg->NextSegment = newSegHeader;
                curSeg->MemoryLength = size;
            }
            
            if (curSeg == FirstFreeMemorySegment) {
                FirstFreeMemorySegment = curSeg->NextFreeSegment;
            }
            curSeg->Free = false;
            if (curSeg->PrevFreeSegment) {
                curSeg->PrevFreeSegment->NextFreeSegment = curSeg->NextFreeSegment; 
            }
            if (curSeg->NextFreeSegment) {
                curSeg->NextFreeSegment->PrevFreeSegment = curSeg->PrevFreeSegment;
            }
            if (curSeg->PrevSegment) {
                curSeg->PrevSegment->NextFreeSegment = curSeg->NextFreeSegment;
            }
            if (curSeg->NextSegment) {
                curSeg->NextSegment->PrevFreeSegment = curSeg->PrevFreeSegment;
            }
            return curSeg + 1;
        }
        if (curSeg->NextFreeSegment == 0) {
            return 0; // No memory remining
        }
        curSeg = curSeg->NextFreeSegment;
    }

    return 0;   // we should never get here;
}
