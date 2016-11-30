
INCLUDE( FindPkgConfig )

# Take care about check.pc settings
PKG_SEARCH_MODULE( CHECK check )
SET(CMAKE_C_FLAGS ${CHECK_CFLAGS} )
include_directories(${CHECK_INCLUDE_DIRS})

SET(TEST_SRC
	test_ast.c test.c test_stack.c test_traverse.c test_parser.c test_parsecontext.c test_integration.c test_buffer.c)

SET(UNIT_UNDER_TEST_SRC
	../ast.c ../stack.h ../stack.c ../parser.h ../parser.c ../operator.h ../operator.c ../parse_context.h ../parse_context.c ../parseaction.h ../parseaction.c ../buffer.h ../buffer.c)

SET(TEST_NAME test_${PROJECT_NAME})
ADD_EXECUTABLE(${TEST_NAME}
	${TEST_SRC}
	${UNIT_UNDER_TEST_SRC})

SET_PROPERTY(TARGET ${TEST_NAME} PROPERTY C_STANDARD 99)
TARGET_LINK_LIBRARIES(${TEST_NAME}
	${CHECK_LDFLAGS})

ADD_TEST(UnitTest ${TEST_NAME})
ADD_TEST(Memory valgrind --leak-check=full --error-exitcode=1 ./${TEST_NAME} --nofork)

