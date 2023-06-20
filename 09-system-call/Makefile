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
BOOTIMG=final.img

.PHONY=clean run all

KERNEL_OBJS= load.o init.o isr.o timer.o libcc.o scr.o kb.o task.o kprintf.o hd.o fs.o mm.o exceptions.o syscall.o

.s.o:
	$(AS) $< -Iinclude -o $*.o

.c.o:
	$(CC) $(CFLAGS) -c $< -Iinclude -o $*.o

all: $(BOOTIMG) color

$(BOOTIMG): bootsect kernel
	cat bootsect kernel > final.img
	@wc -c final.img

color: color.o
	${LD} --oformat binary -N -e color -Ttext 0x100000 -o color $<

bootsect: bootsect.o
	${LD} --oformat binary -N -e start -Ttext 0x7c00 -o bootsect $<

kernel: ${KERNEL_OBJS}
	$(LD) --oformat binary -N -e pm_mode -Ttext 0x0000 -o $@ ${KERNEL_OBJS}
	@wc -c kernel

kernel.sym: ${KERNEL_OBJS}
	$(LD) -N -e pm_mode -Ttext 0x0000 -o $@ ${KERNEL_OBJS}

color: color.o
	$(LD) --oformat binary -N -e color -Ttext 0x100000 -o color $<

run: $(BOOTIMG)
	$(QEMU) -boot a -fda $(BOOTIMG)

run_bochs: $(BOOTIMG)
	$(BOCHS) -qf /dev/null \
		'floppya: 1_44=$(BOOTIMG), status=inserted' \
		'boot: floppy' \
		$(BOCHS_FLAG)

run_debug: $(BOOTIMG) kernel.sym
	$(QEMU) -s -S -boot a -fda $(BOOTIMG) -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.sym"

clean:
	@rm -f *.img kernel kernel.sym bootsect color *.o
