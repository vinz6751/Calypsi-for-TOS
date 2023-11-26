#ifndef _TOS_H
#define _TOS_H

/* Thank you tos.hyp ! */

#include <stdint.h>

/* TOS error messages */
#define E_OK      0 /* OK. No error has arisen */
#define EINVFN  -32 /* Unknown function number */
#define EFILNF  -33 /* File not found */
#define EPTHNF  -34 /* Directory (folder) not found */
#define ENHNDL  -35 /* No more handles available **/
#define EACCDN  -36 /* Access denied */
#define EIHNDL  -37 /* Invalid file handle */
#define ENSMEM  -39 /* Insufficient memory */
#define EIMBA   -40 /* Invalid memory block address */
#define EDRIVE  -46 /* Invalid drive specification */
#define ECWD    -47 /* Current directory cannot be deleted */
#define ENSAME  -48 /* Files on different logical drives */
#define ENMFIL  -49 /* No more files can be opened */
#define ELOCKED -58 /* Segment of a file is protected (network) */
#define ENSLOCK -59 /* Invalid lock removal request */
#define ERANGE  -64 /* File pointer in invalid segment (see also FreeMiNT message -88) */
#define EINTRN  -65 /* Internal error of GEMDOS */
#define EPLFMT  -66 /* Invalid program load format */
#define EGSBF   -67 /* Allocated memory block could not be enlarged */
#define EBREAK  -68 /* Program termination by Control-C */
#define EXCPT   -69 /* 68000 exception (bombs) */
#define EPTHOV  -70 /* Path overflow */
#define ELOOP   -80 /* Endless loop with symbolic links */
#define EPIPE   -81 /* Write to broken pipe. */

/* BIOS structures */
/* BIOS parameter block */
typedef struct
{
	int16_t recsiz; /* Bytes per sector */
	int16_t clsiz;  /* Sectors per cluster */
	int16_t clsizb; /* Bytes per cluster */
	int16_t rdlen;  /* Directory length */
	int16_t fsiz;   /* Length of the FAT in sectors */
	int16_t fatrec; /* Start of the 2nd FAT */
	int16_t datrec; /* 1st free sector */
	int16_t numcl;  /* Total number of clusters */
	int16_t bflags; /* Flags as bit-vector */
                       /* Bit 0: 0 (12-Bit-FAT), 1 16-Bit-FAT  */
                       /* Bit 1: 0 (two FATs), 1 (one FAT)     */
                       /*        only available since TOS 2.06 */
} BPB;


/* Process Descriptor */
typedef struct basep
{
	char		*p_lowtpa;	/* pointer to self (bottom of TPA) */
	char		*p_hitpa;	/* pointer to top of TPA + 1 */
	char		*p_tbase;	/* base of text segment */
	long		p_tlen;		/* 12 length of text segment */
	char		*p_dbase;	/* base of data segment */
	long		p_dlen;		/* length of data segment */
	char		*p_bbase;	/* base of BSS segment */
	long		p_blen;		/* length of BSS segment */
	char		*p_dta;		/* pointer to current DTA */
	struct basep	*p_parent;	/* pointer to parent's basepage */
	char		*p_reserved;	/* reserved for future use */
	char		*p_env;		/* pointer to environment string */
	long		p_undef[20];	/* scratch area... don't touch */
	char		p_cmdlin[128];	/* command line image */
} BASEPAGE;

/* Memory Descriptor */
typedef struct md_t
{
     struct md_t *m_link;         /* Next MD (or NULL)          */
     long m_start;       /* saddr of block             */
     long m_length;      /* # bytes in block           */
     BASEPAGE *m_own;          /* Owner's process descriptor */
} MD;

/* Memory Partition Block */
typedef struct
{
    MD *mp_mfl;      /* Memory free list      */
    MD *mp_mal;      /* Memory allocated list */
    MD *mp_rover;    /* Roving ptr            */
} MPB;

/* BIOS functions */
void    Getmpb (MPB *ptr);
int16_t Bconstat(int16_t dev);
int32_t Bconin(int16_t dev);
void    Bconout(int16_t dev, int16_t c);
int32_t Rwabs(int16_t rwflag, void *buff, int16_t cnt, int16_t recnr, int16_t dev, int32_t lrecno );
int32_t Setexc(int16_t number, void (*vec)(void));
int32_t Tickcal(void);
int32_t Bcostat(int16_t dev);
int32_t Mediach(int16_t dev);
int32_t Drvmap(void);
int32_t Kbshift(int16_t mode);

/* BIOS device numbers */
#define BDEV_PRN  0 /* Printer / parallel port */
#define BDEV_AUX  1 /* Serial port */
#define BDEV_CON  2 /* Console */
#define BDEV_MIDI 3 /* MIDI port */
#define BDEV_IKBD 4 /* Keyboard processor */
#define BDEV_SCRN 5 /* Screen */
#define BDEV_MDM1 6 /* MFP 68901's serial port */
#define BDEV_MDM2 7 /* MFP 68901's serial port */


/* XBIOS structures */
typedef struct
{
	int8_t  topmode;  /* 0: Y=0 at bottom */
					  /* 1: Y=1 at top */
	int8_t  buttons;  /* Similar to  IKBD */
	int8_t  x_scale;  /* Additional parameters */
	int8_t  y_scale;  /* Dependent on selected mode */
	int16_t x_max;    /* Maximum X position */
	int16_t y_max;    /* Maximum Y position */
	int16_t x_start;  /* Start position X */
	int16_t y_start;  /* Start position Y */
} MOUSE;

typedef struct
{
   void   *ibuf;    /* Pointer to buffer      */
   int16_t ibufsiz; /* Size of buffer         */
   int16_t ibufhd;  /* Head index             */
   int16_t ibuftl;  /* Tail index             */
   int16_t ibuflow; /* Low-water mark         */
   int16_t ibufhi;  /* High-water mark        */
} IOREC;

typedef struct
{
   int8_t *unshift;       /* Table of 'normal' key presses  */
   int8_t *shift;         /* Table of Shift key presses     */
   int8_t *capslock;      /* Table of Capslock key presses  */
   int8_t *altunshift;    /* From TOS 4.00, undocumented!   */
   int8_t *altshift;      /* From TOS 4.00, undocumented!   */
   int8_t *altcapslock;   /* From TOS 4.00, undocumented!   */
   int8_t *altgr;         /* From TOS 4.00, undocumented!   */
} KEYTAB;

typedef struct
{
   void   (*kb_midivec)();   /* MIDI interrupt vector    */
   void   (*kb_vkbderr)();   /* Keyboard error vector    */
   void   (*kb_vmiderr)();   /* MIDI error vector        */
   void   (*kb_statvec)();   /* Keyboard status          */
   void   (*kb_mousevec)();  /* Keyboard mouse status    */
   void   (*kb_clockvec)();  /* Keyboard clock           */
   void   (*kb_joyvec)();    /* Keyboard joystick status */
   void   (*kb_midisys)();   /* System Midi vector       */
   void   (*kb_kbdsys)();    /* Keyboard vector          */
   int8_t drvstat;           /* Keyboard driver status   */
} KBDVBASE;

typedef struct
{
   void    *pb_scrptr;  /* Pointer to start of screen memory */
   int16_t  pb_offset;  /* Offset to be added to this        */
   int16_t  pb_width;   /* Screen width in dots              */
   int16_t  pb_height;  /* Screen height in dots             */
   int16_t  pb_left;    /* Left margin in dots               */
   int16_t  pb_right;   /* Right margin in dots              */
   int16_t  pb_screz;   /* Resolution                        */
   int16_t  pb_prrez;   /* Printer type (Atari/Epson)        */
   void    *pb_colptr;  /* Pointer to colour palette         */
   int16_t  pb_prtype;  /* 0: Atari matrix monochrome
                           1: Atari matrix colour
                           2: Atari daisywheel monochrome
                           3: Epson matrix monochrome        */
   int16_t  pb_prport;  /* Centronics/RS-232 port            */
   void    *pb_mask;    /* Pointer to halftone mask          */
} PBDEF;

/* XBIOS functions */
void    Initmouse(int16_t type, MOUSE *par, void (*mousevec)(void));
void   *Ssbrk(int16_t count);
void   *Physbase(void);
void   *Logbase(void);
int16_t Getrez(void);
void    Setscreen(void *laddr, void *paddr, int16_t rez);
void    VsetScreen(void *laddr, void *paddr, int16_t rez, int16_t mode );
void    Setpalette(void *pallptr);
int16_t Setcolor(int16_t colornum, int16_t color);
int16_t Floprd(void *buf, int32_t filler, int16_t devno, int16_t sectno, int16_t trackno, int16_t sideno, int16_t count);
int16_t Flopwr(void *buf, int32_t filler, int16_t devno, int16_t sectno, int16_t trackno, int16_t sideno, int16_t count);
int16_t Flopfmt(void *buf, int32_t filler, int16_t devno, int16_t spt, int16_t trackno, int16_t sideno, int16_t interlv, int32_t magic, int16_t virgin);
void    Dbmsg(int16_t rsrvd, int16_t msg_num, int32_t msg_arg);
void    Midiws(int16_t cnt, void *ptr);
void    Mfpint(int16_t number, int16_t (*vector)(void));
IOREC  *Iorec(int16_t dev);
int32_t Rsconf(int16_t baud, int16_t ctr, int16_t ucr, int16_t rsr, int16_t tsr, int16_t scr);
KEYTAB *Keytbl(void *unshift, void *shift, void *capslock);
int32_t Random(void);
void    Protobt(void *buf, int32_t serialno, int16_t disktype, int16_t execflag); 
int16_t Flopver(void *buf, int32_t filler, int16_t devno, int16_t sectno, int16_t trackno, int16_t sideno, int16_t count);
void    Scrdmp(void);
int16_t Cursconf(int16_t func, int16_t rate);
void    Settime(uint32_t time);
uint32_t Gettime(void);
void    Bioskeys(void);
void    Ikbdws(int16_t count, const int8_t *ptr);
void    Jdisint(int16_t number);
void    Jenabint(int16_t number);
int8_t  Giaccess(int16_t data, int16_t regno);
void    Offgibit(int16_t bitno);
void    Ongibit(int16_t bitno);
void    Xbtimer(int16_t timer, int16_t control, int16_t data, void(*vector)(void));
void   *Dosound(const int8_t *buf);
int16_t Setprt(int16_t config);
KBDVBASE *Kbdvbase(void);
int16_t Kbrate( int16_t initial, int16_t repeat);
int16_t Prtblk( PBDEF *par );
void    Vsync(void);
int32_t Supexec(int32_t (*func)(void));
void    Puntaes(void);
int16_t Floprate(int16_t devno, int16_t newrate);
int16_t DMAread(int32_t sector, int16_t count, void *buffer, int16_t devno);
int16_t DMAwrite(int32_t sector, int16_t count, void *buffer, int16_t devno);
int32_t Bconmap(int16_t devno);
int16_t Blitmode(int16_t mode );



/* GEMDOS */

typedef struct
{
    uint8_t   maxlen;        /* Maximum line length */
    uint8_t   actuallen;     /* Current line length */
    int8_t    buffer[255];   /* Line buffer         */
} LINE;

/* Terminate program, returning 0 as error code*/
void Pterm0(void);

/* Terminate the program with the given return code */
void Pterm(uint16_t);

/* Output a character */
void Cconout(int16_t);

/* Wait for a key (no echo) */
void Cnecin();

/* Display a string*/
void Cconws(const char *);

/* Read string from console */
int32_t Cconrs(LINE *buf);

#endif
