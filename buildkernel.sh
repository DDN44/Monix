#!/bin/bash

KERNELFILES="./kernel/kernel.c ./kernel/stdker/io.c ./kernel/term/term.c ./kernel/mem/mem.c ./kernel/init.c ./kernel/irq.c ./drivers/serial.c ./drivers/ata.c"
OUTFILES="./kernel.o ./io.o ./term.o ./idt.o ./irq.o ./mem.o ./init.o ./serial.o ./ata.o"

CC=/home/me/cross/bin/i686-elf-gcc
OPT="-c -w -nostdinc -mno-mmx -mno-sse -mno-sse2 -mno-sse3 -mno-3dnow -mno-red-zone"
AS=nasm
LINKER=/home/me/cross/bin/i686-elf-ld
BUILD=./build

$CC $OPT -I ./Include $KERNELFILES -g
$AS ./kernel/asm/idt.asm -f elf -o ./idt.o
$LINKER -T ./kernel/kernel.ld -o ./build/kernel.bin $BUILD/kboot.o $OUTFILES