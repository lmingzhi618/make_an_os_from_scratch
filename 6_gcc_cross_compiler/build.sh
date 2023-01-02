nasm bootloader.asm -f bin -o bootloader.bin

nasm ExtendedProgram.asm -f elf64 -o ExtendedProgram.o

gcc -ffreestanding -mno-red-zone -m64 -c "Kernel.cpp" -o "Kernel.o"

ld -o kernel.tmp -Ttext 0x7e00 ExtendedProgram.o Kernel.o 

objcopy -O binary kernel.tmp kernel.bin

cat bootloader.bin kernel.bin > bootloader.img
qemu-system-x86_64 -fda bootloader.img -d int
