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

void GameEngine::addPlayer(Player* player) {
  if(player == nullptr){
    throw std::runtime_error("GameEngine::Error | Cannot add player to game (nullptr)");
  }
  if(state < GE_Players_Added){
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
  MapLoader::load(path, this->map);
}
