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
    assets/textures/layers/parallax-space-background.png
    assets/textures/layers/parallax-space-big-planet.png
    assets/textures/layers/parallax-space-far-planets.png
    assets/textures/layers/parallax-space-stars.png
    assets/textures/layers/parallax-space-ring-planet.png
    assets/textures/ally_bullets.png
    assets/textures/r-typesheet44.png
    assets/textures/buttons/MinusButton.png
    assets/textures/buttons/PlusButton.png
    assets/textures/buttons/OptionButton.png
    assets/textures/buttons/white_rectangle.png
    assets/textures/r-typesheet14.png
    assets/textures/r-typesheet18.png
    assets/textures/Top_wall.png
    assets/textures/Bot_wall.png

    assets/sounds/blaster.mp3
    assets/sounds/explosions.wav
    assets/sounds/boss-shot.wav
    assets/sounds/enemy-shot.wav
    assets/sounds/theme.mp3
)

set(SRC)

set(INCLUDE
    "${CMAKE_SOURCE_DIR}/libs/ecs/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/components/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/systems/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/utils/"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/tags/"
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
target_link_libraries(${EXECUTABLE_NAME} PRIVATE $<IF:$<TARGET_EXISTS:zstd::libzstd_shared>,zstd::libzstd_shared,zstd::libzstd_static>)

target_include_directories(${EXECUTABLE_NAME} PRIVATE include)

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${Boost_INCLUDE_DIRS})

set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
