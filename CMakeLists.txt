cmake_minimum_required(VERSION 3.1)

project(HW2)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/)

add_library(calm SHARED
	${SRC_DIR}Chef.cpp
	${SRC_DIR}Func.cpp
	${SRC_DIR}Kitchen.cpp
	)

add_executable(main
	${SRC_DIR}main.cpp
	)

target_link_libraries(main calm)


# add_custom_target(
# 	one-file
# 	WORKING_DIRECTORY ${SRC_DIR}
# 	COMMAND  cat *.h *.cpp | sed 's/\\s*\#include\\s*\"/\\/\\/ \#include \"/' > compress.cpp
# 	)
