cmake_minimum_required(VERSION 3.12)

add_subdirectory(ecs)
add_subdirectory(sharedEcsElements)
add_subdirectory(network)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    PARENT_SCOPE
)

