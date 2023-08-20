; Startup file for GEMDOS / TOS programs (not desk accessories)
; TabSize=8
	.rtmodel cstartup,"tos" ; Tell that we're not using the default startup from the C library
	.rtmodel version, "1"
	.rtmodel core, "*"

	; External declarations
	.section heap
	.section stack
	.section data_init_table

	.extern __initialize_data, __initialize_udata
	.extern main, exit

	; OS methods used in this file
	.extern Mshrink

#ifdef __CALYPSI_DATA_MODEL_SMALL__
	.extern _NearBaseAddress
#endif

#ifdef __CALYPSI_TARGET_SYSTEM_FOENIX__
	.extern _Gavin
# define GavinLow   0x00b00000
# define GavinHigh  0xfec00000
#endif

#include "macros.h"


	.section tos_start, root, noreorder

	.public __program_root_section
__program_root_section: ; Earliest entry point of the program



; ***************************************************************************
;
; __program_start - actual start point of the program
;
; Initialize sections, stack, shrink TPA, parse command lines and call main().
;
; ***************************************************************************

	.public __program_tos_start
__program_tos_start:	; Program
	move.l	4(sp),a5		  ; Basepage

#ifdef __CALYPSI_DATA_MODEL_SMALL__
	move.l	8(a5),a4	;Start of TEXT
	adda.l	#_NearBaseAddress,a4
#endif

; Initialize data sections if needed.
	.section tos_start, noroot, noreorder
	.pubweak __data_initialization_needed

	.extern __initialize_sections
	.align	2
__data_initialization_needed:
	move.l	#(.sectionStart data_init_table),a0
	move.l	#(.sectionEnd data_init_table),a1
	call	__initialize_sections

; Initialize streams if needed.
	.section tos_start, noroot, noreorder
	.pubweak __call_initialize_global_streams
	.extern __initialize_global_streams
__call_initialize_global_streams:
	call	__initialize_global_streams

; Initialize heap if needed.
	.section tos_start, noroot, noreorder
	.pubweak __call_heap_initialize
	.extern __heap_initialize, __default_heap
__call_heap_initialize:
	move.l	#.sectionSize heap,d0
	move.l	#__default_heap,a0
	move.l	#.sectionStart heap,a1
	call	__heap_initialize

	.section tos_start, noroot, noreorder
#ifdef __CALYPSI_TARGET_SYSTEM_FOENIX__
	.pubweak _Gavin_initialize
_Gavin_initialize:
	move.l	#GavinLow,a0  ; assume A2560U system
	cmp.w	#0x4567,0x0010(a0) ; check byte order
	beq.s	20$
	move.l	#GavinHigh,a0 ; no, assume A2560K 32-bit
20$:
      ; keep base pointer to Gavin
#ifdef __CALYPSI_DATA_MODEL_SMALL__
	move.l	a0,(.near _Gavin,A4)
#else
	move.l	a0,_Gavin
#endif // __CALYPSI_DATA_MODEL_SMALL__
#endif // __CALYPSI_TARGET_SYSTEM_FOENIX__

	.section tos_start, root, noreorder
	move.l	a5,__basepage
	move.l	#.sectionEnd stack,d7
	andi.l #-2,d7	; Even address
	move.l	d7,sp	; Setup stack

	; Compute required size of TPA
	move.l	__basepage,a5	; BASEPAGE
	move.l	#256,d0	    ; sizeof(BASEPAGE)
	add.l	12(a5),d0   ; TEXT length
	add.l	20(a5),d0   ; DATA length
	add.l	28(a5),d0   ; BSS length

	; Compute stack size (bug with ".sectionSize stack")
	moveq #1,d1
	add.l #.sectionEnd stack,d1
	sub.l #.sectionStart stack,d1
	add.l d1,d0

	; Shrink the Transient Program Area to what is really needed
	move.l	a5,a0	    ; d0 already contains the new TPA size
	call	Mshrink

app:	; Command line parameters
	.extern parse_cmd_line	; in crt.c
	lea	128(a5),a0 ; command line, first byte is length
	moveq	#0,d0
	move.b	(a0)+,d0  ; command line length, a0 now points to start of cmd line string
	lea.l	.sectionStart stack,a1	   ; argv is at the bottom of the stack
	call	 parse_cmd_line ; upon return, d0 is argc
	; Pass the rest to main
	move.l	44(a5),a1	; environment
	move.l	a1,__env	; _Stub_environ needs to access the environment
	lea.l	.sectionStart stack,a0 ; argv

call_main:
	call	main

	.extern Pterm ; CHANGE ME TODO exit should be in charge
	call	Pterm
	jump	exit


	; DATA
#ifdef __CALYPSI_DATA_MODEL_SMALL__
	.section near,data
#else
	.section far,data
#endif
_empty_string:	.space 2,0


	; BSS
#ifdef __CALYPSI_DATA_MODEL_SMALL__
	.section znear,bss
#else
	.section zfar,bss
#endif
	.align 4
	.public __basepage, __env
__basepage:	.space 4 ; pointer to basepage
__env:		.space 4 ; environment string
