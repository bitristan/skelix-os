# skelix-os
Make a version of Skelix OS which can run on linux/mac. http://skelix.net/skelixos/index_en.html

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

## tutorial 01: bootstrap

