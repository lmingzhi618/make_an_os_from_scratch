#include "TextPrint.cpp"
#include "IDT.cpp"
#include "Keyboard.cpp"

extern "C" void _start() {
    SetCursorPosition(PositionFromCoords(0, 0));
    InitializeIDT();

    MainKeyboardHandler = KeyboardHandler;

    PrintString(IntegerToString(-54321));
    return;
}
