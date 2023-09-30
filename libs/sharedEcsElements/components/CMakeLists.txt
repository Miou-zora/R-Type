cmake_minimum_required(VERSION 3.12)

set(INCLUDE
    ${INCLUDE}
    "${CMAKE_CURRENT_SOURCE_DIR}/Drawable.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Transformable.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Velocity.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Controllable.hpp"
    PARENT_SCOPE
)
