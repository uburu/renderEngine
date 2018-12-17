cmake_minimum_required(VERSION 3.12)
project(${RENDER_EXAMPLE})

include(sources.cmake)

add_executable(${RENDER_EXAMPLE} ${${RENDER_EXAMPLE}_SOURCES})
target_link_libraries(${RENDER_EXAMPLE} ${CG_LIBRARY} ${${CG_LIBRARY}_LIBRARIES})
copy_target_dlls(${RENDER_EXAMPLE})
