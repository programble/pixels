#include <err.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

int main(int argc, char *argv[]) {
    size_t width = 640, height = 479;
    if (argc > 1) width = strtoul(argv[1], NULL, 0);
    if (argc > 2) height = strtoul(argv[2], NULL, 0);
    if (!width || !height) return EX_USAGE;
    uint32_t pixels[height][width];
    memset(pixels, 0, sizeof(pixels));
    for (size_t i = 0; i < height; ++i) {
        double x = (double)i / (double)height * M_PI * 2.0;
        double y = sin(x);
        size_t n = (y + 1.0) * (double)width / 2.0;
        pixels[i][n] = 0xFFFFFF;
    }
    for (;;) {
        fwrite(pixels, 4, width * height, stdout);
        if (ferror(stdout)) err(EX_IOERR, "fwrite");
    }
}
