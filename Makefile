SOURCES = source/random source/sin source/solid
FILTERS = filter/fps filter/loop filter/noise
SINKS = sink/cocoa

OBJC ?= $(CC)
CWARNS = -Wall -Wextra -Wpedantic

all: $(SOURCES) $(FILTERS) $(SINKS)

sink/cocoa: sink/cocoa.m

.c:
	$(CC) $(CWARNS) $(CFLAGS) -o $@ $<

.m:
	$(OBJC) $(CWARNS) $(OBJCFLAGS) -framework Cocoa -o $@ $<

clean:
	rm -f $(SOURCES) $(FILTERS) $(SINKS)

.PHONY: all clean
