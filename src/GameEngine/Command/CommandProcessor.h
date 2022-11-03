#pragma once
#include <iostream>
#include <vector>

class Command;

//Simulating a game engine
//THIS WILL BE DELETED ONCE PART 2 IS COMPLETED
enum GameEngineState {
  GE_Start = 0,
  GE_Map_Loaded,
  GE_Map_Validated,
  GE_Players_Added,
  GE_Reinforcement,
  GE_Win
};

class CommandProcessor{

    private:
        //Read from CLI
        std::string readCommand();

        //Save to commandCollection
        void saveCommand(Command* c);

        //Store all user commands
        std::vector<Command*> commandCollection;

        //validate a user command
        Command* validate(std::string userInputCommand);

    public:

        //Constructors
        CommandProcessor();
        CommandProcessor(const CommandProcessor &c);


        void getCommand();
        
        //Functions for CommandProcessorDriver.cpp
        void printInvalidCommand(std::string& command);
        void printCommandCollection(std::vector<Command*> commandCollection);
        std::vector<Command*> getCommandCollection();
        std::string StateToString();
};