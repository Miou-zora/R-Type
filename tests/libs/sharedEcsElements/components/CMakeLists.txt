cmake_minimum_required(VERSION 3.10)

link_directories(${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/components)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/components"
    PARENT_SCOPE
)
