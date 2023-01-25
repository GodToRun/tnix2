#! /bin/bash
cd src
cd userland
cd stdlib
make
cd ..
cd hello
make
cd ..
cd ..
make all
cd ..
./make_initrd hello hello
sh update_image.sh
qemu-system-i386 -fda floppy.img
