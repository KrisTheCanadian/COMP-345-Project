#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include "Logger/LogObserver.h"

class Command;

class CommandProcessor: public Subject, ILoggable {

  private:
    //Store all user commands
    std::vector<Command*> commandCollection;

    // Object Owner
    GameEngine* game;

  private:

    virtual std::string readCommand();
    void saveCommand(Command* c);
    Command* validate(std::string userInputCommand);

  public:

    //Constructors
    explicit CommandProcessor(GameEngine*);
    CommandProcessor(const CommandProcessor &c);

    Command* getCommand();
    int getCurrentState();

    //Functions for CommandProcessorDriver.cpp
    void printCommandCollection(const std::vector<Command *> &collection);
    std::vector<Command*> getCommandCollection();
    std::string StateToString();

    //Operator Overloading
    friend std::ostream & operator << (std::ostream &out, const CommandProcessor &c);
    CommandProcessor& operator=(const CommandProcessor& other);

    // Logging
    std::string stringToLog() override;


};
