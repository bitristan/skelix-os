UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	AS=as --32
	LD=ld -m elf_i386
	CC=gcc -m32
endif

ifeq ($(UNAME), Darwin)
	AS=i686-elf-as
	LD=i686-elf-ld
	CC=i686-elf-gcc
	BOCHS_FLAG='display_library: sdl2'
endif

GDB=gdb
CFLAGS=-g -fno-builtin -fno-pic

QEMU=qemu-system-i386
BOCHS=bochs
IMG=final.img

.PHONY=clean run all

BOOT_OBJS=bootsect.o
KERNEL_SYM=kernel.sym
KERNEL_OBJS=load.o init.o isr.o libcc.o scr.o kprintf.o exceptions.o

.s.o:
	$(AS) $< -Iinclude -o $*.o

.c.o:
	$(CC) $(CFLAGS) -c $< -Iinclude -o $*.o

all: $(IMG)

$(IMG): bootsect kernel
	dd if=$(word 1, $^) of=$@ bs=512 count=1
	dd if=$(word 2, $^) of=$@ bs=512 seek=1 conv=notrunc

bootsect: $(BOOT_OBJS)
	$(LD) --oformat binary -e start -Ttext 0x7c00 -o $@ $^

kernel: $(KERNEL_OBJS)
	$(LD) --oformat binary -N -e pm_mode -Ttext 0x0000 -o $@ $^

$(KERNEL_SYM): $(KERNEL_OBJS)
	$(LD) -N -e pm_mode -Ttext 0x0000 -o $@ $(KERNEL_OBJS)

run: $(IMG)
	$(QEMU) -boot a -drive file=$<,format=raw,index=0,if=floppy

run_bochs: $(IMG)
	$(BOCHS) -qf /dev/null \
		'floppya: 1_44=$<, status=inserted' \
		'boot: floppy' \
		$(BOCHS_FLAG)

run_debug: $(IMG) $(KERNEL_SYM)
	$(QEMU) -s -S -boot a -drive file=$<,format=raw,index=0,if=floppy &
	$(GDB) -q -x gdb.gdb -ex "symbol-file $(KERNEL_SYM)"

clean:
	@rm -f bootsect kernel $(BOOT_OBJS) $(KERNEL_OBJS) $(KERNEL_SYM) $(IMG)
