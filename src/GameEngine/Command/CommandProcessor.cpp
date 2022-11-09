#include "CommandProcessor.h"
#include "Command.h"
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

regex regexRuleLoadMap("loadmap .+.map$");
regex regexRulePlayerAdd("addplayer .+");

CommandProcessor::CommandProcessor(GameEngine* gameEngine){
    commandCollection = {};
    this->gameEngine = gameEngine;
}

CommandProcessor::CommandProcessor(const CommandProcessor &c){
    commandCollection = {};
    for(int i = 0; i < c.commandCollection.size(); i++){
        commandCollection.push_back(new Command(*c.commandCollection[i]));
    }
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
    return gameEngine->getCurrentState();
}

Command* CommandProcessor::validate(string _userInput){

    Command *currentCommandObj = new Command(_userInput);
    currentCommandObj->attach((ILogObserver*)gameEngine->getLogObserver());
    GameEngineState current_game_state = gameEngine->getCurrentState();

    switch(current_game_state){
        case GE_Start:
            if (std::regex_match(_userInput, regexRuleLoadMap)){
                gameEngine->setCurrentState(GE_Map_Loaded);
                currentCommandObj->saveEffect("Map successfully loaded");
                return currentCommandObj;
            };
            break;

        case GE_Map_Loaded:
            if (_userInput == "validatemap"){
                gameEngine->setCurrentState(GE_Map_Validated);
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
                gameEngine->setCurrentState(GE_Players_Added);
                currentCommandObj->saveEffect("Player successfully added");
                return currentCommandObj;
            };
            break;

        case GE_Players_Added:
            if (std::regex_match(_userInput, regexRulePlayerAdd)){
                gameEngine->setCurrentState(GE_Players_Added);
                currentCommandObj->saveEffect("Player successfully added");
                return currentCommandObj;
            };
            if(_userInput == "gamestart"){
                gameEngine->setCurrentState(GE_Reinforcement);
                currentCommandObj->saveEffect("Game successfully started");
                return currentCommandObj;
            };
            break;

        case GE_Win:
            if (_userInput == "replay"){
                gameEngine->setCurrentState(GE_Start);
                currentCommandObj->saveEffect("Game successfully restarted");
                return currentCommandObj;
            };
            if(_userInput == "quit"){
                cout << "Quit";
            };
            break;
    }

    currentCommandObj->saveEffect("Invalid Command");
    return currentCommandObj;

}


void CommandProcessor::printCommandCollection(std::vector<Command*> commandCollection){
    for(int i = 0; i < commandCollection.size(); i++){
        cout << (*commandCollection[i]) << endl;
    }
    cout << "Current Game State: " << StateToString() << endl;
}

vector<Command*> CommandProcessor::getCommandCollection(){
    return commandCollection;
}

string CommandProcessor::StateToString() {
    switch (gameEngine->getCurrentState()) {
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
    }
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
