cmake_minimum_required(VERSION 3.12)

set(SRC
    ${SRC}
    "${CMAKE_CURRENT_SOURCE_DIR}/loginPage.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/menuPage.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/joinPage.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/roomPage.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/GamePrefabs.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/OptionPage.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/endPage.cpp"
    PARENT_SCOPE
)

set(INCLUDE
    ${INCLUDE}
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    PARENT_SCOPE
)
