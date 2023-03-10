#include "IDT.h"
#include "KBScanCodeSet1.h"
#include "IO.h"

extern "C" void LoadIDT();
extern IDT64 _idt[256];
extern uint_64 isr1;

void (*MainKeyboardHandler)(uint_8 scanCode, uint_8 chr);

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
    uint_8 chr = 0;
    if (scanCode < 0x3A) {
        chr = KBSet1::ScanCodeLookupTable[scanCode];
    }
    if (MainKeyboardHandler) {
        MainKeyboardHandler(scanCode, chr);
    }
    outb(0x20, 0x20);
    outb(0xa0, 0x20);
}
