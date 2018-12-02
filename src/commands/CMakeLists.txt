cmake_minimum_required(VERSION 3.12)
project(${CMD_LIBRARY})

include(sources.cmake)

add_library(${CMD_LIBRARY} STATIC ${${CMD_LIBRARY}_SOURCES})