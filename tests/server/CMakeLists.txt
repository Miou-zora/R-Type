cmake_minimum_required(VERSION 3.12)

add_subdirectory(utils)

link_directories(${CMAKE_SOURCE_DIR}/server/)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/"
    "${CMAKE_SOURCE_DIR}/server/"
    PARENT_SCOPE
)
