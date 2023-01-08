; Startup file for GEMDOS / TOS programs and desk accessories

              .rtmodel cstartup,"gemdos" ; Tell that we're not using the default startup from the C library

              .rtmodel version, "1"
              .rtmodel core, "*"

              ;; External declarations
              .section heap
              .section stack
              .section data_init_table

              .extern __initialize_data, __initialize_udata
              .extern main, exit

#ifdef __CALYPSI_DATA_MODEL_SMALL__
              .extern _NearBaseAddress
#endif

#ifdef __CALYPSI_TARGET_SYSTEM_FOENIX__
              .extern _Gavin
# define GavinLow   0x00b00000
# define GavinHigh  0xfec00000
#endif

#include "macros.h"

;;; ***************************************************************************
;;;
;;; __program_start - actual start point of the program
;;;
;;; Initialize sections, stack, shrink TPA, parse command lines and call main().
;;;
;;; ***************************************************************************



              .section gemdos_start, root, noreorder
              .public __program_root_section, __program_gemdos_start
               bra.s __program_root_section    ; Jump over header

               ; Header (holding program preferences)
_stack_size:   .long 16384                      ; stack size (16KB default)

__program_root_section:
__program_gemdos_start:
#ifdef __CALYPSI_DATA_MODEL_SMALL__
              move.l  4(sp),a4 ; Basepage
              move.l  8(a4),a4 ; Start of TEXT
              adda.l  #_NearBaseAddress,a4
#endif
;;; Initialize data sections if needed.
              .section gemdos_start, noroot, noreorder
              .pubweak __data_initialization_needed
              .extern __initialize_sections
              .align  2
__data_initialization_needed:
              move.l  #(.sectionStart data_init_table),a0
              move.l  #(.sectionEnd data_init_table),a1
              call    __initialize_sections

;;; **** Initialize streams if needed.
              .section gemdos_start, noroot, noreorder
              .pubweak __call_initialize_global_streams
              .extern __initialize_global_streams
__call_initialize_global_streams:
              call    __initialize_global_streams

;;; **** Initialize heap if needed.
              .section gemdos_start, noroot, noreorder
              .pubweak __call_heap_initialize
              .extern __heap_initialize, __default_heap
__call_heap_initialize:
              move.l  #.sectionSize heap,d0
              move.l  #__default_heap,a0
              move.l  #.sectionStart heap,a1
              call    __heap_initialize

              .section gemdos_start, noroot, noreorder
#ifdef __CALYPSI_TARGET_SYSTEM_FOENIX__
              .pubweak _Gavin_initialize
_Gavin_initialize:
              move.l  #GavinLow,a0  ; assume A2560U system
              cmp.w   #0x4567,0x0010(a0) ; check byte order
              beq.s   20$
              move.l  #GavinHigh,a0 ; no, assume A2560K 32-bit
20$:
              ;; keep base pointer to Gavin
#ifdef __CALYPSI_DATA_MODEL_SMALL__
              move.l  a0,(.near _Gavin,A4)
#else
              move.l  a0,_Gavin
#endif // __CALYPSI_DATA_MODEL_SMALL__
#endif // __CALYPSI_TARGET_SYSTEM_FOENIX__

                .section gemdos_start, root, noreorder
                ; Determine whether we're a program or a GEM desk accessory
                move.l  a0,d0
                seq     d0
                ext.w   d0
                move.w  d0,_is_acc

                ; Compute required size of TPA
                move.l  4(sp),a5    ; BASEPAGE
                move.l  a5,_basepage
                move.l  #256,d0     ; sizeof(BASEPAGE)
                add.l   12(a5),d0   ; TEXT length
                add.l   20(a5),d0   ; DATA length
                add.l   28(a5),d0   ; TEXT length

                ; Setup long-word-aligned stack (better for 68020+)
                add.l   _stack_size,d0
                addq.l  #3,d0
                andi.b  #-4,d0
                move.l  d0,d2       ; d0: size of required TPA
                add.l   8(a5),d2    ; d2: end of required TPA program area
                move.l  d2,_stack_top
                move.l  d2,d1
                sub.l   _stack_size,d1
                move.l  d1,_stack_bottom
                ; Setup stack / stack limit  ?
                move.l  d2,sp

                ; Shrink the Transient Program Area to what is really needed
                .extern Mshrink
                move.l  a5,a0       ; d0 already contains the new TPA size
                jsr     Mshrink

                ; If desk accessory, no environment and no command line parameters
                tst.w   _is_acc
                beq.s   app
                moveq   #0,d0
                lea     _empty_string,a0
                movea.l a0,a1
                bra.s   call_main

app:            ; Command line parameters
                .extern parse_cmd_line  ; in crt.c
                lea     128(a5),a0 ; command line, first byte is length
                moveq   #0,d0
                move.b  (a0)+,d0  ; command line length, a0 now points to start of cmd line string
                movea.l d1,a1     ; argv is at the bottom of the stack
                jsr     parse_cmd_line ; upon return, d0 is argc
                ; Pass the rest to main
                move.l  44(a5),a1        ; environment
                movea.l _stack_bottom,a0 ; argv

call_main:      call    main

                .extern Pterm ; CHANGE ME TODO exit should be in charge
                jsr     Pterm
                jump    exit


                ; DATA
#ifdef __CALYPSI_DATA_MODEL_SMALL__
                .section near,data
#else
                .section far,data
#endif
_empty_string:  .space 2,0


                ; BSS
#ifdef __CALYPSI_DATA_MODEL_SMALL__
                .section znear,bss
#else
                .section zfar,bss
#endif

                .public _is_acc, _basepage
_is_acc:        .space 2 ; 0 if program is app, 1 if is GEM desk accessory
_basepage:      .space 4 ; pointer to basepage
_stack_top:     .space 4 ; top of the stack
_stack_bottom:  .space 4 ; bottom of the stack (going below that corrupts BSS/DATA/TEXT)
