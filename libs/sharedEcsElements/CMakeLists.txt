cmake_minimum_required(VERSION 3.12)
set(LIBRARY_NAME "sharedEcsElements")

project(${LIBRARY_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra -Wshadow -Wuninitialized")

set(SRC)

set(INCLUDE)

add_subdirectory("component")
add_subdirectory("utils")

add_library(${LIBRARY_NAME} STATIC ${SRC} ${INCLUDE})
set_target_properties(${LIBRARY_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)
