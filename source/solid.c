#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

int main(int argc, char *argv[]) {
    uint32_t color = 0;
    if (argc > 1) color = strtoul(argv[1], NULL, 16);
    uint32_t pixels[1024];
    memset_pattern4(pixels, &color, sizeof(pixels));
    for (;;) {
        fwrite(pixels, 4, 1024, stdout);
        if (ferror(stdout)) err(EX_IOERR, "fwrite");
    }
}
