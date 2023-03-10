#pragma once
#include "TypeDefs.cpp"
#include "KBScanCodeSet1.cpp"

/*Interrupt descriptor Table*/
struct IDT64 {
    uint_16 offset_low;
    uint_16 selector;
    uint_8  ist;
    uint_8  types_attr;
    uint_16 offset_mid;
    uint_32 offset_high;
    uint_32 zero;
};

extern IDT64 _idt[256];
extern uint_64 isr1;
extern "C" void LoadIDT();

void InitializeIDT() {
    _idt[1].zero = 0;
    _idt[1].offset_low = (uint_16)(((uint_64)&isr1 & 0xffff));
    _idt[1].offset_mid = (uint_16)(((uint_64)&isr1 & 0xffff0000) >> 16);
    _idt[1].offset_high = (uint_32)(((uint_64)&isr1 & 0xffffffff00000000) >> 32);
    _idt[1].ist = 0;
    _idt[1].selector = 0x08;    // code segment selector declared in GDT
    _idt[1].types_attr = 0x8e;  // interrupt gate
    
    RemapPic();

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    LoadIDT();
}

extern "C" void isr1_handler() {
    uint_8 scanCode = inb(0x60);
    if (scanCode < 0x3A) {
        PrintChar(KBSet1::ScanCodeLookupTable[scanCode]);
    }
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}
