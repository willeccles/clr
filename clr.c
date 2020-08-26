#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// duplicate codes on the bottom rows are to make this even slightly readable
static const char* top = "  \033[9%dm██████\033[3%dm▄\033[m";
static const char* mid = "  \033[9%dm██████\033[3%dm█\033[m";
static const char* bot = "  \033[3%dm ▀▀▀▀▀\033[3%dm▀\033[m";

static uint8_t colors;

static void po(void) {
    char* coloropts = getenv("CLR_OPT");
    if (!coloropts) {
        colors = 0x7E;
    } else {
        if (!strlen(coloropts)
                || !strcmp(coloropts, "*")
                || !strcasecmp(coloropts, "ALL")) {
            colors = 0xFF;
        } else {
            colors = 0;
            char* opt;
            while ((opt = strtok(coloropts, ":"))) {
                int i = atoi(opt);
                if (i < 0 || i > 7) {
                    fprintf(stderr, "CLR_OPT: unknown color option: %d\n", i);
                } else {
                    colors |= 1 << i;
                }
                // see strtok(3)
                coloropts = NULL;
            }
        }
    }
}

static void pr(const char* r) {
    for (int i = 0; i < 8; i++) {
        if (colors & (1 << i)) {
            printf(r, i, i);
        }
    }
    printf("\n");
}

int main(void) {
    po();
    if (colors) {
        printf("\n");
        pr(top);
        pr(mid);
        pr(mid);
        pr(bot);
        printf("\n");
    }
    return 0;
}
