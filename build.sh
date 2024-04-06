nasm -f elf32 kernel.asm -o obj/kasm.o
clang -m32 -c kernel.c -o obj/kc.o -ffreestanding
clang -m32 -c drivers/vga.c -o obj/vga.o -ffreestanding
clang -m32 -c drivers/kernellib/string.c -o obj/string.o -ffreestanding
clang -m32 -c drivers/kernellib/math.c -o obj/math.o -ffreestanding
ld -m elf_i386 -T link.ld -o kernel obj/kasm.o obj/kc.o obj/vga.o obj/string.o obj/math.o -z noexecstack
qemu-system-i386 -kernel kernel
read r
