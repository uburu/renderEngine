include(${CMAKE_SOURCE_DIR}/cmake/system.cmake)

if(${SYSTEM} STREQUAL "darwin")
    set(${MATH_LIBRARY}_COMPILE_OPTIONS
        -Wunused-local-typedef
    )
endif()