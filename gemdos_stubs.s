	; Thank you tos.hyp !
	
	.section code,text

	.public Pterm0
Pterm0:
	move.w	  #0,-(sp)
	trap	  #1
	addq.l	  #2,sp		; unreachable !
	rts

	.public Cconin
Cconin:
	move.w	  #1,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Cconout
Cconout:
	move.w	  d0,-(sp)
	move.w	  #2,-(sp)
	trap	  #1
	addq.l	  #4,sp
	rts

	.public Cauxin
Cauxin:
	move.w	  #3,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Cauxout
Cauxout:
	move.w	  d0,-(sp)
	move.w	  #4,-(sp)
	trap	  #1
	addq.l	  #4,sp
	rts

	.public Cprnout
Cprnout:	
	move.w	  d0,-(sp)
	move.w	  #5,-(sp)
	trap	  #1
	addq.l	  #4,sp
	rts

	.public Crawio
Crawio:	
	move.w	  d0,-(sp)
	move.w	  #6,-(sp)
	trap	  #1
	addq.l	  #4,sp
	rts

	.public Crawin
Crawin:
	move.w	  #7,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Cnecin
Cnecin:
	move.w	  #8,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Cconws
Cconws:
	move.l	  a0,-(sp)
	move.w	  #9,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Cconrs
Cconrs:	
	move.l	  a0,-(sp)
	move.w	  #10,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Cconis
Cconis:
	move.w	  #11,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Dsetdrv
Dsetdrv:
	move.w	  d0,-(sp)
	move.w	  #14,-(sp)
	trap	  #1
	addq.l	  #4,sp
	rts

	.public Cconos
Cconos:	
	move.w	  #16,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Cprnos
Cprnos:
	move.w	  #17,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Cauxos
Cauxos:	
	move.w	  #19,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Maddalt
Maddalt:	
	move.l	  d0,-(sp)
	move.l	  a0,-(sp)
	move.w	  #20,-(sp)
	trap	  #1
	lea	  0xA(sp),sp
	rts

	.public Srealloc
Srealloc:	
	move.l	  d0,-(sp)
	move.w	  #21,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Dgetdrv
Dgetdrv:
	move.w	  #25,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Fsetdta
Fsetdta:
	move.l	  a0,-(sp)
	move.w	  #26,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Super
Super:
	move.l	  a0,-(sp)
	move.w	  #32,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Tgetdate
Tgetdate:	
	move.w	  #42,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Tsetdate
Tsetdate:
	move.w	  d0,-(sp)
	move.w	  #43,-(sp)
	trap	  #1
	addq.l	  #4,sp
	rts

	.public Tgettime
Tgettime:	
	move.w	  #44,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Tsettime
Tsettime:
	move.w	  d0,-(sp)
	move.w	  #45,-(sp)
	trap	  #1
	addq.l	  #4,sp
	rts

	.public Fgetdta
Fgetdta:	
	move.w	  #47,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Sversion
Sversion:
	move.w	  #48,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Ptermres
Ptermres:
	move.w	  d1,-(sp)
	move.l	  d0,-(sp)
	move.w	  #49,-(sp)
	trap	  #1
	addq.l	  #8,sp
	rts

	.public Dfree
Dfree:
	move.w	  d0,-(sp)
	move.l	  a0,-(sp)
	move.w	  #54,-(sp)
	trap	  #1
	addq.l	  #8,sp
	rts

	.public Dcreate
Dcreate:
	move.l	  a0,-(sp)
	move.w	  #57,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Ddelete
Ddelete:	
	move.l	  a0,-(sp)
	move.w	  #58,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Dsetpath
Dsetpath:
	move.l	  a0,-(sp)
	move.w	  #59,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Fcreate
Fcreate:
	move.w	  d0,-(sp)
	move.l	  a0,-(sp)
	move.w	  #60,-(sp)
	trap	  #1
	addq.l	  #8,sp
	rts

	.public Fopen
Fopen:
	move.w	  d0,-(sp)
	move.l	  a0,-(sp)
	move.w	  #61,-(sp)
	trap	  #1
	addq.l	  #8,sp
	rts

	.public Fclose
Fclose:
	move.w	  d0,-(sp)
	move.w	  #62,-(sp)
	trap	  #1
	addq.l	  #4,sp
	rts

	.public Fread
Fread:
	move.l	  a0,-(sp)
	move.l	  d1,-(sp)
	move.w	  d0,-(sp)
	move.w	  #63,-(sp)
	trap	  #1
	lea	  0xC(sp),sp
	rts

	.public Fwrite
Fwrite:
	move.l	  a0,-(sp)
	move.l	  d1,-(sp)
	move.w	  d0,-(sp)
	move.w	  #64,-(sp)
	trap	  #1
	lea	  0xC(sp),sp
	rts

	.public Fdelete
Fdelete:
	move.l	  a0,-(sp)
	move.w	  #65,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Fseek
Fseek:
	move.w	  4(sp),-(sp)
	move.w	  d1,-(sp)
	move.l	  d0,-(sp)
	move.w	  #66,-(sp)
	trap	  #1
	lea	  0xA(sp),sp
	rts

	.public Fattrib
Fattrib:
	move.w	  d1,-(sp)
	move.w	  d0,-(sp)
	move.l	  a0,-(sp)
	move.w	  #67,-(sp)
	trap	  #1
	lea	  0xA(sp),sp
	rts

	.public Mxalloc
Mxalloc:
	move.w	  d1,-(sp)
	move.l	  d0,-(sp)
	move.w	  #68,-(sp)
	trap	  #1
	addq.l	  #8,sp
	rts

	.public Fdup
Fdup:
	move.w	  d0,-(sp)
	move.w	  #69,-(sp)
	trap	  #1
	addq.l	  #4,sp
	rts

	.public Fforce
Fforce:
	move.w	  d1,-(sp)
	move.w	  d0,-(sp)
	move.w	  #70,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Dgetpath
Dgetpath:
	move.w	  d0,-(sp)
	move.l	  a0,-(sp)
	move.w	  #71,-(sp)
	trap	  #1
	addq.l	  #8,sp
	rts

	.public Malloc
Malloc:
	move.l	  d0,-(sp)
	move.w	  #72,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Mfree
Mfree:	
	move.l	  a0,-(sp)
	move.w	  #73,-(sp)
	trap	  #1
	addq.l	  #6,sp
	rts

	.public Mshrink
Mshrink:
	move.l	  d0,-(sp)
	move.l	  a0,-(sp)
	move.w	  #0,-(sp)
	move.w	  #74,-(sp)
	trap	  #1
	lea	  0xC(sp),sp
	rts

	.public Pexec
Pexec:
	move.l	  4(sp),-(sp)
	move.l	  a1,-(sp)
	move.l	  a0,-(sp)
	move.w	  d0,-(sp)
	move.w	  #75,-(sp)
	trap	  #1
	lea	  0x10(sp),sp
	rts

	.public Pterm
Pterm:	
	move.w	  d0,-(sp)
	move.w	  #76,-(sp)
	trap	  #1
	addq.l	  #4,sp
	rts

	.public Fsfirst
Fsfirst:
	move.w	  d0,-(sp)
	move.l	  a0,-(sp)
	move.w	  #78,-(sp)
	trap	  #1
	addq.l	  #8,sp 
	rts

	.public Fsnext
Fsnext:
	move.w	  #79,-(sp)
	trap	  #1
	addq.l	  #2,sp
	rts

	.public Frename
Frename:
	move.l	  a1,-(sp)
	move.l	  a0,-(sp)
	move.w	  #0,-(sp)
	move.w	  #86,-(sp)
	trap	  #1
	lea	  0xC(sp),sp
	rts

	.public Fdatime
Fdatime:
	move.w	  d1,-(sp)
	move.w	  d0,-(sp)
	move.l	  a0,-(sp)
	move.w	  #87,-(sp)
	trap	  #1
	lea	  0xA(sp),sp 
	rts

	.public Flock
Flock:
	move.l	  8(sp),-(sp)
	move.l	  8(sp),-(sp)
	move.w	  d1,-(sp)
	move.w	  d0,-(sp)
	move.w	  #92,-(sp)
	trap	  #1
	lea	  0xE(sp),sp
	rts
	
