#include "Command.h"
#include <iostream>

using namespace std;


Command::Command(string _command){
    command = _command;
    effect = "Command has not been executed yet";
}

Command::Command(const Command &c){
    command = c.command;
    effect = c.effect;
}

void Command::saveEffect(string _effect){
    effect = _effect;
}

string Command::getEffect(){
    return effect;
}

string Command::getCommand(){
    return command;
}

void Command::setCommand(string _command){
    command = _command;
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

  return *this;
}