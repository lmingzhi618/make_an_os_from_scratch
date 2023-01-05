#include "TextPrint.cpp"
#include "IDT.cpp"
#include "Keyboard.cpp"
#include "MemoryMap.cpp"

extern "C" void _start() {
    SetCursorPosition(PositionFromCoords(0, 0));
    InitializeIDT();
    MainKeyboardHandler = KeyboardHandler;
    
    MemoryMapEntry** usableMemoryMaps = GetUsableMemoryRegions();

    for (uint_8 i = 0; i < UsableMemoryRegionCount; i++) {
        MemoryMapEntry* memMap = usableMemoryMaps[i];
        PrintMemoryMap(memMap, CursorPosition);
    }
    return;
}
