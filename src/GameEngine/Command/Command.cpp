#include "Command.h"
#include <iostream>
#include <utility>

using namespace std;


Command::Command(string _command, GameEngine* gameEngine){
  this->game = gameEngine;
  command = std::move(_command);
  effect = "Command has not been executed yet";
  Subject::attach((ILogObserver*)game->getLogObserver());
}

Command::Command(const Command &c) : Subject(c) {
  game = c.game;
  command = c.command;
  effect = c.effect;
  Subject::attach((ILogObserver*)game->getLogObserver());
}

void Command::saveEffect(string _effect){
    effect = std::move(_effect);
    Subject::notify(this);
}

string Command::getEffect(){
    return effect;
}

string Command::getCommand(){
    return command;
}

void Command::setCommand(string _command){
    command = std::move(_command);
}

ostream & operator << (ostream &out, const Command &c)
{
    out << c.command << " : " << c.effect << endl;
    return out;
}

Command& Command::operator=(const Command &other) {
  if(this == &other){
    return *this;
  }

  this->command = other.command;
  this->effect = other.effect;
  Subject::attach((ILogObserver*)game->getLogObserver());

  return *this;
}

std::string Command::stringToLog() {
  std::stringstream ss;
  ss << "COMMAND: ";
  ss << "Saved Effect \"";
  ss << getEffect();
  ss << "\"";
  return ss.str();
}
Command::~Command() {
  if(game){
    Subject::detach((ILogObserver* )game->getLogObserver());
  }
}
