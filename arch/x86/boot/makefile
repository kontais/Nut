AS = as
LD = ld
ASFLAGS = -m16
LDFLAGS = --script=./ldscript -nostdlib --oformat=binary -m elf_i386
CFLAGS = -m16 -fno-asynchronous-unwind-tables -I ./ -I ../
OBJS = init.o main16.o

.PHONY:all
all:$(OBJS)
	$(LD) $(OBJS) -o boot $(LDFLAGS)

.PHONY:clean
clean:
	rm -f boot.o boot $(OBJS)
