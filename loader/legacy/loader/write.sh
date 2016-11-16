#!/bin/bash

if [ $1 == "" ]
	then echo "Usage:./write.sh [target device]";
else
	bootsec_size=`stat -c%s bootsec`
	dd if=$1 of=mbr.img bs=1 count=$((512-$bootsec_size)) skip=$bootsec_size
	cat bootsec mbr.img boot > boot.img
	dd if=boot.img of=$1
	bootimage_size=`stat -c%s boot`
	echo "Boot image size is $bootimage_size bytes"
fi
