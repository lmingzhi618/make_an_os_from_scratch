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

    uint_64* addr = (uint_64*)Malloc(0x08);
    *addr = 12345678;
    //PrintString(IntegerToString(*addr));
    //PrintString("\n\r");

    uint_64* addr2 = (uint_64*)Realloc(addr, 0x08);
    //PrintString(IntegerToString(*addr2));
    //PrintString("\n\r");

    uint_64* addr3 = (uint_64*)Calloc(0x08);
    PrintString(IntegerToString(*addr));
    PrintString(IntegerToString(*addr2));
    PrintString(IntegerToString(*addr3));
    PrintString("\n\r");

    return;
}
