cmake_minimum_required(VERSION 3.9)
project(uburuRenderEngine)

include(cmake/names.cmake)
include(cmake/include_directories.cmake)
include(cmake/util.cmake)

include_directories(${${CMAKE_PROJECT_NAME}_INCLUDE_DIRECTORIES})

add_subdirectory(commands)
add_subdirectory(application)