cmake_minimum_required(VERSION 3.12)

link_directories(${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/components)
link_directories(${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/tags)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/components"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/tags"
    PARENT_SCOPE
)
