cmake_minimum_required(VERSION 3.12)
project(${MATH_LIBRARY})

include(compile_options.cmake)
include(sources.cmake)

add_library(${MATH_LIBRARY} ${${MATH_LIBRARY}_SOURCES})
add_subdirectory(tests)