UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	AS=as --32
	LD=ld -m elf_i386
endif

ifeq ($(UNAME), Darwin)
	AS=i686-elf-as
	LD=i686-elf-ld
	BOCHS_FLAG='display_library: sdl2'
endif

GDB=gdb

QEMU=qemu-system-i386
BOCHS=bochs
IMG=final.img

.PHONY=clean run all

BOOT_OBJS=bootsect.o

%.o: %.s
	$(AS) -o $@ $<

all: $(IMG)

$(IMG): bootsect
	dd if=$(word 1, $^) of=$@ bs=1 count=512

bootsect: $(BOOT_OBJS)
	$(LD) --oformat binary -e start -Ttext 0x7c00 -o $@ $^

run: $(IMG)
	$(QEMU) -boot a -drive file=$<,format=raw,index=0,if=floppy

run_bochs: $(IMG)
	$(BOCHS) -qf /dev/null \
		'floppya: 1_44=$<, status=inserted' \
		'boot: floppy' \
		$(BOCHS_FLAG)

run_debug: $(IMG)
	$(QEMU) -s -S -boot a -drive file=$<,format=raw,index=0,if=floppy &
	$(GDB) -q -x gdb.gdb

clean:
	@rm -f bootsect kernel $(BOOT_OBJS) $(IMG)
