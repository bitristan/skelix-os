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
HD=hd.img

.PHONY=clean run all

BOOT_OBJS=bootsect.o
KERNEL_SYM=kernel.sym
KERNEL_OBJS= load.o init.o isr.o timer.o libcc.o scr.o kb.o task.o kprintf.o hd.o exceptions.o fs.o

.s.o:
	$(AS) $< -Iinclude -o $*.o

.c.o:
	$(CC) $(CFLAGS) -c $< -Iinclude -o $*.o

all: $(IMG)

$(IMG): bootsect kernel
	rm -f $(HD)
	bximage -func=create -imgmode=flat -hd=60 -q $(HD)
	dd if=/dev/zero of=$@ bs=1024 count=1440
	dd if=$(word 1, $^) of=$@ bs=512 count=1 conv=notrunc
	dd if=$(word 2, $^) of=$@ bs=512 seek=1 conv=notrunc

bootsect: $(BOOT_OBJS)
	$(LD) --oformat binary -e start -Ttext 0x7c00 -o $@ $^

kernel: $(KERNEL_OBJS)
	$(LD) --oformat binary -N -e pm_mode -Ttext 0x0000 -o $@ $^

$(KERNEL_SYM): $(KERNEL_OBJS)
	$(LD) -N -e pm_mode -Ttext 0x0000 -o $@ $(KERNEL_OBJS)

run: $(IMG)
	$(QEMU) -boot a -drive file=$<,format=raw,index=0,if=floppy \
		-drive file=$(HD),format=raw,media=disk

run_bochs: $(IMG)
	$(BOCHS) -qf /dev/null \
		'floppya: 1_44=$<, status=inserted' \
		'boot: floppy' \
		'ata0: enabled=1, ioaddr1=0x1f0, ioaddr2=0x3f0, irq=14' \
		'ata0-master: type=disk, mode=flat, path="$(HD)"' \
		$(BOCHS_FLAG)

run_debug: $(IMG) $(KERNEL_SYM)
	$(QEMU) -s -S -boot a -drive file=$<,format=raw,index=0,if=floppy \
		-drive file=$(HD),format=raw,media=disk &
	$(GDB) -q -x gdb.gdb -ex "symbol-file $(KERNEL_SYM)"

clean:
	@rm -f bootsect kernel $(BOOT_OBJS) $(KERNEL_OBJS) $(KERNEL_SYM) $(IMG) $(HD)
