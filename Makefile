AS=as
CC=gcc
Ld=ld

CFLAGS= -Iarch/amd64/ -Iinclude/
LDFLAGS=

INCLUDE= 

OBJECT= arch/amd64/asm/boot.o arch/amd64/asm/context_switch.o arch/amd64/mm_tables.o \
boot/main.o mm/global.o mm/map.o mm/mm.o proc/sched.o proc/thread.o resource/kid.o \
resource/kprocess.o resource/kthread.o

.PHONY:kernel
kernel:$(OBJECT)




.PHONY:clean
clean:
	rm -f $(OBJECT)
