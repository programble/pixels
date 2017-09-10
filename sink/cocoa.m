#import <Cocoa/Cocoa.h>
#import <err.h>
#import <stdint.h>
#import <stdlib.h>
#import <sysexits.h>
#import <unistd.h>

static size_t width = 640;
static size_t height = 480;

static uint8_t *pixels;

@interface PixelView : NSView { }
@end

@implementation PixelView
- (void) drawRect: (NSRect) __attribute__((unused)) rect {
    CGContextRef ctx = [[NSGraphicsContext currentContext] CGContext];

    CGColorSpaceRef rgb = CGColorSpaceCreateDeviceRGB();

    CGDataProviderRef data = CGDataProviderCreateWithData(
        NULL,
        pixels,
        width * height * 4,
        NULL
    );

    CGImageRef image = CGImageCreate(
        width,
        height,
        8,
        32,
        width * 4,
        rgb,
        kCGImageAlphaNoneSkipFirst | kCGBitmapByteOrder32Little,
        data,
        NULL,
        false,
        kCGRenderingIntentDefault
    );

    CGContextDrawImage(ctx, CGRectMake(0, 0, width, height), image);

    CGImageRelease(image);
    CGDataProviderRelease(data);
    CGColorSpaceRelease(rgb);
}
@end

int main(int argc, char *argv[]) {
    if (argc > 1) {
        width = strtol(argv[1], NULL, 10);
        if (!width) return EX_USAGE;
        height = width;
    }
    if (argc > 2) {
        height = strtol(argv[2], NULL, 10);
        if (!height) return EX_USAGE;
    }

    pixels = malloc(width * height * 4);
    if (!pixels) err(EX_OSERR, "malloc");

    [NSApplication sharedApplication];
    [NSApp setActivationPolicy: NSApplicationActivationPolicyRegular];

    NSWindow *window = [
        [NSWindow alloc]
        initWithContentRect: NSMakeRect(0, 0, width, height)
        styleMask: NSTitledWindowMask | NSClosableWindowMask
        backing: NSBackingStoreBuffered
        defer: NO
    ];
    [window setTitle: @"pixels"];
    [window center];

    PixelView *view = [[PixelView alloc] initWithFrame: [window frame]];
    [window setContentView: view];

    [window makeKeyAndOrderFront: nil];
    [NSApp activateIgnoringOtherApps: YES];

    for (;;) {
        for (;;) {
            NSEvent *event = [
                NSApp
                nextEventMatchingMask: NSAnyEventMask
                untilDate: [NSDate distantPast]
                inMode: NSDefaultRunLoopMode
                dequeue: YES
            ];
            if (!event) break;
            // TODO: Handle close, quit.
            [NSApp sendEvent: event];
        }

        fread(pixels, 1, width * height * 4, stdin);
        if (ferror(stdin)) err(EX_IOERR, "fread");

        [view setNeedsDisplay: YES];
    }
}
