cmake_minimum_required(VERSION 3.12)
project(uburuRenderEngine)

include(cmake/names.cmake)
include(cmake/definitions.cmake)
include(cmake/include_directories.cmake)
include(cmake/libraries.cmake)
include(cmake/util.cmake)

REQUIRE_CXX_17()

add_definitions(${${CMAKE_PROJECT_NAME}_DEFINITIONS})
include_directories(${${CMAKE_PROJECT_NAME}_INCLUDE_DIRECTORIES})
link_directories(${${CMAKE_PROJECT_NAME}_LINK_DIRECTORIES})

add_subdirectory(src)