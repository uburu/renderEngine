cmake_minimum_required(VERSION 3.12)
project(Application)

set(SOURCE_LIB application.cpp)

add_library(application STATIC ${SOURCE_LIB})