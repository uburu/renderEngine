cmake_minimum_required(VERSION 3.12)
project(${CURVE_EXAMPLE})

include(sources.cmake)

add_executable(${CURVE_EXAMPLE} ${${CURVE_EXAMPLE}_SOURCES})
target_link_libraries(${CURVE_EXAMPLE} ${CG_LIBRARY} ${${CG_LIBRARY}_LIBRARIES})
copy_target_dlls(${CURVE_EXAMPLE})
