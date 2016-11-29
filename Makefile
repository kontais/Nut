AS=as
CC=gcc
Ld=ld

CFLAGS= -Iarch/x86/ -Iinclude/ -DX86 -I./ -Ilib/ -fno-asynchronous-unwind-tables -I./arch/x86/video/ -fno-builtin -fpie
LDFLAGS= --script=./ldscript -nostdlib

INCLUDE= 

INIT_SOURCE= arch/x86/init/init.S arch/x86/init/init_mm_map.c  arch/x86/early_print.c lib/assert.c lib/printf.c  arch/x86/serial_port/serial_port.c arch/x86/init/init_dsc_tables.c arch/x86/init/exception_handler.S arch/x86/debug/dump_reg.c
INIT_OBJS= init.o init_mm_map.o early_print.o assert.o printf.o serial_port.o init_dsc_tables.o exception_handler.o dump_reg.o


OBJS=  boot/main.o arch/x86/serial_port/serial_port.o arch/x86/video/vga.o arch/x86/early_print.o lib/assert.o lib/printf.o  lib/string.o arch/x86/paging.o arch/x86/asm/start.o

.PHONY:all
all:init kernel
	cat init kernel > kernel.img

.PHONY:init
init:
	$(CC) -c $(CFLAGS) $(INIT_SOURCE) -fPIE  
	$(LD) --script=./init_ldscript -nostdlib -o init $(INIT_OBJS)
.PHONY:kernel
kernel:$(OBJS)
# 	$(CC) -c  $(CFLAGS) $(PIE_SOURCE)
	$(LD) -o kernel $(OBJS) $(LDFLAGS)
.PHONY:clean
clean:
	rm -f $(OBJS) init kernel kernel.img $(INIT_OBJS)
