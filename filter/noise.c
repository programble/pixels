#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

int main(int argc, char *argv[]) {
    uint8_t noise = 8;
    if (argc > 1) noise = strtoul(argv[1], NULL, 0);

    for (;;) {
        uint32_t pixels[1024];
        fread(pixels, 4, 1024, stdin);
        if (ferror(stdin)) err(EX_IOERR, "fread");

        for (int i = 0; i < 1024; ++i) {
            uint8_t bits = arc4random_uniform(noise);
            pixels[i] |= bits | bits << 8 | bits << 16;
        }

        fwrite(pixels, 4, 1024, stdout);
        if (ferror(stdout)) err(EX_IOERR, "fwrite");
    }
}
