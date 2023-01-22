				; Thank you tos.hyp !

	.section code,text

    	.public Getmpb
Getmpb:
	move.l	a0,-(sp)
	move.w    #0,-(sp)
	trap      #13
	addq.l    #6,sp
	rts

    	.public Bconstat
Bconstat:	
	move.w    d0,-(sp)
	move.w 	  #1,-(sp)
	trap      #13
	addq.l    #4,sp
	rts

    	.public Bconin
Bconin:	
	move.w    d1,-(sp)
	move.w    #2,-(sp)
	trap      #13
	addq.l    #4,sp
	rts

    	.public Bconout
Bconout:
	move.w    d1,-(sp)
	move.w    d0,-(sp)
	move.w    #3,-(sp)
	trap      #13
	addq.l    #6,sp
	rts

	; Rwabs: todo

        .public Setexc
Setexc:	
	move.l	  a0,-(sp)
	move.w    d0,-(sp)
	move.w    #5,-(sp)
	trap      #13
	addq.l    #8,sp
	rts

        .public Tickcal
Tickcal:
	move.w    #6,-(sp)
	trap      #13
	addq.l    #2,sp
	rts

    	.public Getbpb
Getbpb:
	move.w    d0,-(sp)
	move.w    #7,-(sp)
	trap      #13
	addq.l    #4,sp
	rts

       	.public Bcostat
Bcostat:
	move.w    d0,-(sp)
	move.w    #8,-(sp)
	trap      #13
	addq.l    #4,sp
	rts

        .public Mediach
Mediach:
	move.w    d0,-(sp)
	move.w    #9,-(sp)
	trap      #13
	addq.l    #4,sp
	rts

        .public Drvmap
Drvmap:
	move.w    #10,-(sp)
	trap      #13
	addq.l    #2,sp
	rts

