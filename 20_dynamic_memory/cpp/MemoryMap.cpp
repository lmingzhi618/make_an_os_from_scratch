#include "MemoryMap.h"
#include "TextPrint.h"

uint_8 UsableMemoryRegionCount;

MemoryMapEntry* UsableMemoryRegions[10];

void PrintMemoryMap(MemoryMapEntry* memoryMap, uint_16 position) {
    SetCursorPosition(position);

    PrintString("Memory Base: ");
    PrintString(IntegerToString(memoryMap->BaseAddress));
    SetCursorPosition(position + 80);

    PrintString("Region Length: ");
    PrintString(IntegerToString(memoryMap->RegionLength));
    SetCursorPosition(position + 160);

    PrintString("Memory Type: ");
    PrintString(IntegerToString(memoryMap->RegionType));
    SetCursorPosition(position + 240);

    PrintString("Memory Attributes: ");
    PrintString(HexToString(memoryMap->ExtendedAttributes));
    SetCursorPosition(position + 400);
}

bool MemoryRegionsGot = false;

MemoryMapEntry** GetUsableMemoryRegions() {
    if (MemoryRegionsGot) {
        return UsableMemoryRegions;
    }
    uint_8 UsableRegionIdx;
    for (uint_8 i = 0; i < MemoryRegionCount; ++i) {
        MemoryMapEntry* memMap = (MemoryMapEntry*)0x5000;
        memMap += i;
        if (memMap->RegionType == 1) {
            UsableMemoryRegions[UsableRegionIdx] = memMap;
            UsableRegionIdx++;
        }
    }
    UsableMemoryRegionCount = UsableRegionIdx;
    MemoryRegionsGot = true;
    return UsableMemoryRegions;
}
