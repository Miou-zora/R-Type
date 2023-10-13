cmake_minimum_required(VERSION 3.12)

link_directories(${CMAKE_SOURCE_DIR}/client/systems/)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/client/systems/"
    "${CMAKE_SOURCE_DIR}/libs/ecs/"
    PARENT_SCOPE
)
