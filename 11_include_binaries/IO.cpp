#pragma once

void outb(unsigned short port, unsigned char val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

unsigned char inb(unsigned short port) {
    unsigned char retVal;
    asm volatile("inb %1, %0" : "=a"(retVal) : "Nd"(port));
    return retVal;
}
