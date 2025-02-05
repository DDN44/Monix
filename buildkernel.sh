#!/bin/bash

KERNELFILES="./kernel/kernel.c ./kernel/stdker/io.c ./kernel/term/term.c ./kernel/mem/mem.c ./kernel/init.c ./kernel/irq.c ./drivers/serial.c ./drivers/ata.c ./drivers/keyboard.c ./fs/fat.c ./kernel/gdt.c ./fs/file.c"
OUTFILES="./kernel.o ./io.o ./term.o ./idt.o ./irq.o ./mem.o ./init.o ./serial.o ./ata.o ./keyboard.o ./fat.o ./gdt.o ./file.o"

CC=gcc
OPT="-nostdinc -fno-stack-protector -m32 -c -w -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow -mno-red-zone"
AS=nasm
LINKER=ld
BUILD=./build

$CC $OPT -I ./Include $KERNELFILES -g
$AS ./kernel/asm/idt.asm -f elf -o ./idt.o
$AS ./boot/multiboot.asm -f elf -o ./build/multiboot.o
$LINKER -melf_i386 -T ./kernel/kernel.ld -o ./build/kernel.elf ./build/kboot.o $OUTFILES