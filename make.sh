#!/bin/sh
nasm -felf -o kernel/src/arch/x86/interrupts.o kernel/src/arch/x86/interrupts.s
nasm -felf -o kernel/src/arch/x86/preboot.o kernel/src/arch/x86/preboot.s
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/arch/x86/boot.o kernel/src/arch/x86/boot.c
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/arch/x86/descriptors.o kernel/src/arch/x86/descriptors.c
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/arch/x86/isr.o kernel/src/arch/x86/isr.c
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/arch/x86/pic.o kernel/src/arch/x86/pic.c
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/drivers/display/vga.o kernel/src/drivers/display/vga.c
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/memory/manager.o kernel/src/memory/manager.c
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/term/term.o kernel/src/term/term.c
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/term/vgaterm.o kernel/src/term/vgaterm.c
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/init.o kernel/src/init.c
clang -c --target=i686-pc-none-elf -march=i686 -ffreestanding -Wall -Wextra -Ikernel/include -Ilibc/include -o kernel/src/log.o kernel/src/log.c
ld.lld -T linker.ld -o tinyos.bin -O2 -nostdlib kernel/src/arch/x86/interrupts.o kernel/src/arch/x86/preboot.o kernel/src/arch/x86/boot.o kernel/src/arch/x86/descriptors.o kernel/src/arch/x86/isr.o kernel/src/arch/x86/pic.o kernel/src/drivers/display/vga.o kernel/src/memory/manager.o kernel/src/term/term.o kernel/src/term/vgaterm.o kernel/src/init.o kernel/src/log.o