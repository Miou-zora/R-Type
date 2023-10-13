cmake_minimum_required(VERSION 3.12)

link_directories(${CMAKE_SOURCE_DIR}/server/systems)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/server/utils/"
    "${CMAKE_SOURCE_DIR}/server/systems/"
    "${CMAKE_SOURCE_DIR}/server/components/"
    PARENT_SCOPE
)
