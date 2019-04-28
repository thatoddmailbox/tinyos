#!/bin/sh
nasm -felf -o kernel/src/arch/x86/preboot.o kernel/src/arch/x86/preboot.s
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/arch/x86/boot.o kernel/src/arch/x86/boot.c
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/drivers/display/vga.o kernel/src/drivers/display/vga.c
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/init.o kernel/src/init.c
ld.lld -T linker.ld -o tinyos.bin -O2 -nostdlib kernel/src/arch/x86/preboot.o kernel/src/arch/x86/boot.o kernel/src/drivers/display/vga.o kernel/src/init.o