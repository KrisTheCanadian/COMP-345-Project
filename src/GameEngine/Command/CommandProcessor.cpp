#include "CommandProcessor.h"
#include "Command.h"
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

regex regexRuleLoadMap("loadmap .+.map$");
regex regexRulePlayerAdd("addplayer .+");

CommandProcessor::CommandProcessor(GameEngine* game) :game(game){
    commandCollection = {};
}

CommandProcessor::CommandProcessor(const CommandProcessor &c) : Subject(c) {
    commandCollection = {};
    for(auto i : c.commandCollection){
        commandCollection.push_back(new Command(*i));
    }
    this->game = c.game;
}

void CommandProcessor::getCommand(){
    string userInput = readCommand();
    Command* currentCommand = validate(userInput);
    saveCommand(currentCommand);
}

string CommandProcessor::readCommand(){
    string userInput;
    cout << "Please enter a command: " << endl;
    getline(cin, userInput);
    cout << endl;
    return userInput;
}

void CommandProcessor::saveCommand(Command* _currentCommand){
    commandCollection.push_back(_currentCommand);
    Subject::notify(this);
}

int CommandProcessor::getCurrentState(){
    return game->getCurrentState();
}

Command* CommandProcessor::validate(const string& _userInput){

    auto currentCommandObj = new Command(_userInput);
    currentCommandObj->attach((ILogObserver*)game->getLogObserver());
    GameEngineState current_game_state = game->getCurrentState();

    switch(current_game_state){
        case GE_Start:
            if (std::regex_match(_userInput, regexRuleLoadMap)){
                game->setCurrentState(GE_Map_Loaded);
                currentCommandObj->saveEffect("Map successfully loaded");
                return currentCommandObj;
            };
            break;

        case GE_Map_Loaded:
            if (_userInput == "validatemap"){
                game->setCurrentState(GE_Map_Validated);
                currentCommandObj->saveEffect("Map successfully validated");
                return currentCommandObj;
            };
            if (std::regex_match(_userInput, regexRuleLoadMap)){
                current_game_state = GE_Map_Loaded;
                currentCommandObj->saveEffect("Map successfully loaded");
                return currentCommandObj;
            }
            break;

        case GE_Map_Validated:
            if (std::regex_match(_userInput, regexRulePlayerAdd)){
                game->setCurrentState(GE_Players_Added);
                currentCommandObj->saveEffect("Player successfully added");
                return currentCommandObj;
            };
            break;

        case GE_Players_Added:
            if (std::regex_match(_userInput, regexRulePlayerAdd)){
                game->setCurrentState(GE_Players_Added);
                currentCommandObj->saveEffect("Player successfully added");
                return currentCommandObj;
            };
            if(_userInput == "gamestart"){
                game->setCurrentState(GE_Reinforcement);
                currentCommandObj->saveEffect("Game successfully started");
                return currentCommandObj;
            };
            break;

        case GE_Win:
            if (_userInput == "replay"){
                game->setCurrentState(GE_Start);
                currentCommandObj->saveEffect("Game successfully restarted");
                return currentCommandObj;
            };
            if(_userInput == "quit"){
                cout << "Quit";
            };
            break;
        case GE_Reinforcement:
          throw std::runtime_error("CommandProcessor::GE_Reinforcement Not Implemented Yet");
        case GE_Issue_Orders:
          throw std::runtime_error("CommandProcessor::GE_Issue_Orders Not Implemented Yet");
        case GE_Execute_Orders:
          throw std::runtime_error("CommandProcessor::GE_Issue_Orders Not Implemented Yet");
    }

    currentCommandObj->saveEffect("Invalid Command");
    return currentCommandObj;

}


void CommandProcessor::printCommandCollection(const std::vector<Command*>& collection){
    for(auto & i : collection){
        cout << (*i) << endl;
    }
    cout << "Current Game State: " << StateToString() << endl;
}

vector<Command*> CommandProcessor::getCommandCollection(){
    return commandCollection;
}

string CommandProcessor::StateToString() {
  switch (game->getCurrentState()) {
    case GE_Start:
        return "Start";
    case GE_Map_Loaded:
        return "Map Loaded";
    case GE_Map_Validated:
        return "Map Validated";
    case GE_Players_Added:
        return "Players Added";
    case GE_Reinforcement:
        return "Assign Reinforcement";
    case GE_Win:
        return "Win";
    case GE_Issue_Orders:
      return "Issue Orders";
    case GE_Execute_Orders:
      return "Execute Orders";
  }
  throw std::runtime_error("CommandProcessor::StateToString Assert:Invalid State");
}

ostream & operator << (ostream &out, const CommandProcessor &c)
{
  out << "Overloaded << operator for Command Processor?" << endl;
  return out;
}

CommandProcessor& CommandProcessor::operator=(const CommandProcessor &other) {
  if(this == &other){
      return *this;
  }

  this->commandCollection = other.commandCollection;

  return *this;
}

std::string CommandProcessor::stringToLog() {
  std::stringstream ss;
  ss << "COMMAND PROCESSOR: ";
  ss << "Saved command \"";
  ss << commandCollection.back()->getEffect();
  ss << "\"";
  return ss.str();
}