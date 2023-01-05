cd bin
rm -rf *.bin *.o *.img *.flp
cd ..

cd asm
nasm bootloader.asm -f bin -o ../bin/bootloader.bin
nasm ExtendedProgram.asm -f elf64 -o ../bin/ExtendedProgram.o
nasm Binaries.asm -f elf64 -o ../bin/Binaries.o
cd ..

cd cpp
gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "Kernel.cpp" -o "../bin/Kernel.o"
gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "IDT.cpp" -o "../bin/IDT.o"
gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "IO.cpp" -o "../bin/IO.o"
gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "Keyboard.cpp" -o "../bin/Keyboard.o"
gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "MemoryMap.cpp" -o "../bin/MemoryMap.o"
gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "TextPrint.cpp" -o "../bin/TextPrint.o"
cd ..

cd bin
ld -T "link.ld" 
cat bootloader.bin kernel.bin > bootloader.img

qemu-system-x86_64 -fda bootloader.img -d int
