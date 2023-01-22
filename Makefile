# Assembly
AS=as68k
ASFLAGS=-l

# C
CC=cc68k
CFLAGS=--data-model small --code-model large

# Linker
LD=ln68k
LDFLAGS=--output-format=tos --cross-reference clib-68000-lc-sd.a --rtattr cstartup=tos --hosted

# Librarian
AR=nlib

# Modules
OBJS=crt0.o crt.o main.o

all:calypsi.prg

PHONY:all clean

calypsi.prg: $(OBJS) toslib.a libc_stubs.a
	$(LD) $^ $(LDFLAGS)
	mv ln68k.prg $@
# Convenience: copy that to the folder mounted as Atari drive in your favourite emulator
#	cp $@ /mnt/c/Atari/Disques/F_Coding/

toslib.a: bios_stubs.o xbios_stubs.o gemdos_stubs.o
	$(AR) $@ $^

libc_stubs.a: libc_stubs.o
	$(AR) $@ $^

clean:
	$(RM) *.a *.elf *.o *.lst *.prg toslib.a libc_stubs.a  2> /dev/null
