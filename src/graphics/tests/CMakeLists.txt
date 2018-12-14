cmake_minimum_required(VERSION 3.12)
project(test-${CG_LIBRARY})

include(sources.cmake)
include_directories(../)

add_gtest(${CG_LIBRARY} ${CG_LIBRARY})