#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

int main(int argc, char *argv[]) {
    size_t count = 640 * 480 * 60;
    if (argc > 1) count = strtoul(argv[1], NULL, 0);
    if (!count) return EX_USAGE;
    uint32_t *pixels = calloc(count, 4);
    if (!pixels) err(EX_OSERR, "calloc");
    fread(pixels, 4, count, stdin);
    if (ferror(stdin)) err(EX_IOERR, "fread");
    for (;;) {
        fwrite(pixels, 4, count, stdout);
        if (ferror(stdout)) err(EX_IOERR, "fwrite");
    }
}
