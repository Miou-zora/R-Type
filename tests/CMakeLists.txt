cmake_minimum_required(VERSION 3.12)

enable_testing()

set(TEST_MAIN
    "main.cpp"
)

file(GLOB_RECURSE TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.test.cpp")

set(TEST_SRC
    ${TEST_FILES}
)

set(SRC
    "${CMAKE_SOURCE_DIR}/client/utils/SceneManager/SceneManager.cpp"
)

set(TEST_INCLUDE)

add_subdirectory("libs")
add_subdirectory("client")
add_subdirectory("server")

include_directories(${TEST_INCLUDE})

set(EXECUTABLE_NAME
    "unit_tests"
)

add_definitions(-DUNIT_TEST)
add_executable(${EXECUTABLE_NAME} ${TEST_MAIN} ${SRC} ${TEST_SRC} )
target_link_libraries(${EXECUTABLE_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME r-type_unit_tests COMMAND unit_tests)

set_target_properties(unit_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

