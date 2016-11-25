cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT(postinfix)

enable_testing()
add_subdirectory(test)

set(APP_SOURCE
	ast.c ast.h stack.h stack.c parser.h parser.c)


add_executable(${PROJECT_NAME}
	main.c
	${APP_SOURCE}
	)
