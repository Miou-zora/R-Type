cmake_minimum_required(VERSION 3.12)
project(r-type)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()

find_package(Boost 1.82.0 REQUIRED COMPONENTS system thread filesystem)
find_package(GTest CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(libs)
add_subdirectory(tests)
