macro(REQUIRE_CXX_17)
    set(CMAKE_CXX_STANDARD 17)

    # MSVC with C++17
    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++latest")
        else()
            message(FATAL_ERROR "C++17 is required")
        ENDIF()
    endif()
endmacro()

macro(copy_target_dlls target_name)
    file(GLOB dlls ${CMAKE_SOURCE_DIR}/lib/bin/${SYSTEM}/*${CMAKE_SHARED_LIBRARY_SUFFIX})

    foreach(dll ${dlls})
        file(COPY ${dll} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
    endforeach(dll ${dlls})
endmacro()

macro(add_gtest test_name)
    add_executable(test-${test_name} ${CMAKE_SOURCE_DIR}/src/global/default_tests_main.cc ${TEST_${test_name}_SOURCES})
    target_compile_options(test-${test_name} BEFORE PRIVATE "${${test_name}_COMPILE_OPTIONS}")
    target_link_libraries(test-${test_name} ${${test_name}_LIBRARIES} ${TEST_LIBRARIES})

    copy_target_dlls(test-${test_name})
endmacro()