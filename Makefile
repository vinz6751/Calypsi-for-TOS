# This is a GNU Make makefile for the Calypsi C compiler targeting TOS
# You may obtain GNU Make from https://www.gnu.org/software/make/
# You may obtain Calypsi from https://www.calypsi.cc/
#
# It is deliberately verbose as it's intended to help non familiar users 
# get familiar with using Make.
# What is this:
# GNU Make is a build tool, i.e. you give it "receipes" for how to do things
# (e.g. link the main executable, assembly an object file from an assembly file,
# compile a C source file into an object file etc.), then you tell it what you
# want to build and it works out what needs done to achieve it (depending on
# what files have changed), and runs the receipes for building what needs it.
# Make is an ubiquitous tool available on all platforms.
#
# Caveat:
#  * the auto-dependencies don't work on Windows.
# To do:
#  * have build artifacts in a separate folder.

# General preferences ---------------------------------------------------------

# What is this: options that translate into command line options for Calypsi.
# All this can be overriden from the command line, e.g. if you want a stack
# size of 4096 instead you can do "make -DSTACK_SIZE=4096"

# Code model: large (full address space addressing) or small (PC-relative)
CODE_MODEL=large
# Data model: small (a4-relative), large (full-address space addressing and a4-relative), or far-only (full address space addressing, a4 is general purpose)
DATA_MODEL=small
# Stack size
STACK_SIZE=2048
# CPU core. Valid values are 68000, 68010
CPU_CORE=68000
# Target hardware. The compiler will try to use if e.g. for floating point
# operations. Possible values are : Foenix, can be left blank.
TARGET_HW=
# Target OS. Valid values are tos, mcp, srec
TARGET_OS=tos
# Enable 64-bit double-precision floating point numbers (default is 32bits).
DOUBLE64=no
# Include debugging information. Makes executables bigger. yes or no.
DEBUG=no


# Preferences -----------------------------------------------------------------

# Note for beginners: we're only setting variables here, that we can then use
# in receipies. Most variables we defined here are used by builtin receipies,
# see https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html
# Due to historical reason, 'make' has convenient implicit rules for building 
# object files

ifeq ($(CPU_CORE),68000)
  # 68000 is the default so we don't specify it to keep the command line short
else
  CPU_CORE_FLAG=--core $(CPU_CORE)
endif

# Assembly
AS=as68k
ASFLAGS=$(CPU_CORE_FLAG)
ifeq ($(DEBUG),yes)
  ASFLAGS += --debug --list-file=$(@:%.o=%.lst)
else ifeq ($(DEBUG),no)
else
  $(error Unrecognized DEBUG value)
endif

# C
CC=cc68k
CFLAGS=--data-model $(DATA_MODEL) --code-model $(CODE_MODEL) $(CPU_CORE_FLAG)

ifneq ($(TARGET_HW),)
  CFLAGS += --target $(TARGET_HW)
endif
ifeq ($(DOUBLE64),yes)
  CFLAGS += --64bit-doubles
endif
ifeq ($(DEBUG),yes)
  CFLAGS += --debug --list-file=$(@:%.o=%.lst)
endif

# Linker
LD=ln68k
# Code model
ifeq ($(CODE_MODEL),large)
  LIB_CODE_MODEL := lc
else ifeq ($(CODE_MODEL),small)
  LIB_CODE_MODEL := sc
else
  $(error Unrecognized CODE_MODEL value)
endif
# Data model
ifeq ($(DATA_MODEL),large)
  LIB_DATA_MODEL := ld
else ifeq ($(DATA_MODEL),small)
  LIB_DATA_MODEL := sd
else ifeq ($(DATA_MODEL),far-only)
  LIB_DATA_MODEL := fod
else
  $(error Unrecognized DATA_MODEL value)
endif
# Target
ifeq ($(TARGET_HW),Foenix)
  LIB_TARGET_HW := -Foenix
else ifeq ($(TARGET_HW),)
  LIB_TARGET_HW :=
else
  $(error Unrecognized TARGET_HW value)
endif
# 64-bit doubles
ifeq ($(DOUBLE64),yes)
  LIB_DOUBLE64 := -double64
else ifeq ($(DOUBLE64),no)
  LIB_DOUBLE64 :=
else
  $(error Unrecognized DOUBLE64 value)
endif
CLIB = clib-$(CPU_CORE)-$(LIB_CODE_MODEL)-$(LIB_DATA_MODEL)$(LIB_DOUBLE64)$(LIB_TARGET_HW).a

LDFLAGS=--stack-size $(STACK_SIZE) $(CLIB)
ifeq ($(TARGET_OS),tos)
  LDFLAGS += --output-format=tos --rtattr cstartup=tos
  # Note: --hosted is assumed for the TOS target
else ifeq ($(TARGET_OS),mcp)
  LDFLAGS += --output-format=pgz --hosted
else ifeq ($(TARGET_OS),srec)
  LDFLAGS += --output-format=s68 --hosted
else ifeq ($(TARGET_OS),raw)
  LDFLAGS += --output-format=raw --hosted
endif

ifeq ($(DEBUG),yes)
  LDFLAGS +=-l --cross-reference
endif

# Librarian
AR=nlib

# OS-specific utilities
ifeq ($(OS),Windows_NT)
  CP=copy
  REN=ren
  MV=move
  RM=del /Q /F
else
  CP=cp
  REN=mv
  MV=mv
endif


# Program definition ----------------------------------------------------------

# Put the name of the executable you want to produce here
MAIN_TARGET=calypsi.prg

# Modules. list out your modules (whether they're assembly or C) here, with .o extension
# Leave crt0.s and crt.c in, as they're the required startup code for TOS.
SRC_C= main.c
SRC_S=

# Adapt to target OS by adding startup and libraries
ifeq ($(TARGET_OS),tos)
  SRC_STARTUP=crt0.o crt.o
  LIBS_OS=toslib.a libc_stubs_tos.a
endif

OBJS_C=$(SRC_C:.c=.o)
OBJS_S=$(SRC_S:.o=.s)
OBJS=$(SRC_STARTUP) $(OBJS_C) $(OBJS_S) $(LIBS_OS)


# Receipes --------------------------------------------------------------------

# What is this: receipes explain how a target depends on, and how to rebuild
# the target if any dependency has changed
# <target>: <dependencies>,...
# !!TAB!!	action
# There are pseudo variables you can use in actions. E.g. $@ is the target's
# name, see https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html

# Phony targets are targets which don't really represent a file (so it doesn't
# make sense to try to see if a file with this name exists and is up to date),
# they're targets which receipe will always be executed whenever you try to
# "make" that target.

.PHONY:all clean

# It's conventional to have a "all" target which builds the main deliverable.
# If you run "make" without a target name, "make" tries to build the first
# target it finds in the make file, so it's usual to have "all" as first target.
all:$(MAIN_TARGET)

$(MAIN_TARGET): $(OBJS) 
	$(LD) $^ $(LDFLAGS)
	$(REN) ln68k.prg $@
# Convenience: copy that to the folder mounted as Atari drive in your favourite emulator
#	$(CP) $@ /mnt/c/Atari/Disques/F_Coding/

# Builds the stubs which "glue" the standard C library to the TOS
libc_stubs_tos.a: libc_stubs_tos.o
	$(AR) $@ $^

# Builds the TOS library, containing bindings for the TOS operating system
toslib.a: bios_stubs.o xbios_stubs.o gemdos_stubs.o
	$(AR) $@ $^

# Use the C compiler to produce a dependencies file specifying which header files
# a C file depends on, such that if one of these .h files are updated then the
# depending C files are rebuilt. The below is pretty much a copy paste from
# https://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html#Automatic-Prerequisites
ifeq ($(OS),Windows_NT)
# Windows has no "sed" command, so we can't follow the recommendation above.
# If you do want to make this work on Windows, you may try
# https://gnuwin32.sourceforge.net/packages/sed.htm
else
include $(OBJS_C:.o=.d)
%.d: %.c
	@set -e; $(RM) $@; \
		$(CC) --dependencies $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		$(RM) $@.$$$$
endif

# This is a phony target just to remove all build artifacts
clean:
	$(RM) *.a *.elf *.s68 *.bin *.hunk, *.pgz *.o *.d *.lst $(MAIN_TARGET) toslib.a libc_stubs_tos.a
