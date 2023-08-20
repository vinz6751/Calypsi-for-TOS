/* Parse the command line given in the BASEPAGE.p_cmdlin */
#include <string.h>

enum cmd_line_parsing_state {
    SKIPPING_WHITESPACE,
    PARSING_QUOTED,
    PARSING_UNQUOTED
};

extern char * const __env;

int parse_cmd_line(unsigned char length, char *cmdline, char **argv)
{
    int state = SKIPPING_WHITESPACE;
    char *c, *start, *end;
    int argc = 0;

    for (start = c = cmdline, end = &cmdline[length]; c < end; c++) {
        switch (state) {
            case SKIPPING_WHITESPACE:
                if (*c == ' ')
                    continue;
                else if (*c == '\"') {
                    state = PARSING_QUOTED;
                    c++;
                    start = c;
                }
                else {
                    state = PARSING_UNQUOTED;
                    start = c;
                }
                break;
            case PARSING_QUOTED:
                if (*c == '"') {
                    *c = '\0';
                    argv[argc++] = start;
                    state = SKIPPING_WHITESPACE;
                }
                break;
            case PARSING_UNQUOTED:
                if (*c == ' ') {
                    *c = '\0';
                    argv[argc++] = start;
                    state = SKIPPING_WHITESPACE;
                }
                break;
        }
    }
    if (state != SKIPPING_WHITESPACE)
        argv[argc++] = start;

    argv[argc] = (char*)0L;
    return argc;
}

char *getenv(const char *psrch)
{
    char *p;
    short len;
    char  *ppath;

    len = strlen(psrch);
    ppath = NULL;

    // Scan environment string until double null
    for (p = __env; *p; ) {
        if (strncmp(p, psrch, len) == 0 && p[len+1] == '=') {
            ppath = p + len + 1;
            break;
        }
        while(*p++) // skip to end of current env variable
            ;
    }
    return ppath;
}
