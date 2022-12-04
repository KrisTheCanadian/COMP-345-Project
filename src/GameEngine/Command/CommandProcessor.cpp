#include "CommandProcessor.h"
#include "../GameEngine.h"
#include <algorithm>

using namespace std;

regex regexRuleLoadMap("loadmap .+.map$");
regex regexRulePlayerAdd("addplayer .+");

vector<string> split(string s, string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  string token;
  vector<string> res;

  while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(s.substr(pos_start));
  return res;
}

CommandProcessor::CommandProcessor(GameEngine* game, int argc, char** argv) : game(game) {
  commandCollection = {};
  // add all program arguments to a raw string
  for(int i = 0; i < argc; i++){ rawCommands.emplace_back(argv[i]); }
  Subject::attach((ILogObserver*)game->getLogObserver());
}

CommandProcessor::CommandProcessor(const CommandProcessor &c) : Subject(c) {
    commandCollection = {};
    for(auto i : c.commandCollection){
        commandCollection.push_back(new Command(*i));
    }
    this->rawCommands = c.rawCommands;
    this->game = c.game;
    Subject::attach((ILogObserver*)game->getLogObserver());
}

Command* CommandProcessor::getCommand(){
    string userInput = readCommand() ;
    Command* currentCommand = validate(userInput);
    saveCommand(currentCommand);
    return currentCommand;
}

string CommandProcessor::readCommand(){
    string userInput;
    cout << "Please enter a command: ";
    getline(cin, userInput);
    std::cout << std::endl;
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

    auto currentCommandObj = new Command(_userInput, game);
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
              catch(std::runtime_error& err){
                cout<< err.what() << endl;
                break;
              }
              game->setCurrentState(GE_Map_Loaded);
              currentCommandObj->saveEffect("Map successfully loaded");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }

            else if (_userInput.substr(0, _userInput.find(' ')) == "tournament"){
              TournamentFunctionInput(_userInput);
              try {
                game->validateTournament();
              }
              catch(std::runtime_error& err){
                cout<< err.what() << endl;
                game->setCurrentState(GE_Start);
                break;
              }
              game->setCurrentState(GE_Tournament);
              currentCommandObj->saveEffect("Tournament started");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }

            break;


        case GE_Map_Loaded:
            if (_userInput == "validatemap"){

              try{
                game->validateMap();
              }
              catch(std::runtime_error& err){
                cout<< err.what() << endl;
                game->setCurrentState(GE_Start);
                break;
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

                // trim spacing
                std::string::iterator end_pos = std::remove(playerName.begin(), playerName.end(), ' ');
                playerName.erase(end_pos, playerName.end());

                if(game->isTesting()){
                  cout << "Game Engine is in testing mode, player will be added automatically as Aggressive." << endl;
                  new Player(game, new Hand(), playerName, "Random");
                } else {
                  new Player(game, new Hand(), playerName, "Human");
                }
                currentCommandObj->saveEffect("Player" + playerName + " has been added successfully");
                game->setCurrentState(GE_Players_Added);
                cout << currentCommandObj->getEffect() << endl;
                return currentCommandObj;
            }
            break;

        case GE_Players_Added:
            if (std::regex_match(_userInput, regexRulePlayerAdd)){

              try {
                game->validateMaxPlayers();
              }
              catch(std::runtime_error& err){
                cout << err.what() << endl;
                break;
              }

              size_t pos = strCommand.find(' ');
              std::string playerName = strCommand.substr(pos);

              // trim spacing
              std::string::iterator end_pos = std::remove(playerName.begin(), playerName.end(), ' ');
              playerName.erase(end_pos, playerName.end());

              if(game->isTesting()){
                cout << "Game Engine is in testing mode, player will be added automatically as Aggressive." << endl;
                new Player(game, new Hand(), playerName, "Random");
              } else {
                new Player(game, new Hand(), playerName, "Human");
              }

              currentCommandObj->saveEffect("Player" + playerName + " has been added successfully");
              cout << currentCommandObj->getEffect() << endl;
              return currentCommandObj;
            }
            else if(_userInput == "gamestart"){

              // Check for minimum 2 players before starting
              try {
                game->validateMinPlayers();
              }
              catch(std::runtime_error& err){
                cout << err.what() << endl;
                break;
              }

              game->distributeTerritories();
              cout<< "Territories distributed."<<endl;

              game->playerOrder();
              cout<< "Order of play of players determined."<<endl;

              // initialize deck
              game->getDeck()->create_deck();

              try{
                for(Player* player : *game->getPlayers()){
                  player->setReinforcementPool(50);
                  game->setCurrentPlayer(player);
                  Hand &hand = *player->getHand();
                  game->getDeck()->draw(hand);
                  game->getDeck()->draw(hand);
                }
              }
              catch(std::runtime_error& err){
                cout << err.what() <<endl;
                break;
              }

              game->setCurrentState(GE_Reinforcement);
              currentCommandObj->saveEffect("Game successfully started");
              cout << currentCommandObj->getEffect() << endl;
              game->mainGameLoop();
              return currentCommandObj;
            }
            break;

        case GE_Win:
            if (_userInput == "replay"){
                game->setCurrentState(GE_Start);
                currentCommandObj->saveEffect("Game successfully restarted");
                cout << currentCommandObj->getEffect() << "!\n" << endl;
                return currentCommandObj;
            }
            else if(_userInput == "quit"){
                cout << "Quitting game";
                exit(0);
            }
            break;
        case GE_Reinforcement:
          throw std::runtime_error("CommandProcessor::GE_Reinforcement Not Implemented Yet");
        case GE_Issue_Orders:
          throw std::runtime_error("CommandProcessor::GE_Issue_Orders Not Implemented Yet");
        case GE_Execute_Orders:
          throw std::runtime_error("CommandProcessor::GE_Execute_Orders Not Implemented Yet");
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
    case GE_Tournament:
      return "Tournament";
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
  Subject::attach((ILogObserver*)game->getLogObserver());
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
std::vector<std::string> *CommandProcessor::getRawCommands() {
  return &rawCommands;
}
CommandProcessor::~CommandProcessor() {
  if(game){
    Subject::detach((ILogObserver* )game->getLogObserver());
  }
}

void CommandProcessor::TournamentFunctionInput(string input) {
  vector<string> enteredTournamentString = split(input, " ");
  int i = 1; // skip the first word "tournament"
  while (i < enteredTournamentString.size()) {
    if (enteredTournamentString[i] == "-M") {
      while (enteredTournamentString[++i] != "-P") {
        game->allMaps.push_back(enteredTournamentString[i]);
      }
    }
    else if (enteredTournamentString[i] == "-P") {
      while (enteredTournamentString[++i] != "-G") {
        game->allPlayerStrategies.push_back(enteredTournamentString[i]);
      }

    }
    else if (enteredTournamentString[i] == "-G") {
      i++;
      string temp;
      temp = enteredTournamentString[i++];
      if (!isdigit(temp[0])) {
        cout << "The number of games has to be a digit" << endl;
        exit(0);
      }
      game->numberOfGames = stoi(temp);

    }
    else if (enteredTournamentString[i] == "-D") {
      i++;
      string temp;
      temp = enteredTournamentString[i++];
      if (!isdigit(temp[0])) {
        cout << "The max number of turns has to be a digit" << endl;
        exit(0);
      }
      game->maxNumberOfTurns = stoi(temp);
    }
  }
}

void CommandProcessor::FileTournamentFunctionInput(string input) {

  std::ifstream temp(input);
  int numberOfTournaments = 0;
  int tournamentsPlayed = 0;
  std::string lineCounter;
  while (std::getline(temp , lineCounter)){
    numberOfTournaments++;
  }

  if(numberOfTournaments > 1){
    game->multipleTournaments = true;
  }

  temp.close();
  ifstream ifs;
  string line;
  ifs.open(input);

  if(!ifs.is_open()){
    throw std::runtime_error("File already open");
  }
  while(getline(ifs, line)){
    TournamentFunctionInput(line);
    game->validateTournament();
    game->runTournament();
    tournamentsPlayed++;
    std::cout << std::endl;
    if(tournamentsPlayed < numberOfTournaments){
      std::cout << "------- NEXT TOURNAMENT STARTING NOW! -------" << std::endl;
    }
  }
  ifs.close();
}