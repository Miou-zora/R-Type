cmake_minimum_required(VERSION 3.10)

add_subdirectory(utils)
link_directories(${CMAKE_SOURCE_DIR}/libs/sharedEcsElements)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/"
    PARENT_SCOPE
)
