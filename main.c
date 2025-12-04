#include <stdio.h>
#include "tos.h"


static char buffer[30];
static char msg[] = "Hello world from Calypsi !\r\n";

int main(int argc, char *argv[], char *env) {
#if 0
    printf("Hello from Calypsi!\n");
#endif
    Cconws("Environment:\r\n");
#if 0
    sprintf(buffer,"argc=%d\r\n", argc);
    Cconws(buffer);
    Cconws(env ? env : "NULL");Cconws("\r\n");

    for (int i=0;i<argc; i++) {
        sprintf(buffer,"argv[%d]=%s\r\n", i, argv[i]);
        Cconws(buffer);
    }

    Cconws(msg); /* Display some string */

    Cnecin(); // Wait for key
#endif
    return 0;
}
