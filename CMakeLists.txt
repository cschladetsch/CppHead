cmake_minimum_required(VERSION 3.20)
project(CppHead CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Main executable target referencing main.cpp in root
add_executable(cpphead main.cpp)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/gtest")
    target_include_directories(cpphead PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/external/gtest/googletest/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/external/gtest/googlemock/include"
    )
endif()

include(CTest)
if(BUILD_TESTING AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/gtest/CMakeLists.txt")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(external/gtest EXCLUDE_FROM_ALL)

    add_executable(cpphead_tests 
        tests/cpphead_tests.cpp
    )

    target_link_libraries(cpphead_tests PRIVATE gtest_main)
    target_include_directories(cpphead_tests PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/external/gtest/googletest/include"
    )

    include(GoogleTest)
    gtest_discover_tests(cpphead_tests)
endif()
