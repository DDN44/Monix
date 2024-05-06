#!/bin/bash

qemu-system-i386 -m 512m -boot menu=on -hda ./testdisk.img -cdrom ./Monix.iso -serial stdio