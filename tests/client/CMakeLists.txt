cmake_minimum_required(VERSION 3.12)

add_subdirectory(components)
add_subdirectory(systems)
add_subdirectory(utils)

link_directories(${CMAKE_SOURCE_DIR}/client/)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/client/"
    PARENT_SCOPE
)
