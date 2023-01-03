#pragma once
#include "TypeDefs.cpp"
#include "IO.cpp"
#include "TextModeColor.cpp"

#define VGA_MEMORY (uint_8*)0xb8000
#define VGA_WIDTH 80

uint_16 CursorPosition; 
uint_8 test;
void ClearScreen(uint_64 ClearColor = BACKGROUND_BLACK | FOREGROUND_RED) {
    uint_64 value = 0;
    value += ClearColor << 8;
    value += ClearColor << 24;
    value += ClearColor << 40;
    value += ClearColor << 56;

    for (uint_64* i = (uint_64*)VGA_MEMORY; i < (uint_64*)(VGA_MEMORY + 4000); i++) {
        *i = value;
        test++;
    }
}

// Position is a index for 0 to the end of video memory
void SetCursorPosition(uint_16 position){
    outb(0x3D4, 0x0F);  
    outb(0x3D5, (uint_8)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint_8)((position >> 8) & 0xFF));
    CursorPosition = position;

	if(CursorPosition > 2000) CursorPosition = 2000;

	if(CursorPosition < 0) CursorPosition = 0;
}

uint_16 PositionFromCoords(uint_8 x, uint_8 y) {
    return y * VGA_WIDTH + x;
}

void PrintChar(char c, uint_8 color = BACKGROUND_BLACK | FOREGROUND_WHITE) {
    *(VGA_MEMORY + CursorPosition * 2) = c;
    *(VGA_MEMORY + CursorPosition * 2 + 1) = color;
    SetCursorPosition(CursorPosition + 1);
}

/* Função para Imprimir Caracteres*/
void PrintString(const char* str, uint_8 color = BACKGROUND_BLACK | FOREGROUND_WHITE) {
    uint_8* ptr = (uint_8*)str;
    uint_16 idx = CursorPosition;
    while (*ptr != 0) {
        switch (*ptr) {
            case 10:
                idx += VGA_WIDTH;
                idx -= idx % VGA_WIDTH;
                break;
            default:
                *(VGA_MEMORY + idx * 2) = *ptr;
                *(VGA_MEMORY + idx * 2 + 1) = color;
                idx++;
        }
        ptr++;
    }
    SetCursorPosition(idx);
}

/* Função para imprimir numeros*/

char hexToStringOutput[128]; //Buffer
template<typename T>
const char* HexToString(T value) {
    T* valPtr = &value;
    uint_8* ptr;
    uint_8 tmp;
    uint_8 size = (sizeof(T)) * 2 - 1;
    uint_8 i;
    
    for (i = 0; i < size; i++) {
   
        ptr = ((uint_8*)valPtr + i);
        tmp = ((*ptr & 0xF0) >> 4);
        hexToStringOutput[size - (i * 2 + 1)] = tmp + (tmp > 9 ? 55 : 48);
   
        tmp = ((*ptr & 0x0F));
        hexToStringOutput[size - (i * 2 + 0)] = tmp + (tmp > 9 ? 55 : 48);
    }
    
    hexToStringOutput[size + 1] = 0;
    
    return hexToStringOutput;
}

char integerToStringOutput[128];
template<typename T>
const char* IntegerToString(T value) {
    uint_8 isNegative = 0;
    if (value < 0) {
        isNegative = 1;
        value *= -1;
        integerToStringOutput[0] = '-';
    }

    uint_8 size = 0;
    uint_64 sizeTester = (uint_64)value;
    while (sizeTester / 10 > 0) {
        sizeTester /= 10;
        size++;
    }

    uint_8 idx = 0;
    uint_64 newVal = (uint_64)value;
    while (newVal / 10) {
        uint_8 remainder = newVal % 10;
        newVal /= 10;
        integerToStringOutput[isNegative + size - idx] = remainder + 48;
        idx++;
    }
    uint_8 remainder = newVal % 10;
    integerToStringOutput[isNegative + size - idx] = remainder + 48;
    integerToStringOutput[isNegative + size + 1] = 0;
    return integerToStringOutput;
}

