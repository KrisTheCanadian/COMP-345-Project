#pragma once
#include "GameEngine/GameEngine.h"
#include "Logger/LogObserver.h"
#include <iostream>
#include <sstream>

class GameEngine;
class ILogObserver;

class Command: public Subject, ILoggable{

private:
  std::string command;
  std::string effect;

  GameEngine* game = nullptr;

public:

  //Constructors
  explicit Command(std::string _command, GameEngine* gameEngine);
  Command(const Command &c);
  ~Command() override;

  //Getters & Setters
  void saveEffect(std::string effect);
  std::string getEffect();
  std::string getCommand();
  void setCommand(std::string _command);

  //Operator Overloading
  friend std::ostream & operator << (std::ostream &out, const Command &c);
  Command& operator=(const Command& other);

  // Logging
  std::string stringToLog() override;
};
