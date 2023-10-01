cmake_minimum_required(VERSION 3.10)

link_directories(${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/systems)
link_directories(${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/systems/Control)
link_directories(${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/systems/VelocityApplicator)
link_directories(${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/systems/Logging)

set(TEST_INCLUDE
    ${TEST_INCLUDE}
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/systems"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/systems/Control"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/systems/VelocityApplicator"
    "${CMAKE_SOURCE_DIR}/libs/sharedEcsElements/systems/Logging"
    PARENT_SCOPE
)
