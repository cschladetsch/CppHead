cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0135 NEW)
project(CppHead LANGUAGES CXX)

# Require C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main Head Executable
add_executable(head main.cpp)

# Enable Testing
enable_testing()

# Fetch GoogleTest automatically via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Unit Tests Executable (located in tests/)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/cpphead_tests.cpp")
    add_executable(cpphead_tests tests/cpphead_tests.cpp)
    target_link_libraries(cpphead_tests PRIVATE GTest::gtest_main)
    include(GoogleTest)
    gtest_discover_tests(cpphead_tests)
endif()

# Micro-Benchmark Executable (located in tests/)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/benchmark.cpp")
    add_executable(cpphead_benchmark tests/benchmark.cpp)
endif()
