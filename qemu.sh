#!/bin/bash

<<<<<<< HEAD
qemu-system-i386 -m 512M -boot menu=on -hda ./drive2 -cdrom ./Monix.iso -serial stdio
=======
qemu-system-i386 -m 512M -boot menu=on -hda ./drive2 -cdrom ./Monix.iso -serial stdio
>>>>>>> 4b18a3a (Many improvements)

##qemu-system-i386 -m 512m -boot menu=on -hda ./testdisk.img -cdrom ./Monix.iso -serial stdio