#include "GameEngine.h"


void GameEngine::setCurrentState(GameEngineState engineState) {
  this->state = engineState;
}

GameEngineState GameEngine::getCurrentState() {
  return this->state;
}

GameEngine::GameEngine(GameEngineState state) {
  this->state = state;
  this->deck = new Deck(this);
  this->map = new Map(this);
}

void GameEngine::startupPhase(bool cmd) {
    if(cmd){cStartupPhase();}
    else if(!cmd){fStartupPhase();}
    else cout << "Please chose an input mode!";

}

void GameEngine::fStartupPhase() {
    std::string command;
    cout << "Welcome to the startup phase of the game! Here are the list of commands available to you: " << endl;
    printCommands();
    cout << "Please enter the command you wish to use: ";
    cin >> command;

    while(!std::equal(command.begin(), command.end(),"quit")){
        std::vector<std::string>::iterator it = std::find(commands.begin(), commands.end(),command);
        int cmdInd = std::distance(commands.begin(), it);
        if(commands.at(cmdInd) != command) {
            cout << "Please enter a valid command!" << endl;
            return;
        }
        switch(cmdInd){

        }
    }
}

void GameEngine::cStartupPhase() {


}

void GameEngine::printCommands() {
    for(string cmd : commands){
        cout << cmd << ((std::equal(cmd.begin(), cmd.end(),"loadmap"))?" <filename>": "" )<< ((std::equal(cmd.begin(), cmd.end(),"addplayer"))?" <playername>": "" ) << endl;
    }
}

std::string GameEngine::getCurrentStateToString() {
  switch (this->state) {
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
    case GE_Issue_Orders:
      return "Issue Orders";
    case GE_Execute_Orders:
      return "Execute Orders";
    case GE_Win:
      return "Win";
  }

  throw std::runtime_error("Invalid State");
}

void GameEngine::nextPlayerTurn() {
  playerTurn++;
  playerTurn %= players.size();
}

std::vector<Player *> *GameEngine::getPlayers() {
  return &this->players;
}

Player* GameEngine::getCurrentPlayerTurn() {
  return players.at(playerTurn);
}

Deck *GameEngine::getDeck() {
  return this->deck;
}

Map* GameEngine::getMap() {
  return this->map;
}

void GameEngine::addPlayer(const std::string& name) {
  auto* p = new Player(this, new Hand());
//  this->players.push_back(p);
}

void GameEngine::addPlayer(Player* player) {
  if(player == nullptr){
    throw std::runtime_error("GameEngine::Error | Cannot add player to game (nullptr)");
  }
  if(state > GE_Players_Added){
    throw std::runtime_error("GameEngine::ASSERT | Cannot add player to game. Game is already in progress.");
  }
  this->players.push_back(player);
}

GameEngine::~GameEngine() {
  delete deck;
  delete map;

  for(auto player : players){
    delete player;
  }
}

GameEngine::GameEngine() {
  this->map = new Map(this);
  this->deck = new Deck(this);
}

void GameEngine::loadMap(const std::string& path) {
  if(state >= GE_Map_Loaded && state != GE_Win){ throw runtime_error("Map is already loaded."); }
  MapLoader::load(path, this->map);
  state = GE_Map_Loaded;
}

bool GameEngine::validateMap() {
  if(state != GE_Map_Loaded){ throw runtime_error("ASSERT: Cannot Validate Map Before Loading Map."); }
  if(map == nullptr){ throw runtime_error("ASSERT: Map is null."); }
  state = GE_Map_Validated;
  return map->validate();
}

void GameEngine::gameStart() {
  // Loading the map
  while(this->state != GE_Map_Loaded){
    std::string mapPath;
    std::cout << "Enter the path for the map: ";
    std::cin >> mapPath;
    std::cout << std::endl;
    try{
      loadMap(mapPath);
    } catch (const runtime_error& error){
      std::cout << "Error: " << error.what() << endl;
      std::cout << "Please Try Again." << error.what() << endl;
    }

    std::cout << "Validating Map..." << std::endl;
    std::cout << "Map is " << (validateMap() ? "Valid":"Invalid") << std::endl;
  }



}
