#include <stdint.h>
#include "tos.h"

void Getmpb(MPB *mpb) {
	int16_t out;
	__asm(" move.l %[mpb],-(sp)\n"
	  " move.w #0,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out) // Unused
	  : [mpb] "Kxreg32" (mpb)
	  : TOS_CLOBBERED_REGS);
}

int16_t Bconstat(int16_t dev) {
	int16_t result;
	__asm(" move.w %[dev],-(sp)\n"
	  " move.w #1,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #4,sp\n"
	  : [result] "=Kd0w" (result)
	  : [dev] "Kdreg16" (dev)
	  : TOS_CLOBBERED_REGS);
	return result;
}

int32_t Bconin(int16_t dev) {
	int32_t result;
	__asm(" move.w %[dev],-(sp)\n"
	  " move.w #2,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #4,sp\n"
	  : [result] "=Kd0" (result)
	  : [dev] "Kdreg16" (dev)
	  : TOS_CLOBBERED_REGS);
	return result;
}

void Bconout(int16_t dev, int16_t c) {
	int16_t result;
	__asm(" move.w %[c],-(sp)\n"
	  " move.w %[dev],-(sp)\n"
	  " move.w #3,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #6,sp\n"
	  : [result] "=Kd0w" (result) // Unused
	  : [dev] "Kdreg16" (dev), [c] "Kdreg16" (c)
	  : TOS_CLOBBERED_REGS);
}

int32_t Rwabs(int16_t rwflag, void *buff, int16_t cnt, int16_t recnr, int16_t dev, int32_t lrecno) {
	int32_t result;
	__asm(" move.l %[lrecno],-(sp)\n"
	  " move.w %[dev],-(sp)\n"
	  " move.w %[recnr],-(sp)\n"
	  " move.w %[cnt],-(sp)\n"
	  " move.l %[buff],-(sp)\n"
	  " move.l %[rwflag],-(sp)\n"
	  " move.w #4,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #6,sp\n"
	  : [result] "=Kd0" (result)
	  : [rwflag] "Kxreg16" (rwflag), [buff] "Kxreg32" (buff), [cnt] "Kxreg16" (cnt), [recnr] "Kxreg16" (recnr), [dev] "Kxreg16" (dev), [lrecno] "Kdreg32" (lrecno)
	  : TOS_CLOBBERED_REGS);
	return result;
}

_cpu_irq_handler_t Setexc(int16_t number, _cpu_irq_handler_t vector) {
	void (*result)(void);
	__asm(" move.l %[vector],-(sp)\n"
	  " move.w %[number],-(sp)\n"
	  " move.w #5,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #8,sp\n"
	  : [result] "=Kd0" (result)
	  : [number] "Kdreg16" (number), [vector] "Kxreg32" (vector)
	  : TOS_CLOBBERED_REGS);
	return result;
}

int32_t Tickcal(void) {
	int32_t result;
	__asm(" move.w #6,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #2,sp\n"
	  : [result] "=Kd0" (result)
	  :
	  : TOS_CLOBBERED_REGS);
	return result;
}

BPB *Getbpb(int16_t dev) {
	BPB *result;
	__asm(" move.w %[dev],-(sp)\n"
	  " move.w #7,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #4,sp\n"
	  : [result] "=Kd0" (result)
	  : [dev] "Kdreg16" (dev)
	  : TOS_CLOBBERED_REGS);
	return result;
}

int32_t Bcostat(int16_t dev) {
	int32_t result;
	__asm(" move.w %[dev],-(sp)\n"
	  " move.w #8,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #4,sp\n"
	  : [result] "=Kd0" (result)
	  : [dev] "Kdreg16" (dev)
	  : TOS_CLOBBERED_REGS);
	return result;
}

int32_t Mediach(int16_t dev) {
	int32_t result;
	__asm(" move.w %[dev],-(sp)\n"
	  " move.w #9,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #4,sp\n"
	  : [result] "=Kd0" (result)
	  : [dev] "Kdreg16" (dev)
	  : TOS_CLOBBERED_REGS);
	return result;
}

int32_t Drvmap(void) {
	int32_t result;
	__asm(" move.w #10,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #2,sp\n"
	  : [result] "=Kd0" (result)
	  :
	  : TOS_CLOBBERED_REGS);
	return result;
}

int32_t Kbshift(int16_t mode) {
	int32_t result;
	__asm(" move.w %[mode],-(sp)\n"
	  " move.w #11,-(sp)\n"
	  " trap   #13\n"
	  " addq.l #2,sp\n"
	  : [result] "=Kd0" (result)
	  : [mode] "Kdreg16" (mode)
	  : TOS_CLOBBERED_REGS);
	return result;
}
