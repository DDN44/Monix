#!/bin/bash

gcc -m32 -ffreestanding -nostdlib -fno-pie -c -o test.o test.c
ld -m elf_i386 -T test.ld test.o -o EXEC2