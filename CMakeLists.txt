cmake_minimum_required(VERSION 3.22)
project(COMP_345_Project)

set(CMAKE_CXX_STANDARD 14)

#get googletest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0)

FetchContent_MakeAvailable(googletest)

if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

add_library(Example STATIC src/source/Example.cpp src/headers/Example.hpp)

add_executable(mainApp src/main.cpp)
target_link_libraries(mainApp Example)

add_executable(testRunner test/Test.cpp)
target_link_libraries(testRunner Example gtest_main gmock_main)
