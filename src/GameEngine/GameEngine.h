#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include "Player/Player.h"
#include "Map/Map.h"
#include "Logger/LogObserver.h"

class Player;
class Map;
class Deck;

// ----------------------------------------
// Public GameEngine State Enum
// ----------------------------------------
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

class GameEngine : public Subject, ILoggable {
private:
  // current state
  GameEngineState state = GE_Start;
  // Players
  unsigned int playerTurn = 0;
  std::vector<Player*> players;
  // Deck
  Deck* deck = nullptr;
  // Map
  Map* map = nullptr;
  // Logger
  LogObserver* logObserver = nullptr;

public:
  // ----------------------------------------
  // Constructors
  // ----------------------------------------
  GameEngine();
  explicit GameEngine(GameEngineState state);

  // ----------------------------------------
  // Modifications + setters
  // ----------------------------------------
  void setCurrentState(GameEngineState engineState);

  // ----------------------------------------
  // Destructor
  // ----------------------------------------
  ~GameEngine() override;

  // ----------------------------------------
  // add players to game
  // ----------------------------------------
  void addPlayer(Player* player);

  // ----------------------------------------
  // load game map
  // ----------------------------------------
  void loadMap(const std::string& path);

  // ----------------------------------------
  // convert current state to string
  // ----------------------------------------
  std::string getCurrentStateToString();

  // ----------------------------------------
  // convert current state to string
  // ----------------------------------------
  std::string stringToLog() override;

private:
  // player increment turn
  void nextPlayerTurn();

public:
  // getters
  std::vector<Player*>* getPlayers();
  Player* getCurrentPlayerTurn();
  Deck* getDeck();
  Map* getMap();
  LogObserver* getLogObserver();
  GameEngineState getCurrentState();
};