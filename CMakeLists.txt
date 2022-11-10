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
src/Orders/OrdersDriver.cpp
src/Orders/OrdersDriver.h

# Cards
src/Cards/CardsDriver.cpp
src/Cards/CardsDriver.h
src/Cards/Cards.cpp
src/Cards/Cards.h

# GameEngine
src/GameEngine/GameEngineDriver.cpp
src/GameEngine/GameEngineDriver.h
src/GameEngine/GameEngine.cpp
src/GameEngine/GameEngine.h

# CommandProcessing
src/GameEngine/Command/Command.cpp
src/GameEngine/Command/Command.h
src/GameEngine/Command/CommandProcessingDriver.cpp
src/GameEngine/Command/CommandProcessingDriver.h
src/GameEngine/Command/CommandProcessor.cpp
src/GameEngine/Command/CommandProcessor.h
src/GameEngine/CommandFile/FileCommandProcessorAdapter.cpp
src/GameEngine/CommandFile/FileCommandProcessorAdapter.h
src/GameEngine/CommandFile/FileLineReader.cpp
src/GameEngine/CommandFile/FileLineReader.h


)
add_library(Game STATIC ${GAME_LIB_SRCS})
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)



# ---------------------------------------------------------
# Main Driver
# ---------------------------------------------------------
add_executable(MainDriver src/main.cpp)
target_link_libraries(MainDriver Game)



# ---------------------------------------------------------
# Tests
# ---------------------------------------------------------

# Command (File) Test
add_executable(testRunnerCommand test/Command/TEST_Command.cpp)
target_link_libraries(testRunnerCommand gtest_main gmock_main Game)
add_test(NAME CommandTests COMMAND testRunnerCommand)

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