include(${CMAKE_CURRENT_LIST_DIR}/names.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/system.cmake)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(crt_type d)
    set(cty_type_long _debug)
endif()

set(${CMAKE_PROJECT_NAME}_LINK_DIRECTORIES
    ${CMAKE_SOURCE_DIR}/lib/bin/${SYSTEM}
)

set(${MATH_LIBRARY}_LIBRARIES
    tbb${cty_type_long}
)

set(${CG_LIBRARY}_LIBRARIES
    ${MATH_LIBRARY}
    ${${MATH_LIBRARY}_LIBRARIES}
)

set(TEST_LIBRARIES
    gtest${crt_type}
    gmock${crt_type}
)