cmake_minimum_required(VERSION 3.12)

set(SRC
    ${SRC}
    "${CMAKE_CURRENT_SOURCE_DIR}/KeyToString/KeyToString.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/AssetsManager/AssetsManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SceneManager/SceneManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/OptionManager/OptionManager.cpp"
    PARENT_SCOPE
)

set(INCLUDE
    ${INCLUDE}
    "${CMAKE_CURRENT_SOURCE_DIR}/KeyToString/"
    "${CMAKE_CURRENT_SOURCE_DIR}/AssetsManager/"
    "${CMAKE_CURRENT_SOURCE_DIR}/SceneManager/"
    "${CMAKE_CURRENT_SOURCE_DIR}/OptionManager/"
    PARENT_SCOPE
)
