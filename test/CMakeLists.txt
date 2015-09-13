################################
# Unit Tests
################################

include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_CXX_COMPILER g++-5)
set(CMAKE_CXX_FLAGS -std=c++0x)

# Add test cpp file
add_executable(unit_tests BigInt.cpp)
target_link_libraries(unit_tests gtest gtest_main)
add_test(unit_tests unit_tests)
