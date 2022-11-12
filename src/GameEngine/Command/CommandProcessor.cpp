#include "CommandProcessor.h"
#include "../GameEngine.h"

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

Command* CommandProcessor::getCommand(){
    string userInput = readCommand() ;
    Command* currentCommand = validate(userInput);
    saveCommand(currentCommand);
    return currentCommand;
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
    std::string strCommand = currentCommandObj->getCommand();

    switch(current_game_state){
        case GE_Start:
            if (std::regex_match(_userInput, regexRuleLoadMap)){
              size_t pos = strCommand.find(' ');
              std::string mapName = "res/" + MapLoader::trim(strCommand.substr(pos));
              try {
                game->loadMap(mapName);
              }
              catch(std::runtime_error err){
                cout<< err.what() << endl;
                break;
              }
              game->setCurrentState(GE_Map_Loaded);
              currentCommandObj->saveEffect("Map successfully loaded");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }
            break;

        case GE_Map_Loaded:
            if (_userInput == "validatemap"){

              try{
                game->validateMap();
              }
              catch(std::runtime_error err){
                cout<< err.what() << endl;
                game->setCurrentState(GE_Start);
              }

              game->setCurrentState(GE_Map_Validated);
              currentCommandObj->saveEffect("Map successfully validated");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }
            else if (std::regex_match(_userInput, regexRuleLoadMap)){
                cout << "Map already loaded" << endl;
            }
            break;

        case GE_Map_Validated:
            if (std::regex_match(_userInput, regexRulePlayerAdd)){

                size_t pos = strCommand.find(' ');
                std::string playerName = strCommand.substr(pos);
                new Player(game, new Hand());
                currentCommandObj->saveEffect("Player successfully added");
                game->setCurrentState(GE_Players_Added);
                cout << currentCommandObj->getEffect() << playerName << endl;
                return currentCommandObj;
            }
            break;

        case GE_Players_Added:
            if (std::regex_match(_userInput, regexRulePlayerAdd)){

              try {
                game->validateMaxPlayers();
              }
              catch(std::runtime_error err){
                cout << err.what() << endl;
                break;
              }

              size_t pos = strCommand.find(' ');
              std::string playerName = strCommand.substr(pos);
              new Player(game, new Hand());
              currentCommandObj->saveEffect("Player successfully added");
              cout << currentCommandObj->getEffect() << playerName << endl;
              return currentCommandObj;
            }
            else if(_userInput == "gamestart"){

              try {
                game->validateMinPlayers();
              }
              catch(std::runtime_error err){
                cout << err.what() << endl;
                break;
              }

              game->setCurrentState(GE_Reinforcement);
              currentCommandObj->saveEffect("Game successfully started");
              return currentCommandObj;
            }
            break;

        case GE_Win:
            if (_userInput == "replay"){
                game->setCurrentState(GE_Start);
                currentCommandObj->saveEffect("Game successfully restarted");
                return currentCommandObj;
            }
            if(_userInput == "quit"){
                cout << "Quit";
            }
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