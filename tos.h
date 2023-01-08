#ifndef _TOS_H
#define _TOS_H

/* Thank you */

#include <stdint.h>

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