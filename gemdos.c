/* TOS (BIOS/XBIOS/GEMDOS) for Calypsi 68k
 * Vinz/MPS
 */

#include "tos.h"

void Pterm0(void) {
	int16_t out;
	__asm(" clr.w  -(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out)
	  : 
	  : "d0","d1","d2","a0","a1","a2");
}

int32_t Cconin(void) {
	int32_t out;
	__asm(" move.w #1,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  : 
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Cconout(int16_t c) {
	int32_t out;
	__asm(" move.w %[c],-(sp)\n"
	  " move.w #2,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #4,sp\n"
	  : "=Kd0" (out)
	  : [c] "Kxreg16" (c)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Cauxin(void) {
	int32_t out;
	__asm(" move.w #3,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Cauxout(int16_t c) {
	int32_t out;
	__asm(" move.w %[c],-(sp)\n"
	  " move.w #4,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #4,sp\n"
	  : "=Kd0" (out)
	  : [c] "Kxreg16" (c)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Cprnout(int16_t c) {
	int32_t out;
	__asm(" move.w %[c],-(sp)\n"
	  " move.w #5,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #4,sp\n"
	  : "=Kd0" (out)
	  : [c] "Kxreg16" (c)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Crawio(int16_t w) {
	int32_t out;
	__asm(" move.w %[w],-(sp)\n"
	  " move.w #6,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #4,sp\n"
	  : "=Kd0" (out)
	  : [w] "Kxreg16" (w)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Crawcin(void) {
	int32_t out;
	__asm(" move.w #7,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  : 
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Cnecin(void) {
	int32_t out;
	__asm(" move.w #8,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  : 
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Cconws(const char *buf) {
	int32_t out;
	__asm(" move.l %[buf],-(sp)\n"
	  " move.w #9,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [buf] "Kxreg32" (buf)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Cconrs(LINE *buf) {
	int32_t out;
	__asm(" move.l %[buf],-(sp)\n"
	  " move.w #10,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [buf] "Kxreg32" (buf)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Cconis(void) {
	int32_t out;
	__asm(" move.w #11,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  : 
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Dsetdrv(int16_t drv) {
	int32_t out;
	__asm(" move.w %[drv],-(sp)\n"
	  " move.w #15,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [drv] "Kxreg16" (drv)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Cconos(void) {
	int16_t out;
	__asm( " move.w #16,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Cprnos(void) {
	int16_t out;
	__asm(" move.w #17,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Cauxis(void) {
	int16_t out;
	__asm(" move.w #18,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Cauxos(void) {
	int16_t out;
	__asm(" move.w #19,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Maddalt (void *start, int32_t size) {
	int32_t out;
	__asm(" move.l %[size],-(sp)\n"
	  " move.l %[start],-(sp)\n"
	  " move.w #20,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #8,sp\n"
	  : "=Kd0" (out)
	  : [start] "Kxreg32" (start), [size] "Kxreg32" (size)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Srealloc(int32_t len) {
	int32_t out;
	__asm(" move.l %[len],-(sp)\n"
	  " move.w #21,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [len] "Kxreg32" (len)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Dgetdrv(void) {
	int16_t out;
	__asm(" move.w #25,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void Fsetdta(DTA *buf) {
	int32_t out;
	__asm(" move.l %[buf],-(sp)\n"
	  " move.w #26,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out) // ignored
	  : [buf] "Kxreg32" (buf)
	  : "d0","d1","d2","a0","a1","a2");
}

int32_t Super(void *stack) {
	int32_t out;
	__asm(" move.l %[stack],-(sp)\n"
	  " move.w #32,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [stack] "Kxreg32" (stack)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

uint32_t Tgetdate(void) {
	int32_t out;
	__asm(" move.w #42,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Tsetdate(uint16_t date) {
	int16_t out;
	__asm(" move.w %[date],-(sp)\n"
	  " move.w #43,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #4,sp\n"
	  : "=Kd0w" (out)
	  : [date] "Kxreg16" (date)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

uint32_t Tgettime(void) {
	int32_t out;
	__asm(" move.w #44,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Tsettime(uint16_t time) {
	int16_t out;
	__asm(" move.w %[time],-(sp)\n"
	  " move.w #45,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #4,sp\n"
	  : "=Kd0w" (out)
	  : [time] "Kxreg16" (time)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

DTA *Fgetdta(void) {
	DTA *out;
	__asm(" move.w #47,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

uint16_t Sversion(void) {
	uint16_t out;
	__asm(" move.w #48,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void Ptermres(int32_t keepcnt, int16_t retcode) {
	uint16_t out;
	__asm(" move.w %[retcode],-(sp)\n"
	  " move.l %[keepcnt],-(sp)\n"
	  " move.w #49,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out) // Unused
	  : [keepcnt] "Kxreg32" (keepcnt), [retcode] "Kxreg16" (retcode)
	  : "d0","d1","d2","a0","a1","a2");
}

int16_t Dfree(DISKINFO *buf, int16_t driveno) {
	uint16_t out;
	__asm(" move.w %[driveno],-(sp)\n"
	  " move.l %[buf],-(sp)\n"
	  " move.w #54,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #8,sp\n"
	  : "=Kd0w" (out)
	  : [buf] "Kxreg32" (buf), [driveno] "Kxreg16" (driveno)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Dcreate(const char *path) {
	uint32_t out;
	__asm(" move.l %[path],-(sp)\n"
	  " move.w #57,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [path] "Kxreg32" (path)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Ddelete(const char *path) {
	uint32_t out;
	__asm(" move.l %[path],-(sp)\n"
	  " move.w #58,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [path] "Kxreg32" (path)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Dsetpath(const char *path) {
	uint16_t out;
	__asm(" move.l %[path],-(sp)\n"
	  " move.w #59,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out)
	  : [path] "Kxreg32" (path)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Fcreate(const char *fname, int16_t attr) {
	uint16_t out;
	__asm(" move.w %[attr],-(sp)\n"
	  " move.l %[fname],-(sp)\n"
	  " move.w #60,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #8,sp\n"
	  : "=Kd0w" (out)
	  : [fname] "Kxreg32" (fname), [attr] "Kxreg16" (attr)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Fopen(const char *fname, int16_t mode) {
	uint32_t out;
	__asm(" move.w %[mode],-(sp)\n"
	  " move.l %[fname],-(sp)\n"
	  " move.w #61,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #8,sp\n"
	  : "=Kd0" (out)
	  : [fname] "Kxreg32" (fname), [mode] "Kxreg16" (mode)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Fclose(int16_t handle) {
	uint16_t out;
	__asm(" move.w %[handle],-(sp)\n"
	  " move.w #62,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #4,sp\n"
	  : "=Kd0w" (out)
	  : [handle] "Kxreg16" (handle)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Fread(int16_t handle, int32_t count, void *buf) {
	uint32_t out;
	__asm(" move.l %[buf],-(sp)\n"
	  " move.l %[count],-(sp)\n"
	  " move.w %[handle],-(sp)\n"
	  " move.w #63,-(sp)\n"
	  " trap   #1\n"
	  " lea	   12(sp),sp\n"
	  : "=Kd0" (out)
	  : [handle] "Kxreg16" (handle), [count] "Kxreg32" (count), [buf] "Kxreg32" (buf)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Fwrite(int16_t handle, int32_t count, void *buf) {
	uint32_t out;
	__asm(" move.l %[buf],-(sp)\n"
	  " move.l %[count],-(sp)\n"
	  " move.w %[handle],-(sp)\n"
	  " move.w #64,-(sp)\n"
	  " trap   #1\n"
	  " lea	   12(sp),sp\n"
	  : "=Kd0" (out)
	  : [handle] "Kxreg16" (handle), [count] "Kxreg32" (count), [buf] "Kxreg32" (buf)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Fdelete(const char *fname) {
	uint16_t out;
	__asm(" move.l %[fname],-(sp)\n"
	  " move.w #65,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out)
	  : [fname] "Kxreg32" (fname)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Fseek(int32_t offset, int16_t handle, int16_t seekmode) {
	uint32_t out;
	__asm(" move.w %[seekmode],-(sp)\n"
	  " move.w %[handle],-(sp)\n"
	  " move.l %[offset],-(sp)\n"
	  " move.w #66,-(sp)\n"
	  " trap   #1\n"
	  " lea.l  10(sp),sp\n"
	  : "=Kd0" (out)
	  : [offset] "Kxreg32" (offset), [handle] "Kxreg16" (handle), [seekmode] "Kxreg16" (seekmode)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Fattrib(const char *filename, int16_t wflag, int16_t attrib) {
	uint16_t out;
	__asm(" move.l %[filename],-(sp)\n"
	  " move.w %[wflag],-(sp)\n"
	  " move.w %[attrib],-(sp)\n"
	  " move.w #67,-(sp)\n"
	  " trap   #1\n"
	  " lea.l  10(sp),sp\n"
	  : "=Kd0w" (out)
	  : [filename] "Kxreg32" (filename), [wflag] "Kxreg16" (wflag), [attrib] "Kxreg16" (attrib)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void *Mxalloc(int32_t amount, int16_t mode) {
	void *out;
	__asm(" move.w %[mode],-(sp)\n"
	  " move.l %[amount],-(sp)\n"
	  " move.w #68,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #8,sp\n"
	  : "=Kd0" (out)
	  : [amount] "Kxreg32" (amount), [mode] "Kxreg16" (mode)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Fdup(int16_t handle) {
	int16_t out;
	__asm(" move.w %[handle],-(sp)\n"
	  " move.w #69,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #4,sp\n"
	  : "=Kd0w" (out)
	  : [handle] "Kxreg16" (handle)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Fforce(int16_t stdh, int16_t nonstdh) {
	int16_t out;
	__asm(" move.w %[nonstdh],-(sp)\n"
	  " move.w %[stdh],-(sp)\n"
	  " move.w #70,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0w" (out)
	  : [stdh] "Kxreg16" (stdh), [nonstdh] "Kxreg16" (nonstdh)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int16_t Dgetpath(const char *path, int16_t driveno) {
	int16_t out;
	__asm(" move.w %[driveno],-(sp)\n"
	  " move.l %[path],-(sp)\n"
	  " move.w #71,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #8,sp\n"
	  : "=Kd0w" (out)
	  : [path] "Kxreg32" (path), [driveno] "Kxreg16" (driveno)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

void *Malloc(int32_t number) {
	void *out;
	__asm(" move.l %[number],-(sp)\n"
	  " move.w #72,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [number] "Kxreg32" (number)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Mfree(void *block) {
	int32_t out;
	__asm(" move.l %[block],-(sp)\n"
	  " move.w #73,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [block] "Kxreg32" (block)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t Mshrink(void *block, int32_t newsiz) {
	int32_t out;
	__asm(" move.l %[newsiz],-(sp)\n"
	  " move.l %[block],-(sp)\n"
	  " move.w #74,-(sp)\n"
	  " trap   #1\n"
	  " lea.l  10(sp),sp\n"
	  : "=Kd0" (out)
	  : [block] "Kxreg32" (block), [newsiz] "Kxreg32" (newsiz)
	  : "d0","d1","d2","a0","a1","a2");
	return out;
}

int32_t CDECL Pexec(uint16_t mode, ...) {
	// This one is a bit special because it has variable arguments.
	// So we use the C calling convention (args on the stack) and just repush
	// everything
	int32_t out;
	__asm(" move.l sp,a0\n"
	  " move.l 14(a0),-(sp)\n"
	  " move.l 10(a0),-(sp)\n"
	  " move.l 6(a0),-(sp)\n"
	  " move.w 4(a0),-(sp)\n"
	  " move.w #75,-(sp)\n"
	  " trap   #1\n"
	  " lea.l  16(sp),sp\n"
	  : "=Kd0" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
	return out;

}

void Pterm (uint16_t retcode) {
	int32_t out;
	__asm(" move.w %[retcode],-(sp)\n"
	  " move.w #76,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #4,sp\n"
	  : "=Kd0" (out)
	  : [retcode] "Kxreg16" (retcode)
	  : "d0","d1","d2","a0","a1","a2");
}

int32_t Fsfirst(const char *filename, int16_t attr) {
	int32_t out;
	__asm(" move.w %[attr],-(sp)\n"
	  " move.l %[filename],-(sp)\n"
	  " move.w #78,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #6,sp\n"
	  : "=Kd0" (out)
	  : [filename] "Kxreg32" (filename), [attr] "Kxreg16" (attr)
	  : "d0","d1","d2","a0","a1","a2");
   return out;
}

int16_t Fsnext(void) {
	int16_t out;
	__asm(" move.w #79,-(sp)\n"
	  " trap   #1\n"
	  " addq.l #2,sp\n"
	  : "=Kd0w" (out)
	  :
	  : "d0","d1","d2","a0","a1","a2");
   return out;
}

int32_t Frename(const char *oldname, const int8_t *newname) {
	int32_t out;
	__asm(" move.l %[newname],-(sp)\n"
	  " move.l %[oldname],-(sp)\n"
	  " move.w #86,-(sp)\n"
	  " trap   #1\n"
	  " lea.l  10(sp),sp\n"
	  : "=Kd0" (out)
	  : [oldname] "Kxreg32" (oldname), [newname] "Kxreg32" (newname)
	  : "d0","d1","d2","a0","a1","a2");
   return out;
}

void Fdatime(DOSTIME *timeptr, int16_t handle, int16_t wflag) {
	int32_t out;
	__asm(" move.w %[wflag],-(sp)\n"
	  " move.w %[handle],-(sp)\n"
	  " move.l %[timeptr],-(sp)\n"
	  " move.w #87,-(sp)\n"
	  " trap   #1\n"
	  " lea.l  10(sp),sp\n"
	  : "=Kd0" (out) // Unused
	  : [timeptr] "Kxreg32" (timeptr), [handle] "Kxreg16" (handle), [wflag] "Kxreg16" (wflag)
	  : "d0","d1","d2","a0","a1","a2");
}
