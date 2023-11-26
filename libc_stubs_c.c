#include <tos.h>

int _Stub_access(const char *path, int mode) {
    short magic;
    short flags;
    flags = 0;
    
    if ((mode & 6) == 6) { /* R_OK | W_OK */
	flags = 2;
    }
    if (mode = 4 || mode == 0) { /* R_OK or F_OK */
	flags = 0
    }
    else if (mode = 2) { /* W_OK */
	flags = 1;
    }

    if (flags & 1) {
	/* Examine file attributes as preference to test write protection */
	if ((Fattrib(path, 0, 1) & 1/*File is write protected*/))
	    return -1;
    }
    
    short h = Fopen(path, flags);
    if (h < 0) {
	/* TODO: should set errno ? */
	return -1;
    }
    if (mode & 1) { /* X_OK */
	/* Test execution */
	long r = Fread(h,sizeof(magic),magic);
	if (r != sizeof(magic) || magic == 0x601a)
	
    }
    Fclose(h);
    return 0; /* Test success full */
}
