CFLAGS = `pkg-config --cflags check` -g --std=c99
LIBS = `pkg-config --libs check`
VPATH=..
APPNAME=postinfix

TEST_OBJECTS = test_ast.o test_stack.o
OBJECTS_UNDER_TEST = ast.o stack.o
TEST_APP = test_$(APPNAME)

all: ${TEST_APP}
	./${TEST_APP}

full: all memtest

${TEST_APP}: test.o $(TEST_OBJECTS) ${OBJECTS_UNDER_TEST}
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

memtest: ${TEST_APP}
	CK_FORK=no valgrind --leak-check=full ./${TEST_APP}

clean:
	rm -f *.o
	rm -f ${TEST_APP}