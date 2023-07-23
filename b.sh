smlrcc -SI. -flat16 -origin 0x8000 *.c -o kern.bin
nasm -fbin boot.asm -o boot.bin
cat boot.bin kern.bin > kern.sys
rm *.bin
qemu-system-x86_64 -fda kern.sys
