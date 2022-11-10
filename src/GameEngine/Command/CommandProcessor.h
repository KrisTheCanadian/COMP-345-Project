#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "Logger/LogObserver.h"
#include "GameEngine/GameEngine.h"

class Command;

class CommandProcessor: public Subject, ILoggable {

  protected:
    virtual std::string readCommand();
    void saveCommand(Command* c);

  private:
    //Store all user commands
    std::vector<Command*> commandCollection;

    // Object Owner
    GameEngine* game;

    //validate a user command
    Command *validate(const std::string &_userInput);

  public:

    //Constructors
    explicit CommandProcessor(GameEngine*);
    CommandProcessor(const CommandProcessor &c);

    void getCommand();
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
