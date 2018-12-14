CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(${CG_LIBRARY})

include(sources.cmake)

add_library(${CG_LIBRARY} ${${CG_LIBRARY}_SOURCES})
add_dependencies(${CG_LIBRARY} ${MATH_LIBRARY})

add_subdirectory(tests)