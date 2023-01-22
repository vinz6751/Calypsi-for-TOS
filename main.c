#include <stdio.h>
#include "tos.h"


static char buffer[30];
static char msg[] = "Hello world from Calypsi !\r\n";

int main(int argc, char *argv[], char *env) {
	printf("Hello from printf!\n");
    Cconws("Env:");
    sprintf(buffer,"argc=%d\r\n", argc);
    Cconws(buffer);
    Cconws(env ? env : "NULL");Cconws("\r\n");

    for (int i=0;i<argc; i++) {
        sprintf(buffer,"argv[%d]=%s\r\n", i, argv[i]);
        Cconws(buffer);
    }

    Cconws(msg); /* Display some string */
    return 0;
}
