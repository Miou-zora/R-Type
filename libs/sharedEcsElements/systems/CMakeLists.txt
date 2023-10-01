cmake_minimum_required(VERSION 3.12)

set(SRC
    ${SRC}
    "${CMAKE_CURRENT_SOURCE_DIR}/Control/Control.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/VelocityApplicator/VelocityApplicator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Logging/Logging.cpp"
    PARENT_SCOPE
)

set(INCLUDE
    ${INCLUDE}
    "${CMAKE_CURRENT_SOURCE_DIR}/Control/"
    "${CMAKE_CURRENT_SOURCE_DIR}/VelocityApplicator/"
    "${CMAKE_CURRENT_SOURCE_DIR}/Logging/"
    PARENT_SCOPE
)
