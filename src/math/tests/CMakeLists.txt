cmake_minimum_required(VERSION 3.12)
project(test-${MATH_LIBRARY})

include(sources.cmake)
include_directories(../)

add_gtest(${MATH_LIBRARY})