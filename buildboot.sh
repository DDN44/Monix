#!/bin/bash

BOOT=./boot
BUILD=./build
KERNEL=./kernel

nasm $BOOT/boot.asm -f bin -o $BUILD/boot.o
nasm $KERNEL/kernel.asm -f elf -o $BUILD/kboot.o