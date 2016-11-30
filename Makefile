.PHONY: all test clean

CFLAGS=-g --std=c99

APPNAME=postinfix
LIBNAME=lib$(APPNAME).a

SRC = ast.o buffer.o operator.o parseaction.o parse_context.o parser.o stack.o

all: test $(LIBNAME) $(APPNAME)

clean:
	APPNAME=$(APPNAME) $(MAKE) -C test clean
	rm -f *.o
	rm -f $(APPNAME)

test:
	$(MAKE) -C test full

$(LIBNAME): $(SRC)
	ar r $@ $^

$(APPNAME): $(LIBNAME) main.o
	$(CC) -o $@ $^ -L. -l$(APPNAME)
