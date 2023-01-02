nasm bootloader.asm -f bin -o bootloader.bin
nasm ExtendedProgram.asm -f bin -o ExtendedProgram.bin
cat bootloader.bin ExtendedProgram.bin > bootloader.img

qemu-system-x86_64 bootloader.img

