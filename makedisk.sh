#!/bin/bash

rm -rf disk.img

dd if=/dev/zero of=disk.img bs=512 count=60000

mkfs.fat -F16 disk.img