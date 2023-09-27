#!/bin/bash

KERNELFILES="./kernel/kernel.c ./kernel/stdker/io.c ./kernel/term/term.c"
OUTFILES="./kernel.o ./io.o ./term.o ./irq.o"

CC=/home/me/cross/bin/i686-elf-gcc
AS=nasm
LINKER=/home/me/cross/bin/i686-elf-ld
BUILD=./build

$CC -c -nostdinc -I ./Include $KERNELFILES -g
$AS ./kernel/asm/irq.asm -f elf -o ./irq.o
$LINKER -T ./kernel/kernel.ld -o ./build/kernel.bin $BUILD/kboot.o $OUTFILES