cmake_minimum_required(VERSION 3.12)
project(r-type)

set(CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_NAME "r-type_client")

find_package(CMakeRC REQUIRED)

cmrc_add_resource_library(
    ${EXECUTABLE_NAME}-resources

    ALIAS assets::rc
    NAMESPACE assets
    assets/textures/ships.png
    assets/textures/buttons/BackButton.png
    assets/textures/buttons/ExitButton.png
    assets/textures/buttons/IPZone.png
    assets/textures/buttons/PortZone.png
    assets/textures/buttons/StartButton.png
    assets/textures/buttons/SingleButton.png
    assets/textures/buttons/JoinRoomButton.png
    assets/textures/buttons/CreateRoomButton.png
    assets/textures/buttons/white_square.png
    assets/textures/spacebg.png
    assets/textures/R-Type_Logo.png
    assets/textures/r-typesheet5.png
    assets/textures/r-typesheet43.png
    assets/textures/bullet.png
    assets/textures/ally_bullets.png
)

set(SRC)

set(INCLUDE
    "${CMAKE_SOURCE_DIR}/libs/ecs/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/components/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/systems/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/utils/"
    "${CMAKE_SOURCE_DIR}/libs/network/"
    "${CMAKE_SOURCE_DIR}/libs/network/include"
)

add_subdirectory("components")
add_subdirectory("systems")
add_subdirectory("utils")
add_subdirectory("loads")
add_subdirectory("network")

include_directories(${INCLUDE})

add_executable(${EXECUTABLE_NAME}
        main.cpp
        ${SRC}
)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE Boost::boost Boost::system Boost::thread Boost::filesystem)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE raylib)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE assets::rc)
if (WIN32)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE winmm)
endif (WIN32)

target_include_directories(${EXECUTABLE_NAME} PRIVATE include)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
