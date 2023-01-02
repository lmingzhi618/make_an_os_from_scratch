#include "TextPrint.cpp"

extern "C" void _start() {

    SetCursorPosition(PositionFromCoords(0, 0));
    PrintString("Hello World!\n\rThis is a new line\n\r");
	PrintString(HexToString(0x1234abcd));
    return;
}
