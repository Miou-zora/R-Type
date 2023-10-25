cmake_minimum_required(VERSION 3.12)
project(r-type)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_NAME "r-type_server")

set(SRC)

set(INCLUDE
    "${CMAKE_SOURCE_DIR}/libs/ecs/"
    "${CMAKE_SOURCE_DIR}/libs/network/"
    "${CMAKE_SOURCE_DIR}/libs/network/include"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/components/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/systems/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/utils/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/tags/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/events/"
)

add_subdirectory("components")
add_subdirectory("systems")
add_subdirectory("network")
add_subdirectory("utils")

include_directories(${INCLUDE})

add_executable(${EXECUTABLE_NAME}
        main.cpp
        ${SRC}
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE Boost::boost Boost::system Boost::thread Boost::filesystem)

target_include_directories(${EXECUTABLE_NAME} PRIVATE include)
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
