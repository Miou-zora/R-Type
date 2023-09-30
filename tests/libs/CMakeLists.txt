cmake_minimum_required(VERSION 3.10)

add_subdirectory(ecs)
add_subdirectory(sharedEcsElements)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    PARENT_SCOPE
)

