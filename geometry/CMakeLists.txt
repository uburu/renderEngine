cmake_minimum_required(VERSION 3.12)
project(Geometry)

set(SOURCE_LIB geometry.cpp)

add_library(geometry STATIC ${SOURCE_LIB})