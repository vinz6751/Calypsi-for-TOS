				; Thank you tos.hyp !

	.section code,text

        .public Initmouse
Initmouse:
	move.l	  a1,-(sp)
	move.l    a0,-(sp)
	move.w    d0,-(sp)
	move.w    #0,-(sp)
	trap      #14
	lea       12(sp),sp
	rts

    	.public Ssbrk
Ssbrk:
	move.w    d0,-(sp)
	move.w    #1,-(sp)
	trap      #14
	addq.l    #4,sp
	rts

        .public Physbase
Physbase:
	move.w    #2,-(sp)
	trap      #14
	addq.l    #2,sp
	rts

        .public Getrez
Getrez:
	move.w    #4,-(sp)
	trap      #14
	addq.l    #2,sp
	rts

        .public Setscreen
Setscreen:
	move.w    d0,-(sp)
	move.l    a1,-(sp)
	move.l    a0,-(sp)
	move.w    #5,-(sp)
	trap      #14
	lea       0xC(sp),sp
	rts

        .public Setcolor
Setcolor:
	move.w    d1,-(sp)
	move.w    d0,-(sp)
	move.w    #7,-(sp)
	trap      #14
	addq.l    #6,sp
	rts

        .public Floprd
Floprd:
	move.w    10(sp),-(sp)
	move.w    10(sp),-(sp)
	move.w    10(sp),-(sp)
	move.w    10(sp),-(sp)
	move.w    d1,-(sp)
	move.l    d0,-(sp)
	move.l    a0,-(sp)
	move.w    #8,-(sp)
	trap      #14
	lea       0x14(sp),sp
	rts

        .public Flopwr
Flopwr:
	move.w    10(sp),-(sp)
	move.w    10(sp),-(sp)
	move.w    10(sp),-(sp)
	move.w    10(sp),-(sp)
	move.w    d1,-(sp)
	move.l    d0,-(sp)
	move.l    a0,-(sp)
	move.w    #9,-(sp)
	trap      #14
	lea       0x14(sp),sp
	rts

        .public Flopfmt
Flopfmt:
	move.w    18(sp),-(sp)
	move.l    18(sp),-(sp)
	move.w    18(sp),-(sp)
	move.w    18(sp),-(sp)
	move.w    18(sp),-(sp)
	move.w    18(sp),-(sp)
	move.w    d1,-(sp)
	move.l    d0,-(sp)
	move.l	  a0,-(sp)
	move.w    #10,-(sp)
	trap      #14
	lea       0x1A(sp),sp
	rts

        .public Dbmsg
Dbmsg:
	move.l    4(sp),-(sp)
	move.w    d1,-(sp)
	move.w    d0,-(sp)
	move.w    #11,-(sp)
	trap      #14
	lea       10(sp),sp
	rts

        .public Midiws
Midiws:
	move.l	  a0,-(sp)
	move.w    d0,-(sp)
	move.w    #12,-(sp)
	trap      #14
	addq.l    #8,sp
	rts

        .public Mfpint
Mfpint:	
	move.l	  a0,-(sp)
	move.w    d0,-(sp)
	move.w    #13,-(sp)
	trap      #14
	addq.l    #8,sp
	rts

        .public Iorec
Iorec:
	move.w    d0,-(sp)
	move.w    #14,-(sp)
	trap      #14
	addq.l    #4,sp
	rts

        .public Rsconf
Rsconf:
	move.w    10(sp),-(sp)    ; Offset 12
	move.w    10(sp),-(sp)    ; Offset 10
	move.w    10(sp),-(sp)    ; Offset  8
	move.w    10(sp),-(sp)    ; Offset  6
	move.w    d1,-(sp)    ; Offset  4
	move.w    d0,-(sp)   ; Offset  2
	move.w    #15,-(sp)    ; Offset  0
	trap      #14          ; Call XBIOS
	lea       0xE(sp),sp    ; Correct stack
	rts

        .public Keytbl
Keytbl:
	move.l	  4(sp),-(sp)
	move.l	  a1,-(sp)
	move.l	  a0,-(sp)
	move.w    #16,-(sp)
	trap      #14
	lea       0xE(sp),sp
	rts

        .public Random
Random:
	move.w    #17,-(sp)
	trap      #14
	addq.l    #2,sp
	rts

        .public Protobt
Protobt:
	move.w    4(sp),-(sp)
	move.w    d1,-(sp)
	move.l    d0,-(sp)
	move.l    a0,-(sp)
	move.w    #18,-(sp)
	trap      #14
	lea       0xE(sp),sp
	rts

        .public Flopver
Flopver:
	move.w    10(sp),-(sp)
	move.w    10(sp),-(sp)
	move.w    10(sp),-(sp)
	move.w    10(sp),-(sp)
	move.w    d1,-(sp)
	move.l    d0,-(sp)
	move.l	  a0,-(sp)
	move.w    #19,-(sp)
	trap      #14
	lea       0x14(sp),sp
	rts

        .public Scrdmp
Scrdmp:
	move.w    #20,-(sp)
	trap      #14
	addq.l    #2,sp
	rts

        .public Cursconf
Cursconf:	
	move.w    d1,-(sp)
	move.w    d0,-(sp)
	move.w    #21,-(sp)
	trap      #14
	addq.l    #6,sp
	rts

        .public Settime
Settime:
	move.l    d0,-(sp)
	move.w    #22,-(sp)
	trap      #14
	addq.l    #6,sp
	rts

        .public Gettime
Gettime:
	move.w    #23,-(sp)
	trap      #14
	addq.l    #2,sp
	rts

        .public Bioskeys
Bioskeys:
	move.w    #24,-(sp)
	trap      #14
	addq.l    #2,sp
	rts

        .public Ikbdws
Ikbdws:
	move.l	  a0,-(sp)
	move.w    d0,-(sp)
	move.w    #25,-(sp)
	trap      #14
	addq.l    #8,sp
	rts

        .public Jdisint
Jdisint:
	move.w    d0,-(sp)
	move.w    #26,-(sp)
	trap      #14
	addq.l    #4,sp
	rts

        .public Jenabint
Jenabint:
	move.w    d0,-(sp)
	move.w    #27,-(sp)
	trap      #14
	addq.l    #4,sp
	rts

        .public Giaccess
Giaccess:	
	move.w    d1,-(sp)
	move.w    d0,-(sp)
	move.w    #28,-(sp)
	trap      #14
	addq.l    #6,sp
	rts

        .public Offgibit
Offgibit:
	move.w    d0,-(sp)
	move.w    #29,-(sp)
	trap      #14
	addq.l    #4,sp
	rts

        .public Ongibit
Ongibit:
	move.w    d0,-(sp)
	move.w    #30,-(sp)
	trap      #14
	addq.l    #4,sp
	rts

        .public Xbtimer
Xbtimer:
	move.l	  a0,-(sp)
	move.w    4(sp),-(sp)
	move.w    d1,-(sp)
	move.w    d0,-(sp)
	move.w    #31,-(sp)
	trap      #14
	lea       0xC(sp),sp
	rts

        .public Dosound
Dosound:
	move.l	  a0,-(sp)
	move.w    #32,-(sp)
	trap      #14
	addq.l    #6,sp
	move.l    d0,a0
	rts

        .public Setprt
Setprt:
	move.w    d0,-(sp)
	move.w    #33,-(sp)
	trap      #14
	addq.l    #4,sp
	rts

        .public Kbdvbase
Kbdvbase:
	move.w    #34,-(sp)
	trap      #14
	addq.l    #2,sp
	rts

        .public Kbrate
Kbrate:
	move.w    d1,-(sp)
	move.w    d0,-(sp)
	move.w    #35,-(sp)
	trap      #14
	addq.l    #6,sp
	rts

        .public Prtblk
Prtblk:
	move.l	  a0,-(sp)
	move.w    #36,-(sp)
	trap      #14
	addq.l    #6,sp
	rts

        .public Vsync
Vsync:
	move.w    #37,-(sp)
	trap      #14
	addq.l    #2,sp
	rts

        .public Supexec
Supexec:
	move.l	  a0,-(sp)
	move.w    #38,-(sp)    ; Offset 0
	trap      #14          ; Call XBIOS
	addq.l    #6,sp
	rts

        .public Puntaes
Puntaes:
	move.w    #39,-(sp)
	trap      #14
	addq.l    #2,sp
	rts

        .public Floprate
Floprate:
	move.w    d1,-(sp)
	move.w    d0,-(sp)
	move.w    #41,-(sp)
	trap      #14
	addq.l    #6,sp
	rts

        .public Bconmap
Bconmap:
	move.w    d0,-(sp)
	move.w    #44,-(sp)
	trap      #14
	addq.l    #4,sp
	rts

        .public Blitmode
Blitmode:
	move.w    d0,-(sp)
	move.w    #64,-(sp)
	trap      #14
	addq.l    #4,sp
	rts

