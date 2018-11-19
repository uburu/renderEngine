cmake_minimum_required(VERSION 3.12)
project(OpenCommand)

set(SOURCE_LIB open_command.cc)

add_library(open_command STATIC ${SOURCE_LIB})