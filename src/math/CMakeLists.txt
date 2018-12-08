cmake_minimum_required(VERSION 3.12)
project(${MATH_LIBRARY})

include(compile_options.cmake)
include(sources.cmake)

add_subdirectory(tests)