#!/bin/sh
rm -r iso

mkdir -p iso/boot/grub

cp tinyos.bin iso/boot
cat > iso/boot/grub/grub.cfg << EOF
menuentry "tinyos" {
	multiboot /boot/tinyos.bin
}
EOF

i386-elf-grub-mkrescue -o tinyos.iso iso