cmake_minimum_required(VERSION 3.12)
project(${APP_LIBRARY})

include(sources.cmake)

add_library(${APP_LIBRARY} STATIC ${${APP_LIBRARY}_SOURCES})