cmake_minimum_required(VERSION 3.12)

link_directories(${CMAKE_SOURCE_DIR}/client/utils/SceneManager/)
link_directories(${CMAKE_SOURCE_DIR}/client/utils/AssetsManager/)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/client/utils/SceneManager/"
    "${CMAKE_SOURCE_DIR}/client/utils/AssetsManager/"
    PARENT_SCOPE
)
