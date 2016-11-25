
INCLUDE( FindPkgConfig )

# Take care about check.pc settings
PKG_SEARCH_MODULE( CHECK check )
SET(CMAKE_C_FLAGS ${CHECK_CFLAGS} )
include_directories(${CHECK_INCLUDE_DIRS})

SET(TEST_SRC
	test_ast.c test.c test_stack.c)

SET(UNIT_UNDER_TEST_SRC
	../ast.c ../stack.h ../stack.c)

SET(TEST_NAME test_${PROJECT_NAME})
ADD_EXECUTABLE(${TEST_NAME}
	${TEST_SRC}
	${UNIT_UNDER_TEST_SRC})

SET_PROPERTY(TARGET ${TEST_NAME} PROPERTY C_STANDARD 99)
TARGET_LINK_LIBRARIES(${TEST_NAME}
	${CHECK_LDFLAGS})

ADD_TEST(UnitTest ${TEST_NAME})
ADD_TEST(Memory valgrind --leak-check=full ./${TEST_NAME} --nofork)

