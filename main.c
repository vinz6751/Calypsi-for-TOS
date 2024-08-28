#include <stdio.h>
#include "tos.h"


static char buffer[30];
static char msg[] = "Hello world from Calypsi !\r\n";

int main(int argc, char *argv[], char *env) {
    printf("Hello from Calypsi!\n");
    Cconws("Environment:\r\n");
    sprintf(buffer,"argc=%d\r\n", argc);
    Cconws(buffer);
    Cconws(env ? env : "NULL");Cconws("\r\n");

    for (int i=0;i<argc; i++) {
        sprintf(buffer,"argv[%d]=%s\r\n", i, argv[i]);
        Cconws(buffer);
    }

    Cconws(msg); /* Display some string */

    Cnecin(); // Wait for key
    return 0;
}
