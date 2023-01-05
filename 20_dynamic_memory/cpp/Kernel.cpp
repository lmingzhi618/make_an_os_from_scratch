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
    void* TestMemoryAddr = Malloc(60);
    PrintString(HexToString((uint_64)TestMemoryAddr));
    return;
}
