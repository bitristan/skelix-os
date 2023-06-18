# skelix-os

Make a version of Skelix OS which can run on linux/mac which support bochs and qemu.

Please see more details from http://skelix.net/skelixos/index_en.html.

## environment setup

### linux

```
apt install binutils
```

Using *as --32* and *ld -m elf_i386* to compile 32-bit code.

### mac

```
brew install i686-elf-binutils
brew install i686-elf-gcc

brew install qemu
brew install bochs
```

### run

```
# run with qemu
make run

# run with bochs
make run_bochs

# run with qemu in debug mode
make run_debug
```

## tutorial

- 01: bootstrap

- 02: protected mode

- 04: interrupts

- 05-1: timer interrupt

- 05-2: keyboard interrupt

- 06: muti-tasking

- 07-1: filesystem: dpt create and read

In the demo, we create empty hard disk. Then the kernel will create a dpt for the hd automatically. You can also use fdisk tool to create dpt manually, then the kernel can read dpt info.

- 07-2: filesystem: fs create and read

- 07-3: filesystem: set up root directory
