#pragma once
#include <iostream>
#include <vector>
#include "./GameEngine/GameEngine.h"

class Command;

class CommandProcessor{

    protected:
      virtual std::string readCommand();
      void saveCommand(Command* c);

    private:
    
        //Store all user commands
        std::vector<Command*> commandCollection;

        //validate a user command
        Command* validate(std::string userInputCommand);

    public:

        //Constructors
        CommandProcessor();
        CommandProcessor(const CommandProcessor &c);


        void getCommand();
        int getCurrentState();

        
        //Functions for CommandProcessorDriver.cpp
        void printInvalidCommand(std::string& command);
        void printCommandCollection(std::vector<Command*> commandCollection);
        std::vector<Command*> getCommandCollection();
        std::string StateToString();

        //Operator Overloading
        friend std::ostream & operator << (std::ostream &out, const CommandProcessor &c);
        CommandProcessor& operator=(const CommandProcessor& other);
};