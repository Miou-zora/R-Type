cmake_minimum_required(VERSION 3.12)
project(ecs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra -Wshadow -Wuninitialized")

set(INCLUDE
    "Entity.hpp"
    "IndexedZipper.hpp"
    "IndexedZipperIterator.hpp"
    "Prefab.hpp"
    "Registry.hpp"
    "SparseArray.hpp"
    "ZipperIterator.hpp"
    "Zipper.hpp"
    "Exceptions.hpp"
)

add_library(ecs STATIC ${INCLUDE})
set_target_properties(ecs PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(ecs PROPERTIES LINKER_LANGUAGE CXX)
