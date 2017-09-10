#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    uint32_t fps = 60;
    size_t width = 640;
    size_t height = 480;

    if (argc > 1) {
        fps = strtoul(argv[1], NULL, 0);
    }
    if (argc > 2) {
        width = strtoul(argv[2], NULL, 0);
        height = width;
    }
    if (argc > 3) {
        height = strtoul(argv[3], NULL, 0);
    }
    if (!fps || !width || !height) return EX_USAGE;

    for (;;) {
        uint32_t frame[width * height];

        fread(frame, 4, width * height, stdin);
        if (ferror(stdin)) err(EX_IOERR, "fread");

        fwrite(frame, 4, width * height, stdout);
        if (ferror(stdout)) err(EX_IOERR, "fwrite");

        usleep(1000000 / fps);
    }
}
