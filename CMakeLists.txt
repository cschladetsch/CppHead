cmake_minimum_required(VERSION 3.20)
project(CppHead LANGUAGES CXX)

# Require C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main Head Executable
add_executable(head main.cpp)

# Enable Testing
enable_testing()

# Fetch GoogleTest automatically via FetchContent (replaces submodule requirement)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows MSVC: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Unit Tests Executable
add_executable(cpphead_tests cpphead_tests.cpp)
target_link_libraries(cpphead_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(cpphead_tests)

# Micro-Benchmark Executable
add_executable(cpphead_benchmark benchmark.cpp)
