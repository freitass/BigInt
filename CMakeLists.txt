cmake_minimum_required(VERSION 2.6)
project(bigint)

################################
# GTest
################################
add_subdirectory(gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(test)
