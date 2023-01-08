	.public Pterm0
Pterm0:
	clr.w	-(sp)
	trap	#1

	.public Cconout
Cconout:
	move.w    d0,-(sp)
	move.w    #2,-(sp)
	trap      #1
	addq.l    #4,sp
	rts

	.public Cnecin
Cnecin:
	move.w	#8,-(sp)
	trap	#1
	addq.l	#2,sp
	rts

	.public Cconws
Cconws:
	move.l	a0,-(sp)
	move.w	#9,-(sp)
	trap	#1
	addq.l	#6,sp
	rts

	.public Cconrs
Cconrs:
	move.l	a0,-(sp)
	move.w	#10,-(sp)
	trap	#1
	addq.l	#6,sp
	rts

	.public Mshrink
Mshrink:
	move.l  d0,-(sp)
	move.l  a0,-(sp)
	move.w  #0,-(sp)
	move.w  #74,-(sp)
	trap    #1
	lea     0xc(sp),sp
	rts

	.public Pterm
Pterm
	move.w	d0,-(sp)
	move.w	#76,-(sp)
	trap	#1
	