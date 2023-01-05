#include "TextPrint.cpp"
#include "IDT.cpp"
#include "Keyboard.cpp"
#include "MemoryMap.cpp"

extern "C" void _start() {
    SetCursorPosition(PositionFromCoords(0, 0));
    InitializeIDT();

    MainKeyboardHandler = KeyboardHandler;

    PrintString(IntegerToString(-54321));
    PrintString("\n");
    PrintString("AABB\n");
    return;

    double testFloat = -672.938f;
    SetCursorPosition(PositionFromCoords(0, 1));
    PrintString(FloatToString(testFloat, 10));
    
    SetCursorPosition(PositionFromCoords(0, 3));
    PrintString(IntegerToString(MemoryRegionCount));

    PrintString("\n");
    PrintString("12345\n");
    return;
}
