#include "TextPrint.cpp"
#include "IDT.cpp"
#include "Keyboard.cpp"

extern "C" void _start() {
    SetCursorPosition(PositionFromCoords(0, 0));
    InitializeIDT();

    MainKeyboardHandler = KeyboardHandler;

    PrintString(IntegerToString(-54321));

    double testFloat = -672.938f;
    SetCursorPosition(PositionFromCoords(0, 1));
    PrintString(FloatToString(testFloat, 10));
    return;
}
