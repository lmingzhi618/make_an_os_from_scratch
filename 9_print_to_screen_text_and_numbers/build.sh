rm -rf *.bin *.o *.img

nasm bootloader.asm -f bin -o bootloader.bin

nasm ExtendedProgram.asm -f elf64 -o ExtendedProgram.o

gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "Kernel.cpp" -o "Kernel.o"

ld -T "link.ld" 

cat bootloader.bin kernel.bin > bootloader.img

qemu-system-x86_64 -fda bootloader.img -d int
