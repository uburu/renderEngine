include(${CMAKE_CURRENT_LIST_DIR}/system.cmake)

IF(${SYSTEM} STREQUAL "darwin")
    SET(UBURUENGINE_DEFINITIONS
        -Wunused-local-typedef
    )
ENDIF()