.PHONY: all test clean

CFLAGS=-g --std=c99

APPNAME=postinfix

SRC = ast.o buffer.o operator.o parseaction.o parse_context.o parser.o stack.o

all: test $(APPNAME)

clean:
	APPNAME=$(APPNAME) $(MAKE) -C test clean
	rm -f *.o
	rm -f $(APPNAME)

test:
	$(MAKE) -C test full

$(APPNAME): $(SRC) main.o
	$(CC) -o $@ $^
