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
# Game Library
# ---------------------------------------------------------

set(GAME_LIB_SRCS
    # Map
    src/Map/Map.cpp
    src/Map/Map.h
    src/Map/Loader/MapLoader.cpp
    src/Map/Loader/MapLoader.h
    src/Map/Territory/Territory.cpp
    src/Map/Territory/Territory.h
    src/Map/Continent/Continent.cpp
    src/Map/Continent/Continent.h
    src/Map/MapDriver.cpp
    src/Map/MapDriver.h

    # Player
    src/Player/Player.cpp
    src/Player/Player.h
    src/Player/PlayerDriver.cpp
    src/Player/PlayerDriver.h

    # Orders
    src/Orders/Orders.cpp
    src/Orders/Orders.h
    src/Orders/OrdersList/OrdersList.cpp
    src/Orders/OrdersList/OrdersList.h
    src/Orders/OrderTypes/Advance/Advance.h
    src/Orders/OrderTypes/Advance/Advance.cpp
    src/Orders/OrderTypes/Airlift/Airlift.h
    src/Orders/OrderTypes/Airlift/Airlift.cpp
    src/Orders/OrderTypes/Blockade/Blockade.h
    src/Orders/OrderTypes/Blockade/Blockade.cpp
    src/Orders/OrderTypes/Bomb/Bomb.h
    src/Orders/OrderTypes/Bomb/Bomb.cpp
    src/Orders/OrderTypes/Deploy/Deploy.h
    src/Orders/OrderTypes/Deploy/Deploy.cpp
    src/Orders/OrderTypes/Negotiate/Negotiate.h
    src/Orders/OrderTypes/Negotiate/Negotiate.cpp
    src/Orders/OrdersDriver.cpp
    src/Orders/OrdersDriver.h
    src/Orders/UserInputOrder/UserInputOrder.cpp
    src/Orders/UserInputOrder/UserInputOrder.h

    # Cards
    src/Cards/CardsDriver.cpp
    src/Cards/CardsDriver.h
    src/Cards/Cards.cpp
    src/Cards/Cards.h
    src/Cards/Deck/Deck.cpp
    src/Cards/Deck/Deck.h
    src/Cards/Hand/Hand.cpp
    src/Cards/Hand/Hand.h

    # GameEngine
    src/GameEngine/GameEngineDriver.cpp
    src/GameEngine/GameEngineDriver.h
    src/GameEngine/GameEngine.cpp
    src/GameEngine/GameEngine.h
)
add_library(Game STATIC ${GAME_LIB_SRCS})
target_include_directories(Game PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)



# ---------------------------------------------------------
# Main Driver
# ---------------------------------------------------------
add_executable(MainDriver src/main.cpp)
target_link_libraries(MainDriver Game)



# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------

# Game Engine Test
add_executable(testRunnerGameEngine test/GameEngine/TEST_GameEngine.cpp)
target_link_libraries(testRunnerGameEngine gtest_main gmock_main Game)
add_test(NAME GameEngineTests COMMAND testRunnerGameEngine)

# Card Test
add_executable(testRunnerCards test/Cards/TEST_Cards.cpp)
target_link_libraries(testRunnerCards gtest_main gmock_main Game)
add_test(NAME CardsTests COMMAND testRunnerCards)

# Orders Test
add_executable(testRunnerOrders test/Orders/TEST_Orders.cpp)
target_link_libraries(testRunnerOrders gtest_main gmock_main Game)
add_test(NAME OrdersTests COMMAND testRunnerOrders)

# Player Test
add_executable(testRunnerPlayer test/Player/TEST_Player.cpp)
target_link_libraries(testRunnerPlayer gtest_main gmock_main Game)
add_test(NAME PlayerTests COMMAND testRunnerPlayer)

# Map Test
add_executable(testRunnerMap test/Map/TEST_MapLoader.cpp)
target_link_libraries(testRunnerMap gtest_main gmock_main Game)
add_test(NAME MapTests COMMAND testRunnerMap)



# ---------------------------------------------------------
# Maps
# ---------------------------------------------------------

# When Res is modified, rerun cmake (to copy new files to binary out)
file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
