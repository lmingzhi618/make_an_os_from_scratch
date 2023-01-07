#include "Heap.h"
#include "Memory.h"

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

void* Calloc(uint_64 size) {
    void* mallocVal = Malloc(size);
    Memset(mallocVal, 0, size);
    return mallocVal;
} 

void* Calloc(uint_64 num, uint_64 size) {
    return Calloc(num * size);
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

void CombineFreedSegments(MemorySegmentHeader* a, MemorySegmentHeader* b) {
    if (a == 0 || b == 0 || a == b) {
        return;
    }
    if (a->Free == false || b->Free == false) {
        return;
    }
    if (a < b) {
        a->MemoryLength += b->MemoryLength + sizeof(MemorySegmentHeader);
        a->NextSegment = b->NextSegment;
        a->NextFreeSegment = b->NextFreeSegment;
        if (b->NextSegment) {
            b->NextSegment->PrevSegment = a;
            b->NextSegment->PrevFreeSegment = a;
        }
        if (b->NextFreeSegment)  {
            b->NextFreeSegment->PrevFreeSegment = a;
        }
    } else {
        b->MemoryLength += a->MemoryLength + sizeof(MemorySegmentHeader);
        b->NextSegment = a->NextSegment;
        b->NextFreeSegment = a->NextFreeSegment;
        if (a->NextSegment) {
            a->NextSegment->PrevSegment = b;
            a->NextSegment->PrevFreeSegment = b;
        }
        if (a->NextFreeSegment)  {
            a->NextFreeSegment->PrevFreeSegment = b;
        }
    }
}

void Free(void* addr) {
    MemorySegmentHeader* curSeg = ((MemorySegmentHeader*)addr) - 1;
    curSeg->Free = true;

    if (curSeg < FirstFreeMemorySegment) {
        FirstFreeMemorySegment  = curSeg;
    }
    if (curSeg->NextFreeSegment) {
        if (curSeg->NextFreeSegment->PrevFreeSegment < curSeg) {
            curSeg->NextFreeSegment->PrevFreeSegment = curSeg;
        }
    }
    if (curSeg->PrevFreeSegment) {
        if (curSeg->PrevFreeSegment->NextFreeSegment > curSeg) {
            curSeg->PrevFreeSegment->NextFreeSegment = curSeg;
        }
    }
    if (curSeg->NextSegment) {
        curSeg->NextSegment->PrevSegment = curSeg;
        if (curSeg->NextSegment->Free) {
            CombineFreedSegments(curSeg, curSeg->NextSegment);
        }
    }
    if (curSeg->PrevSegment) {
        curSeg->PrevSegment->NextSegment = curSeg;
        if (curSeg->PrevSegment->Free) {
            CombineFreedSegments(curSeg, curSeg->PrevSegment);
        }
    }
}

void* Realloc(void* addr, uint_64 newSize) {
    MemorySegmentHeader* oldSegHeader = (MemorySegmentHeader*)addr - 1;
    uint_64 smallerSize = newSize;
    if (oldSegHeader->MemoryLength < newSize) {
        smallerSize = oldSegHeader->MemoryLength;
    }
    void* newMem = Malloc(newSize);
    Memcpy(newMem, addr, smallerSize);
    Free(addr);
    return newMem;
}
