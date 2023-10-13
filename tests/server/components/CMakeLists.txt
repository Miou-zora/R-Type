cmake_minimum_required(VERSION 3.10)

link_directories(${CMAKE_SOURCE_DIR}/server/components/)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/server/utils/"
    "${CMAKE_SOURCE_DIR}/server/network/"
    "${CMAKE_SOURCE_DIR}/server/components/"
    PARENT_SCOPE
)
