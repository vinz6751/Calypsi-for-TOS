# Assembly
AS=as68k
ASFLAGS=-l

# C
CC=cc68k
CFLAGS=--data-model small --code-model large

# Linker
LD=ln68k
LDFLAGS=--output-format=tos --cross-reference clib-68000-lc-sd.a --rtattr cstartup=tos --hosted

# Modules
OBJS=crt0.o crt.o main.o tos.o

all:calypsi.prg

PHONY:all clean

calypsi.prg: $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS)
	mv ln68k.prg $@
# Convenience: copy that to the folder mounted as Atari drive in your favourite emulator
#	cp $@ /mnt/c/Atari/Disques/F_Coding/

clean:
	$(RM) *.a *.elf *.o *.lst *.prg 2> /dev/null
