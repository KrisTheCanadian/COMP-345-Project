#include <memory>
#include <gtest/gtest.h>
#include "GameEngine/CommandFile/FileCommandProcessorAdapter.h"
#include "GameEngine/CommandFile/FileLineReader.h"

TEST(FileCommandTestSuite, CommandFile1_Valid){

    FileLineReader flr;
    FileCommandProcessorAdapter adapter;
    adapter.commandLineToFile(&flr);
    flr.setFile("../res/TestCommand1_valid.txt");

    while(!flr.getReadComplete()){
        adapter.getCommand();
    }

    int final_state = adapter.getCurrentState();

    EXPECT_TRUE(final_state == 4);
}

TEST(FileCommandTestSuite, CommandFile2_invalid){

    FileLineReader flr;
    FileCommandProcessorAdapter adapter;
    adapter.commandLineToFile(&flr);
    flr.setFile("../res/TestCommand2_invalid.txt");

    while(!flr.getReadComplete()){
        adapter.getCommand();
    }

    int final_state = adapter.getCurrentState();

    EXPECT_FALSE(final_state == 4);
}

TEST(FileCommandTestSuite, CommandFile3_invalid){

    FileLineReader flr;
    FileCommandProcessorAdapter adapter;
    adapter.commandLineToFile(&flr);
    flr.setFile("../res/TestCommand3_invalid.txt");

    while(!flr.getReadComplete()){
        adapter.getCommand();
    }

    int final_state = adapter.getCurrentState();

    EXPECT_FALSE(final_state == 4);
}

TEST(FileCommandTestSuite, CommandFile4_valid){

    FileLineReader flr;
    FileCommandProcessorAdapter adapter;
    adapter.commandLineToFile(&flr);
    flr.setFile("../res/TestCommand4_valid.txt");

    while(!flr.getReadComplete()){
        adapter.getCommand();
    }

    int final_state = adapter.getCurrentState();

    EXPECT_TRUE(final_state == 4);
}

TEST(FileCommandTestSuite, CommandFile5_invalid){

    FileLineReader flr;
    FileCommandProcessorAdapter adapter;
    adapter.commandLineToFile(&flr);
    flr.setFile("../res/TestCommand5_invalid_format.txt");

    while(!flr.getReadComplete()){
        adapter.getCommand();
    }

    int final_state = adapter.getCurrentState();

    EXPECT_FALSE(final_state == 4);
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}