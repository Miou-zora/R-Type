cmake_minimum_required(VERSION 3.12)

set(SRC
    ${SRC}
    "${CMAKE_CURRENT_SOURCE_DIR}/loginPage.cpp"
    PARENT_SCOPE
)

set(INCLUDE
    ${INCLUDE}
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    PARENT_SCOPE
)
