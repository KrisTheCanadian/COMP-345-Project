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
    src/Player/Player.cpp src/Player/Player.h)

add_library(Map STATIC ${MAP_SRCS})
target_include_directories(Map PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Map
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Map/Loader
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Map/Territory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Map/Continent
    )

# ---------------------------------------------------------
# Player Library
# ---------------------------------------------------------

set(PLAYER_SRCS
    src/Player/Player.cpp
    src/Player/Player.h
    )
add_library(Player STATIC ${PLAYER_SRCS}
    )
target_include_directories(Player PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Player
    )

# ---------------------------------------------------------
# Order Library
# ---------------------------------------------------------
set(ORDER_SRCS
    src/Orders/Orders.cpp
    src/Orders/Orders.h
    )
add_library(Order STATIC ${ORDER_SRCS})
target_include_directories(Order PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Orders
    )

# ---------------------------------------------------------
# Orders Test
# ---------------------------------------------------------
add_executable(testRunnerOrders test/Orders/TEST_Orders.cpp)
target_link_libraries(testRunnerOrders gtest_main gmock_main Orders)
add_test(NAME OrdersTests COMMAND testRunnerOrders)

# ---------------------------------------------------------
# Player Test
# ---------------------------------------------------------
add_executable(testRunnerPlayer test/Player/TEST_Player.cpp)
target_link_libraries(testRunnerPlayer gtest_main gmock_main Player)
add_test(NAME PlayerTests COMMAND testRunnerPlayer)

# ---------------------------------------------------------
# Map Test
# ---------------------------------------------------------
add_executable(testRunnerMap test/Map/TEST_MapLoader.cpp)
target_link_libraries(testRunnerMap gtest_main gmock_main Player Map)
add_test(NAME MapTests COMMAND testRunnerMap)

# ---------------------------------------------------------
# Orders - DEMO
# ---------------------------------------------------------
add_executable(OrdersDriver src/Orders/OrdersDriver.cpp)
target_link_libraries(OrdersDriver Orders)

# ---------------------------------------------------------
# Player - DEMO
# ---------------------------------------------------------
add_executable(PlayerDriver src/Player/PlayerDriver.cpp)
target_link_libraries(PlayerDriver Player Map)

# ---------------------------------------------------------
# Map Driver - DEMO
# ---------------------------------------------------------
add_executable(MapDriver src/Map/MapDriver.cpp)
target_link_libraries(MapDriver Map)


# ---------------------------------------------------------
# Main
# ---------------------------------------------------------
add_executable(mainApp src/main.cpp)
target_link_libraries(mainApp Map Player)
