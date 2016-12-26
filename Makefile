AS=as
CC=gcc
Ld=ld

COMMON_CFLAGS= -Iarch/x86/ -Iinclude/ -DX86 -I./ -Ilib/ -fno-asynchronous-unwind-tables -I./arch/x86/video/ -fno-builtin -Ifs/ -Isyscall/ -Iproc/ -Imm/ -Icommon/ -mno-sse -msoft-float
CFLAGS=  $(COMMON_CFLAGS) -mcmodel=large -fstack-protector
LDFLAGS= --script=./ldscript -nostdlib 

INCLUDE= 

INIT_CFLAGS= $(COMMON_CFLAGS) -c -fpie
INIT_LDFLAGS=  --script=./init_ldscript -nostdlib -pie

INIT_SOURCE= arch/x86/init/init.S arch/x86/init/init_mm_map.c  arch/x86/init/early_print.c lib/assert.c lib/printf.c  arch/x86/serial_port/serial_port.c arch/x86/init/init_dsc_tables.c arch/x86/init/exception_handler.S arch/x86/init/dump.c lib/string.c
INIT_OBJS= init.o init_mm_map.o early_print.o assert.o printf.o serial_port.o init_dsc_tables.o exception_handler.o dump.o string.o

OBJS=  boot/main.o  arch/x86/video/vga.o lib/assert.o lib/printf.o  lib/string.o  arch/x86/asm/start.o arch/x86/paging.o lib/bug.o arch/x86/int_ctl.o arch/x86/isa.o arch/x86/asm/interrupt_handler.o mm/vm.o arch/x86/asm/exception_handler.o arch/x86/pci.o fs/fat.o syscall/syscall.o fs/fs.o lib/coding.o proc/sched.o arch/x86/asm/context_switch.o proc/proc.o proc/thread.o arch/x86/context.o lib/queue.o syscall/sys_syscall.o mm/malloc.o proc/exec.o mm/vm_map.o proc/id.o syscall/sys_open.o syscall/sys_write.o fs/fs_special.o syscall/sys_read.o syscall/sys_ioctl.o syscall/sys_fstat.o syscall/sys_lseek.o syscall/sys_fork.o fs/fs_generic.o  syscall/sys_close.o proc/fork.o proc/exit.o syscall/sys_exit.o syscall/sys_exec.o arch/x86/debug/stack_guard.o

.PHONY:all
all:init kernel
	cat init kernel > kernel.img

.PHONY:init
init:
	$(CC) $(INIT_CFLAGS) $(INIT_SOURCE)
	$(LD) $(INIT_LDFLAGS) $(INIT_OBJS) -o init
.PHONY:kernel
kernel:$(OBJS)
# 	$(CC) -c  $(CFLAGS) $(PIE_SOURCE)
	$(LD) -o kernel $(OBJS) $(LDFLAGS)
	$(LD) -o kernel.elf $(OBJS) $(LDFLAGS) --oformat=elf64-x86-64
.PHONY:clean
clean:
	rm -f $(OBJS) init kernel kernel.img kernel.elf $(INIT_OBJS)
