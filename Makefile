# This is a GNU Make makefile for the Calypsi C compiler targetting TOS
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
# Make is an ubiquitous tool available on all platforms and has been around for
# 40 years or so.


# General preferences ---------------------------------------------------------

# What is this: options that translate into command line options for Calypsi.

# Code model: large (full address space addressing) or small (PC-relative)
CODE_MODEL=large
# Data model: small (a4-relative), large (full-address space addressing and a4-relative), or far-only (full address space addressing, a4 is general purpose)
DATA_MODEL=small
# stack size
STACK_SIZE=2048
# Target hardware. The compiler can make use of hardware FPU etc. Can be left blank.
TARGET_HW=Foenix
# Enable 64-bit double-precision floating point numbers (default is 32bits).
DOUBLE64=yes
# Include debugging information. Makes executables bigger.
DEBUG=yes


# Preferences -----------------------------------------------------------------

# Note for beginners: we're only setting variables here, that we can then use
# in receipies. Most variables we defined here are used by builtin receipies,
# see https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html
# Due to historical reason, 'make' has convenient implicit rules for building 
# object files

# Assembly
AS=as68k
ASFLAGS=
ifeq ($(DEBUG),yes)
  ASFLAGS += --debug
else
 $(error wrong DEBUG)
endif

# C
CC=cc68k
CFLAGS=--data-model $(DATA_MODEL) --code-model $(CODE_MODEL)

ifneq ($(TARGET_HW),)
  CFLAGS += --target $(TARGET_HW)
endif
ifeq ($(DOUBLE64),yes)
  CFLAGS += --64bit-doubles
endif
ifeq ($(DEBUG),yes)
  CFLAGS += --debug
endif

# Linker
LD=ln68k
CLIB=clib-68000
# Code model
ifeq ($(CODE_MODEL),large)
  LIB_CODE_MODEL := lc
else ifeq ($(CODE_MODEL),small)
  LIB_CODE_MODEL := sc
else
  $(error Unrecognized code model)
endif
# Data model
ifeq ($(DATA_MODEL),large)
  LIB_DATA_MODEL := ld
else ifeq ($(DATA_MODEL),small)
  LIB_DATA_MODEL := sd
else ifeq ($(DATA_MODEL),far-only)
  LIB_DATA_MODEL := fod
else
  $(error Unrecognized data model)
endif
# Target
ifeq ($(TARGET_HW),Foenix)
  LIB_TARGET_HW := -Foenix
else ifeq ($(TARGET_HW),)
  LIB_TARGET_HW :=
else
  $(error Unrecognized target hardware)
endif
# 64-bit doubles
ifeq ($(DOUBLE64),yes)
  LIB_DOUBLE64 := -double64
else ifeq ($(DOUBLE64),no)
  LIB_DOUBLE64 :=
else
  $(error Unrecognized setting for DOUBLE64)
endif
CLIB = clib-68000-$(LIB_CODE_MODEL)-$(LIB_DATA_MODEL)$(LIB_DOUBLE64)$(LIB_TARGET_HW).a

LDFLAGS=--output-format=tos --cross-reference $(CLIB) --rtattr cstartup=tos --stack-size $(STACK_SIZE)
# Note: --hosted is assumed for the TOS target

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
OBJS=crt0.o crt.o main.o


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

$(MAIN_TARGET): $(OBJS) toslib.a libc_stubs.a
	$(LD) $^ $(LDFLAGS)
	$(REN) ln68k.prg $@
# Convenience: copy that to the folder mounted as Atari drive in your favourite emulator
	$(CP) $@ /mnt/c/Atari/Disques/F_Coding/

# Builds the TOS library, containing bindings for the TOS operating system
toslib.a: bios_stubs.o xbios_stubs.o gemdos_stubs.o
	$(AR) $@ $^

# Builds the stubs which "glue" the standard C library to the OS
libc_stubs.a: libc_stubs.o
	$(AR) $@ $^

# This is a phony target just to remove all build artifacts
clean:
	$(RM) *.a *.elf *.s68 *.hunk *.o *.lst *.prg toslib.a libc_stubs.a
