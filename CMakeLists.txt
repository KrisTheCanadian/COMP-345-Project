cmake_minimum_required(VERSION 3.22)
project(COMP_345_Project)

set(CMAKE_CXX_STANDARD 14)

# ---------------------------------------------------------
# Dependencies
# ---------------------------------------------------------
include(CTest)
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.12.1)

FetchContent_MakeAvailable(googletest)

if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()



# ---------------------------------------------------------
# Map Library
# ---------------------------------------------------------
set(MAP_SRCS 
    src/Map/Map.cpp
    src/Map/Map.h 
    src/Map/Loader/MapLoader.cpp 
    src/Map/Loader/MapLoader.h 
    src/Map/Territory/Territory.cpp
    src/Map/Territory/Territory.h 
    src/Map/Continent/Continent.cpp 
    src/Map/Continent/Continent.h
    )

add_library(Map STATIC ${MAP_SRCS})
target_include_directories(Map PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Map
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Map/Loader
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Map/Territory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Map/Continent
    )

# ---------------------------------------------------------
# Map Test
# ---------------------------------------------------------
add_executable(testRunnerMap test/Map/TEST_MapLoader.cpp)
target_link_libraries(testRunnerMap gtest_main gmock_main Map)
add_test(NAME MapTests COMMAND testRunnerMap)

# ---------------------------------------------------------
# Map Driver - DEMO
# ---------------------------------------------------------
add_executable(MapDriver src/Map/MapDriver.cpp)
target_link_libraries(MapDriver Map)


# ---------------------------------------------------------
# Main
# ---------------------------------------------------------
add_executable(mainApp src/main.cpp)
target_link_libraries(mainApp Map)
