#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

int main() {
    uint32_t pixels[1024];
    for (;;) {
        for (int i = 0; i < 1024; ++i) {
            pixels[i] = arc4random_uniform(0x1000000);
        }
        fwrite(pixels, 4, 1024, stdout);
        if (ferror(stdout)) err(EX_IOERR, "fwrite");
    }
}
