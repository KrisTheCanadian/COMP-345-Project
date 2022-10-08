#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include "Player/Player.h"
#include "Map/Loader/MapLoader.h"

enum GameEngineState {
  GE_Start = 0,
  GE_Map_Loaded,
  GE_Map_Validated,
  GE_Players_Added,
  GE_Reinforcement,
  GE_Issue_Orders,
  GE_Execute_Orders,
  GE_Win
};

class GameEngine {
private:
  GameEngineState state = GE_Start;
  // Players
  unsigned int playerTurn = 0;
  std::vector<Player*> players;
  // Deck
  Deck* deck = nullptr;
  // Map
  Map* map = nullptr;
public:
  // Constructors
  GameEngine();
  explicit GameEngine(GameEngineState state);

  // Modifications + setters
  void setCurrentState(GameEngineState engineState);

  // Destructor
  ~GameEngine();

  // add players to game
  void addPlayer(Player* player);

  // load game map
  void loadMap(const std::string& path);

  // MISC
  std::string getCurrentStateToString();

private:
  // player increment turn
  void nextPlayerTurn();

public:
  // getters
  std::vector<Player*>* getPlayers();
  Player* getCurrentPlayerTurn();
  Deck* getDeck();
  Map* getMap();
  GameEngineState getCurrentState();
};