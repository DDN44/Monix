#!/bin/bash

RED='\033[0;31m'
NC='\033[0m'

IMGFILE="./os.img"
BUILD="./build"
KBIN="$BUILD/kernel.bin"
IMGOUT="$BUILD/boot.o"
KERNELBYTES=$(wc -c < $KBIN)

echo -e $RED
echo -e $IMGFILE
echo -e $BUILD
echo -e $IMGOUT
echo -e "KERNELBYTES: $KERNELBYTES"
echo -e $NC
echo " "

rm -rf $IMGFILE
sleep 2
dd if=$IMGOUT of=$IMGFILE bs=512 count=1

dd if=$BUILD/bootloader.bin of=$IMGFILE bs=512 count=1 seek=1

dd if=$KBIN of=$IMGFILE seek=2
dd if=/dev/zero bs=1 count=$((8192-$KERNELBYTES)) >> $IMGFILE

dd if=/dev/zero bs=512 count=2877 >> $IMGFILE
