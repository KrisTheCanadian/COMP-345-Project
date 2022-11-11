#include <memory>
#include <gtest/gtest.h>
#include "GameEngine/CommandFile/FileCommandProcessorAdapter.h"
#include "GameEngine/CommandFile/FileLineReader.h"
#include "GameEngine/GameEngine.h"

TEST(FileCommandTestSuite, CommandFile2_invalid){

    int final_state;
    auto game = new GameEngine;

    FileLineReader flr;
    FileCommandProcessorAdapter adapter(game);
    adapter.commandLineToFile(&flr);
    flr.setFile("../res/TestCommand2_invalid.txt");

    while(!flr.getReadComplete()){
        adapter.getCommand();
    }

    final_state = adapter.getCurrentState();


    EXPECT_FALSE(final_state == 4);
}

TEST(FileCommandTestSuite, CommandFile3_invalid){

    auto game = new GameEngine;
    FileLineReader flr;
    FileCommandProcessorAdapter adapter(game);
    adapter.commandLineToFile(&flr);
    flr.setFile("../res/TestCommand3_invalid.txt");

    while(!flr.getReadComplete()){
        adapter.getCommand();
    }

    int final_state = adapter.getCurrentState();

    EXPECT_FALSE(final_state == 4);
}



TEST(FileCommandTestSuite, CommandFile5_invalid){

    auto game = new GameEngine;
    FileLineReader flr;
    FileCommandProcessorAdapter adapter(game);
    adapter.commandLineToFile(&flr);
    flr.setFile("../res/TestCommand5_invalid_format.txt");

    while(!flr.getReadComplete()){
        adapter.getCommand();
    }

    int final_state = adapter.getCurrentState();
    EXPECT_FALSE(final_state == 4);
}


TEST(FileCommandTestSuite, CommandFile1_Valid){

    auto game = new GameEngine;
    FileLineReader flr;
    FileCommandProcessorAdapter adapter(game);
    adapter.commandLineToFile(&flr);
    flr.setFile("../res/TestCommand1_valid.txt");

    while(!flr.getReadComplete()){
        adapter.getCommand();
    }

    int final_state = adapter.getCurrentState();

    EXPECT_TRUE(final_state == 4);
}

TEST(FileCommandTestSuite, CommandFile4_valid){

    auto game = new GameEngine;
    FileLineReader flr;
    FileCommandProcessorAdapter adapter(game);
    adapter.commandLineToFile(&flr);
    flr.setFile("../res/TestCommand4_valid.txt");

    while(!flr.getReadComplete()){
        adapter.getCommand();
    }

    int final_state = adapter.getCurrentState();

    EXPECT_TRUE(final_state == 4);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}