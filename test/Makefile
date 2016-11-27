CFLAGS = `pkg-config --cflags check` -g --std=c99
LIBS = `pkg-config --libs check`
VPATH=..
APPNAME=postinfix

TEST_OBJECTS = test_ast.o test_stack.o test_traverse.o test_parser.o test_parsecontext.o
OBJECTS_UNDER_TEST = ast.o stack.o parser.o operator.o parse_context.o parseaction.o
TEST_APP = test_$(APPNAME)

all: ${TEST_APP}
	./${TEST_APP}

full: all memtest

${TEST_APP}: test.o $(TEST_OBJECTS) ${OBJECTS_UNDER_TEST}
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

memtest: ${TEST_APP}
	valgrind --leak-check=full --error-exitcode=1 ./${TEST_APP} --nofork

clean:
	rm -f *.o
	rm -f ${TEST_APP}
