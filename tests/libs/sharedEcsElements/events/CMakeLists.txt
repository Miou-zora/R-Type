cmake_minimum_required(VERSION 3.12)

link_directories(${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/events)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/events"
    PARENT_SCOPE
)
