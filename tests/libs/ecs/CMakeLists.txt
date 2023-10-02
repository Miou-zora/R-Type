cmake_minimum_required(VERSION 3.10)

link_directories(${CMAKE_SOURCE_DIR}/libs/ecs/include)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/libs/ecs/include"
    PARENT_SCOPE
)
