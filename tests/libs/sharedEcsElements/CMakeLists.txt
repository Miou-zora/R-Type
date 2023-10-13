cmake_minimum_required(VERSION 3.12)

add_subdirectory(utils)
add_subdirectory(components)
add_subdirectory(systems)

link_directories(${CMAKE_SOURCE_DIR}/libs/sharedEcsElements)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/"
    PARENT_SCOPE
)
