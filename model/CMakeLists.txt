cmake_minimum_required(VERSION 3.12)
project(model)

set(SOURCE_LIB model.cpp)

add_library(model STATIC ${SOURCE_LIB})