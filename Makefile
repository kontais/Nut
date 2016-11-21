AS=as
CC=gcc
Ld=ld

CFLAGS= -Iarch/x86/ -Iinclude/ -DX86 -I./ -Ilib/ -fno-asynchronous-unwind-tables -I./arch/x86/video/
LDFLAGS= --script=./ldscript -nostdlib  --oformat=binary 

INCLUDE= 

OBJS= arch/x86/asm/start.o boot/main.o arch/x86/SerialPortLib.o arch/x86/video/vga.o

.PHONY:kernel
kernel:$(OBJS)
# 	$(CC) -c $(CFLAGS) $(OBJS)
	$(LD) -o kernel.img $(OBJS) $(LDFLAGS)
.PHONY:clean
clean:
	rm -f $(OBJS) kernel.img
