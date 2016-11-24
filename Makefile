.PHONY: all test clean

CFLAGS=-g --std=c99

APPNAME=postinfix

all: test $(APPNAME)

clean:
	APPNAME=$(APPNAME) $(MAKE) -C test clean
	rm -f *.o
	rm -f $(APPNAME)

test:
	$(MAKE) -C test full

$(APPNAME): main.o
	$(CC) -o $@ $^
