cmake_minimum_required(VERSION 3.12)
project(Tgaimage)

set(SOURCE_LIB tgaimage.cpp)

add_library(tgaimage STATIC ${SOURCE_LIB})

#find_package( GTest REQUIRED )
#include_directories(${GTEST_INCLUDE_DIRS})
#
#add_executable(test_session test/test_session.cc)
#
#target_link_libraries(test_session ${GTEST_LIBRARIES})
#target_link_libraries(test_session session)