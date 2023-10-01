cmake_minimum_required(VERSION 3.12)
project(r-type)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_NAME "r-type_client")

find_package(CMakeRC REQUIRED)

cmrc_add_resource_library(
    ${EXECUTABLE_NAME}-resources

    ALIAS assets::rc
    NAMESPACE assets

)

add_executable(${EXECUTABLE_NAME}
        src/main.cpp
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE Boost::boost Boost::system Boost::thread Boost::filesystem)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE raylib)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE assets::rc)
if (WIN32)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE winmm)
endif (WIN32)

target_include_directories(${EXECUTABLE_NAME} PRIVATE include)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
