#include <stdint.h>
#include "tos.h"

void Initmouse(int16_t type, MOUSE *par, void (*mousevec)()) {
	int16_t out;
	__asm(" move.l %[mousevec],-(sp)\n"
	  " move.l %[par],-(sp)\n"
	  " move.w %[type],-(sp)\n"
	  " move.w #0,-(sp)\n"
	  " trap   #14\n"
	  " lea	   12(sp),sp\n"
	  : "=Kd0w" (out) // Unused
	  : [mousevec] "Kxreg32" (mousevec), [par] "Kxreg32" (par), [type] "Kdreg16" (type)
	  : "d0","d1","d2","a0","a1","a2");
}

void *Ssbrk(int16_t count) {
	void *out;
	__asm(" move.w %[count],-(sp)\n"
	  " move.w #1,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #4,sp\n"
	  : "=Kd0" (out)
	  : [count] "Kdreg16" (count)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void *Physbase(void) {
	void *out;
	__asm(" move.w #2,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Getrez(void) {
	int16_t out;
	__asm(" move.w #4,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void Setscreen(void *laddr, void *paddr, int16_t rez) {
	int16_t out;
	__asm(" move.w %[rez],-(sp)\n"
	  " move.l %[paddr],-(sp)\n"
	  " move.l %[laddr],-(sp)\n"
	  " move.w #5,-(sp)\n"
	  " trap   #14\n"
	  " lea	   12(sp),sp\n"
	  : "=Kd0w" (out) // Unused
	  : [laddr] "Kxreg32" (laddr), [paddr] "Kxreg32" (paddr), [rez] "Kdreg16" (rez)
	  : "d0","d1","d2","a0","a1","a2");
}


void VsetScreen(void *laddr, void *paddr, int16_t rez, int16_t mode) {
	int16_t out;
	__asm(" move.w %[mode],-(sp)\n"
	  " move.w %[rez],-(sp)\n"
	  " move.l %[paddr],-(sp)\n"
	  " move.l %[laddr],-(sp)\n"
	  " move.w #5,-(sp)\n"
	  " trap   #14\n"
	  " lea	   12(sp),sp\n"
	  : "=Kd0w" (out) // Unused
	  : [laddr] "Kxreg32" (laddr), [paddr] "Kxreg32" (paddr), [rez] "Kdreg16" (rez), [mode] "Kdreg16" (mode)
	  : "d0","d1","d2","a0","a1","a2");
}

void Setpalette(void *pallptr) {
	int16_t out;
	__asm(" move.l %[pallptr],-(sp)\n"
	  " move.w #6,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out) // Unused
	  : [pallptr] "Kxreg32" (pallptr)
	  : "d0","d1","d2","a0","a1","a2");
}

int16_t Setcolor(int16_t colornum, int16_t color) {
	int16_t out;
	__asm(" move.w %[color],-(sp)\n"
	  " move.w %[colornum],-(sp)\n"
	  " move.w #7,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out)
	  : [colornum] "Kdreg16" (colornum), [color] "Kdreg16" (color)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Floprd(void *buf, int32_t filler, int16_t devno, int16_t sectno, int16_t trackno, int16_t sideno, int16_t count) {
	int16_t out;
	__asm(" move.w %[count],-(sp)\n"
	  " move.w %[sideno],-(sp)\n"
	  " move.w %[trackno],-(sp)\n"
	  " move.w %[sectno],-(sp)\n"
	  " move.w %[devno],-(sp)\n"
	  " move.l %[filler],-(sp)\n"
	  " move.l %[buf],-(sp)\n"
	  " move.w #8,-(sp)\n"
	  " trap   #14\n"
	  " lea	   14(sp),sp\n"
	  : "=Kd0w" (out)
	  : [buf] "Kxreg32" (buf), [filler] "Kxreg32" (filler), [devno] "Kdreg16" (devno), [sectno] "Kdreg16" (sectno), [trackno] "Kdreg16" (trackno), [sideno] "Kdreg16" (sideno), [count] "Kdreg16" (count)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Flopwr(void *buf, int32_t filler, int16_t devno, int16_t sectno, int16_t trackno, int16_t sideno, int16_t count) {
	int16_t out;
	__asm(" move.w %[count],-(sp)\n"
	  " move.w %[sideno],-(sp)\n"
	  " move.w %[trackno],-(sp)\n"
	  " move.w %[sectno],-(sp)\n"
	  " move.w %[devno],-(sp)\n"
	  " move.l %[filler],-(sp)\n"
	  " move.l %[buf],-(sp)\n"
	  " move.w #9,-(sp)\n"
	  " trap   #14\n"
	  " lea	   14(sp),sp\n"
	  : "=Kd0w" (out)
	  : [buf] "Kxreg32" (buf), [filler] "Kxreg32" (filler), [devno] "Kdreg16" (devno), [sectno] "Kdreg16" (sectno), [trackno] "Kdreg16" (trackno), [sideno] "Kdreg16" (sideno), [count] "Kdreg16" (count)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Flopfmt(void *buf, int32_t filler, int16_t devno, int16_t spt, int16_t trackno, int16_t sideno, int16_t interlv, int32_t magic, int16_t virgin) {
	int16_t out;
	__asm(" move.w %[virgin],-(sp)\n"
	  " move.w %[magic],-(sp)\n"
	  " move.w %[interlv],-(sp)\n"
	  " move.w %[sideno],-(sp)\n"
	  " move.w %[trackno],-(sp)\n"
	  " move.w %[spt],-(sp)\n"
	  " move.w %[devno],-(sp)\n"
	  " move.l %[filler],-(sp)\n"
	  " move.l %[buf],-(sp)\n"
	  " move.w #10,-(sp)\n"
	  " trap   #14\n"
	  " lea	   16(sp),sp\n"
	  : "=Kd0w" (out)
	  : [buf] "Kxreg32" (buf), [filler] "Kxreg32" (filler), [devno] "Kdreg16" (devno), [spt] "Kdreg16" (spt), [trackno] "Kdreg16" (trackno), [sideno] "Kdreg16" (sideno), [interlv] "Kdreg16" (interlv), [magic] "Kdreg32" (magic), [virgin] "Kdreg16" (virgin)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void Dbmsg(int16_t rsrvd, int16_t msg_num, int32_t msg_arg) {
	int16_t out;
	__asm(" move.l %[msg_arg],-(sp)\n"
	  " move.w %[msg_num],-(sp)\n"
	  " move.w %[rsrvd],-(sp)\n"
	  " move.w #11,-(sp)\n"
	  " trap   #14\n"
	  " lea	   10(sp),sp\n"
	  : "=Kd0w" (out) // Unused
	  : [rsrvd] "Kdreg16" (rsrvd), [msg_num] "Kdreg16" (msg_num), [msg_arg] "Kxreg32" (msg_arg)
	  : "d0","d1","d2","a0","a1","a2");
}

void Midiws(int16_t cnt, void *ptr) {
	int16_t out;
	__asm(" move.l %[ptr],-(sp)\n"
	  " move.w %[cnt],-(sp)\n"
	  " move.w #12,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #8,sp\n"
	  : "=Kd0w" (out) // Unused
	  : [cnt] "Kdreg16" (cnt), [ptr] "Kxreg32" (ptr)
	  : "d0","d1","d2","a0","a1","a2");
}


void Mfpint(int16_t number, int16_t (*vector)(void)) {
	int16_t out;
	__asm(" move.l %[vector],-(sp)\n"
	  " move.w %[number],-(sp)\n"
	  " move.w #13,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #8,sp\n"
	  : "=Kd0w" (out) // Unused
	  : [number] "Kdreg16" (number), [vector] "Kxreg32" (vector)
	  : "d0","d1","d2","a0","a1","a2");
}

IOREC *Iorec(int16_t dev) {
	IOREC *out;
	__asm(" move.w %[dev],-(sp)\n"
	  " move.w #14,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #4,sp\n"
	  : "=Kd0" (out) // Unused
	  : [dev] "Kdreg16" (dev)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Rsconf(int16_t baud, int16_t ctr, int16_t ucr, int16_t rsr, int16_t tsr, int16_t scr) {
	int32_t out;
	__asm(" move.w %[scr],-(sp)\n"
	  " move.w %[tsr],-(sp)\n"
	  " move.w %[rsr],-(sp)\n"
	  " move.w %[ucr],-(sp)\n"
	  " move.w %[ctr],-(sp)\n"
	  " move.w %[baud],-(sp)\n"
	  " move.w #15,-(sp)\n"
	  " trap   #14\n"
	  " lea	   14(sp),sp\n"
	  : "=Kd0" (out)
	  : [baud] "Kdreg16" (baud), [ctr] "Kdreg16" (ctr), [ucr] "Kdreg16" (ucr), [rsr] "Kdreg16" (rsr), [tsr] "Kdreg16" (tsr), [scr] "Kdreg16" (scr)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

KEYTAB *Keytbl(void *unshift, void *shift, void *capslock) {
	KEYTAB *out;
	__asm(" move.l %[capslock],-(sp)\n"
	  " move.l %[shift],-(sp)\n"
	  " move.l %[unshift],-(sp)\n"
	  " move.w #16,-(sp)\n"
	  " trap   #14\n"
	  " lea	   14(sp),sp\n"
	  : "=Kd0" (out)
	  : [unshift] "Kxreg32" (unshift), [shift] "Kxreg32" (shift), [capslock] "Kxreg32" (capslock)
	  : "d0","d1","d2","a0","a1","a2");
	return out;

}

int32_t Random(void) {
   int32_t out;
   __asm( " move.w #16,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  : 
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void Protobt(void *buf, int32_t serialno, int16_t disktype, int16_t execflag) {
	uint32_t out;
	__asm(" move.w %[execflag],-(sp)\n"
	  " move.w %[disktype],-(sp)\n"
	  " move.l %[serialno],-(sp)\n"
	  " move.l %[buf],-(sp)\n"
	  " move.w #18,-(sp)\n"
	  " trap   #14\n"
	  " lea	   14(sp),sp\n"
	  : "=Kd0" (out)
	  : [buf] "Kxreg32" (buf), [serialno] "Kxreg32" (serialno), [disktype] "Kdreg16" (disktype), [execflag] "Kdreg16" (execflag)
	  : "d0","d1","d2","a0","a1","a2");
}

int16_t Flopver(void *buf, int32_t filler, int16_t devno, int16_t sectno, int16_t trackno, int16_t sideno, int16_t count) {
	int16_t out;
	__asm(" move.w %[count],-(sp)\n"
	  " move.w %[sideno],-(sp)\n"
	  " move.w %[trackno],-(sp)\n"
	  " move.w %[sectno],-(sp)\n"
	  " move.w %[devno],-(sp)\n"
	  " move.l %[filler],-(sp)\n"
	  " move.l %[buf],-(sp)\n"
	  " move.w #19,-(sp)\n"
	  " trap   #14\n"
	  " lea	   20(sp),sp\n"
	  : "=Kd0w" (out)
	  : [buf] "Kxreg32" (buf), [filler] "Kxreg32" (filler), [devno] "Kdreg16" (devno), [sectno] "Kdreg16" (sectno), [trackno] "Kdreg16" (trackno), [sideno] "Kdreg16" (sideno), [count] "Kdreg16" (count)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void Scrdmp(void) {
  int16_t out;
   __asm( " move.w #20,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out) // Unused
	  : 
	  : "d0","d1","d2","a0","a1","a2");
}

int16_t Cursconf(int16_t func, int16_t rate) {
	int16_t out;
	__asm(" move.w %[rate],-(sp)\n"
	  " move.w %[func],-(sp)\n"
	  " move.w #21,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out)
	  : [rate] "Kdreg16" (rate), [func] "Kdreg16" (func)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void Settime(uint32_t time) {
	int16_t out;
	__asm(" move.l %[time],-(sp)\n"
	  " move.w #22,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out) // Unused
	  : [time] "Kxreg32" (time)
	  : "d0","d1","d2","a0","a1","a2");
}

uint32_t Gettime(void) {
	int32_t out;
	__asm(" move.w #23,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void Bioskeys(void) {
	int32_t out;
	__asm(" move.w #24,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out) // Unused
	  :
	  : "d0","d1","d2","a0","a1","a2");
}

void Ikbdws(int16_t count, const int8_t *ptr) {
	int16_t out;
	__asm(" move.l %[ptr],-(sp)\n"
	  " move.w %[count],-(sp)\n"
	  " move.w #25,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #8,sp\n"
	  : "=Kd0w" (out) // Unused
	  : [count] "Kdreg16" (count), [ptr] "Kxreg32" (ptr)
	  : "d0","d1","d2","a0","a1","a2");
}

void Jdisint(int16_t number) {
	int16_t out;
	__asm(" move.w %[number],-(sp)\n"
	  " move.w #26,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #4,sp\n"
	  : "=Kd0w" (out) // Unused
	  : [number] "Kdreg16" (number)
	  : "d0","d1","d2","a0","a1","a2");
}

void Jenabint(int16_t number) {
	int16_t out;
	__asm(" move.w %[number],-(sp)\n"
	  " move.w #27,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #4,sp\n"
	  : "=Kd0w" (out) // Unused
	  : [number] "Kdreg16" (number)
	  : "d0","d1","d2","a0","a1","a2");
}

int8_t Giaccess(int16_t data, int16_t regno) {
	int16_t out;
	__asm(" move.w %[regno],-(sp)\n"
	  " move.w %[data],-(sp)\n"
	  " move.w #28,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out)
	  : [data] "Kdreg16" (data), [regno] "Kdreg16" (regno)
	  : "d0","d1","d2","a0","a1","a2");
	return (int8_t)out; // There seem to be a problem with the "=Kd0b" constraint" in Calypsi 5.1, it's reported to Hakan.
}

void Offgibit(int16_t bitno) {
	int16_t out;
	__asm(" move.w %[bitno],-(sp)\n"
	  " move.w #29,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #4,sp\n"
	  : "=Kd0w" (out) // Unused
	  : [bitno] "Kdreg16" (bitno)
	  : "d0","d1","d2","a0","a1","a2");
}

void Ongibit(int16_t bitno) {
	int16_t out;
	__asm(" move.w %[bitno],-(sp)\n"
	  " move.w #30,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #4,sp\n"
	  : "=Kd0w" (out) // Unused
	  : [bitno] "Kdreg16" (bitno)
	  : "d0","d1","d2","a0","a1","a2");
}

void Xbtimer(int16_t timer, int16_t control, int16_t data, void(*vector)(void)) {
	int16_t out;
	__asm(" move.l %[vector],-(sp)\n"
	  " move.w %[data],-(sp)\n"
	  " move.w %[control],-(sp)\n"
	  " move.w %[timer],-(sp)\n"
	  " move.w #31,-(sp)\n"
	  " trap   #14\n"
	  " lea	   12(sp),sp\n"
	  : "=Kd0w" (out) // Unused
	  : [timer] "Kxreg16" (timer), [control] "Kxreg16" (control), [data] "Kxreg16" (data), [vector] "Kxreg32" (vector)
	  : "d0","d1","d2","a0","a1","a2");
}

void *Dosound(const int8_t *buf) {
	void *out;
	__asm(" move.l %[buf],-(sp)\n"
	  " move.w #32,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [buf] "Kxreg32" (buf)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Setprt(int16_t config) {
	int16_t out;
	__asm(" move.w %[config],-(sp)\n"
	  " move.w #33,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #4,sp\n"
	  : "=Kd0w" (out)
	  : [config] "Kxreg16" (config)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

KBDVBASE *Kbdvbase(void) {
	KBDVBASE *out;
	__asm( " move.w #34,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}


int16_t Kbrate(int16_t initial, int16_t repeat) {
	int16_t out;
	__asm(" move.w %[repeat],-(sp)\n"
	  " move.w %[initial],-(sp)\n"
	  " move.w #35,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out)
	  : [initial] "Kxreg16" (initial), [repeat] "Kxreg16" (repeat)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Prtblk(PBDEF *par) {
	int16_t out;
	__asm(" move.l %[par],-(sp)\n"
	  " move.w #36,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out)
	  : [par] "Kxreg32" (par)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void Vsync(void) {
	int16_t out;
	__asm(" move.w #37,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out) // Unused
	  :
	  : "d0","d1","d2","a0","a1","a2");
}

int32_t Supexec(int32_t (*func)(void)) {
	int32_t out;
	__asm(" move.l %[func],-(sp)\n"
	  " move.w #38,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [func] "Kxreg32" (func)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void Puntaes(void) {
	int16_t out;
	__asm(" move.w #39,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out) // Unused
	  :
	  : "d0","d1","d2","a0","a1","a2");
}

int16_t Floprate(int16_t devno, int16_t newrate) {
	int16_t out;
	__asm(" move.w %[newrate],-(sp)\n"
	  " move.w %[devno],-(sp)\n"
	  " move.w #41,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out)
	  : [devno] "Kxreg16" (devno), [newrate] "Kxreg16" (newrate)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t DMAread(int32_t sector, int16_t count, void *buffer, int16_t devno) {
	int16_t out;
	__asm(" move.w %[devno],-(sp)\n"
	  " move.l %[buffer],-(sp)\n"
	  " move.w %[count],-(sp)\n"
	  " move.l %[sector],-(sp)\n"
	  " move.w #42,-(sp)\n"
	  " trap   #14\n"
	  " lea	   15(sp),sp\n"
	  : "=Kd0w" (out)
	  : [sector] "Kxreg32" (sector), [count] "Kxreg16" (count), [buffer] "Kxreg32" (buffer), [devno] "Kxreg16" (devno)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t DMAwrite(int32_t sector, int16_t count, void *buffer, int16_t devno) {
	int16_t out;
	__asm(" move.w %[devno],-(sp)\n"
	  " move.l %[buffer],-(sp)\n"
	  " move.w %[count],-(sp)\n"
	  " move.l %[sector],-(sp)\n"
	  " move.w #43,-(sp)\n"
	  " trap   #14\n"
	  " lea	   15(sp),sp\n"
	  : "=Kd0w" (out)
	  : [sector] "Kxreg32" (sector), [count] "Kxreg16" (count), [buffer] "Kxreg32" (buffer), [devno] "Kxreg16" (devno)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Bconmap(int16_t devno) {
	int32_t out;
	__asm(" move.w %[devno],-(sp)\n"
	  " move.w #44,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #4,sp\n"
	  : "=Kd0" (out)
	  : [devno] "Kxreg16" (devno)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Blitmode(int16_t mode) {
	int16_t out;
	__asm(" move.w %[mode],-(sp)\n"
	  " move.w #45,-(sp)\n"
	  " trap   #14\n"
	  " addq.l #4,sp\n"
	  : "=Kd0w" (out)
	  : [mode] "Kxreg16" (mode)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

