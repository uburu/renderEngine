cmake_minimum_required(VERSION 3.12)
project(uburuRenderEngine)

include(cmake/names.cmake)
include(cmake/definitions.cmake)
include(cmake/include_directories.cmake)
include(cmake/libraries.cmake)
include(cmake/util.cmake)

REQUIRE_CXX_17()

include_directories(${${CMAKE_PROJECT_NAME}_INCLUDE_DIRECTORIES})
link_directories(${${CMAKE_PROJECT_NAME}_LINK_DIRECTORIES})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${UBURUENGINE_DEFINITIONS}")

add_subdirectory(src)