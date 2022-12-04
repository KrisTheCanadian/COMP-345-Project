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

  // command line arguments
  std::vector<std::string> rawCommands;

private:

  virtual std::string readCommand();
  void saveCommand(Command* c);
  Command* validate(const std::string& _userInput);

public:
    void FileTournamentFunctionInput(std::string input);
    void TournamentFunctionInput(std::string);

  //Constructors
  explicit CommandProcessor(GameEngine*, int argc,char* argv[]);
  CommandProcessor(const CommandProcessor &c);

  ~CommandProcessor() override;

  //getters and setters
  Command* getCommand();
  int getCurrentState();

  std::vector<std::string>* getRawCommands();
  bool validateTournament();

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
