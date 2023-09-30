cmake_minimum_required(VERSION 3.10)

enable_testing()

set(TEST_MAIN
    "main.cpp"
)

file(GLOB_RECURSE TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.test.cpp")

set(TEST_SRC
    ${TEST_FILES}
)

set(TEST_INCLUDE)

add_subdirectory("libs")

include_directories(${TEST_INCLUDE})

set(EXECUTABLE_NAME
    "unit_tests"
)

add_executable(${EXECUTABLE_NAME} ${TEST_MAIN} ${SRC} ${TEST_SRC})
target_link_libraries(${EXECUTABLE_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME r-type_unit_tests COMMAND unit_tests)

set_target_properties(unit_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

