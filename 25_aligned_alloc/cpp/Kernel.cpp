#include "TextPrint.h"
#include "IDT.h"
#include "Keyboard.h"
#include "MemoryMap.h"
#include "Heap.h"

extern "C" void _start() {
    SetCursorPosition(PositionFromCoords(0, 0));
    InitializeIDT();
    MainKeyboardHandler = KeyboardHandler;

    MemoryMapEntry** usableMemoryMaps = GetUsableMemoryRegions();
    InitializeHeap(0x100000, 0x100000);
    
    void* addr = (uint_64*)AlignedAlloc(0x4000, 0x08);
    PrintString(HexToString((uint_64)addr));
    Free(addr);

    addr = (uint_64*)Malloc(0x4000);
    PrintString(HexToString((uint_64)addr));

    return;
}
