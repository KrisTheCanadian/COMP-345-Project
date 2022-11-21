#include <memory>
#include <gtest/gtest.h>
#include "GameEngine/GameEngine.h"

// Logging GameState
TEST(LoggerTestSuite, GameStateChange){
    // mocking argc and argv
    int argc = 1;
    char* argv[] = {(char*)"-console"};

    auto gameEngine = new GameEngine(argc, argv, true);
    std::string output;
    std::fstream file;
    file.open("gamelog.txt", std::ios::in | std::ios::out | std::ios::trunc);

    // TEST GAME STATE CHANGE
    gameEngine->setCurrentState(GE_Map_Loaded);

    std::string line;
    if ( file.is_open() ) {
        while(file){
            std::getline (file, line);
            output += line;
        }
    }
    else {
        std::cout << "Couldn't open file\n";
    }

    EXPECT_TRUE(output == "GAME ENGINE: State transition to Map Loaded");
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}