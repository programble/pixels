#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

int main(int argc, char *argv[]) {
    size_t repeat = 640;
    if (argc > 1) repeat = strtoul(argv[1], NULL, 0);
    if (!repeat) return EX_USAGE;
    uint32_t pixels[repeat];
    for (;;) {
        fread(pixels, 4, 1, stdin);
        if (ferror(stdin)) err(EX_IOERR, "fread");
        memset_pattern4(pixels, pixels, sizeof(pixels));
        fwrite(pixels, 4, repeat, stdout);
        if (ferror(stdout)) err(EX_IOERR, "fwrite");
    }
}
