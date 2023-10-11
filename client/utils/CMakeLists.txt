cmake_minimum_required(VERSION 3.12)

set(SRC
    ${SRC}
    "${CMAKE_CURRENT_SOURCE_DIR}/AssetsManager/AssetsManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SceneManager/SceneManager.cpp"
    PARENT_SCOPE
)

set(INCLUDE
    ${INCLUDE}
    "${CMAKE_CURRENT_SOURCE_DIR}/AssetsManager/"
    "${CMAKE_CURRENT_SOURCE_DIR}/SceneManager/"
    PARENT_SCOPE
)
