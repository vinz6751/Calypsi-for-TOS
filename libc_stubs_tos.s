// See Calypsi doc
	.public _Stub_putchar
_Stub_putchar:
	move.w	  d0,-(sp)
	move.w	  #2,-(sp)	; Cconout
	trap	  #1
	addq.l	  #4,sp
	rts

	.public _Stub_puts
_Stub_puts:
	move.l	 a0,-(sp)
	move.w	 #9,-(sp)	; Cconws
	trap	 #1
	addq.l	 #6,sp
	rts ; We're not setting the return value. Anybody cares ?


	//int _Stub_raise(int signo);

	.public _Stub_open
_Stub_open: 
	move.w	  d0,-(sp)
	move.l	  a0,-(sp)
	move.w	  #61,-(sp)	; Fopen
	trap	  #1
	addq.l	  #8,sp
	rts

	.public _Stub_close
_Stub_close:
	move.w	  d0,-(sp)
	move.w	  #62,-(sp)	; Fclose
	trap	  #1
	addq.l	  #4,sp
	rts

// int _Stub_fcntl(int fd, int command, ...);
// int _Stub_access(const char *path, int mode);

	.public _Stub_lseek
_Stub_lseek:
	move.l	  4(sp),-(sp)
	move.w	  d0,-(sp)
	move.w	  d1,-(sp)
	move.w	  #66,-(sp) ; Fseek
	trap	  #1
	lea	  10(sp),sp
	rts

	.public _Stub_fsetpos
_Stub_fsetpos:
	move.l	  4(sp),-(sp)
	move.w	  d0,-(sp)
	move.w	  #0,-(sp)	; SEEK_SET
	move.w	  #66,-(sp)	; Fseek
	trap	  #1
	lea	  10(sp),sp
	rts

	.public _Stub_read
_Stub_read: 
	move.l	  a0,-(sp)
	move.l	  d1,-(sp)
	move.w	  d0,-(sp)
	move.w	  #63,-(sp)	; Fread
	trap	  #1
	lea	  0xC(sp),sp
	rts

	.public _Stub_write
_Stub_write: 
	move.l	  a0,-(sp)
	move.l	  d1,-(sp)
	move.w	  d0,-(sp)
	move.w	  #64,-(sp)	; Fwrite
	trap	  #1
	lea	  0xC(sp),sp
	rts

	.public _Stub_rename
_Stub_rename:
	move.l	a0,-(sp)
	move.l	a1,-(sp)
	move.w	#0,-(sp)
	move.w	#86,-(sp)
	trap	#1		; Frename
	lea	0xC(sp),sp
	rts

	.public _Stub_remove
_Stub_remove:
	move.l	a0,-(sp)
	move.w	#65,-(sp)
	trap	#1	     ; Fdelete
	addq.l	#6,sp
	rts

	.public _Stub_environ
	.extern __env
_Stub_environ:
	move.l	__env,d0
	rts

/****************************************************************************
 * Name: _Stub_assert
 *
 * Description:
 *   Handle an assertion
 *
 ****************************************************************************/

//#ifdef _CONFIG_HAVE_FILENAME
//void _Stub_assert(const char *filename, int linenum) __noreturn_function;
//#else
//void _Stub_assert() __noreturn_function;
///#endif
