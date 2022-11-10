#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include "Player/Player.h"
#include "Map/Map.h"
#include "Logger/LogObserver.h"
#include "GameEngine/Command/CommandProcessor.h"

class Player;
class Map;
class Deck;
class CommandProcessor;

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
  Player* currentPlayerTurn;
  std::vector<Player*> players;

  // Deck
  Deck* deck = nullptr;

  // Map
  Map* map = nullptr;

  // Logger
  LogObserver* logObserver = nullptr;

  // Command Processor
  CommandProcessor* commandProcessor = nullptr;

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

    // ----------------------------------------
    // reinforcement phase
    // ----------------------------------------
    void reinforcementPhase();

  // ----------------------------------------
  // Issuing Orders Phase
  // ----------------------------------------
  void issueOrdersPhase();

  // ----------------------------------------
  // Execute Orders Phase
  // ----------------------------------------
  void executeOrdersPhase();

  // ----------------------------------------
  // Main Game Loop
  // ----------------------------------------
  void mainGameLoop();

  // ----------------------------------------
  // add players to game (THIS IS DONE AUTOMATICALLY IN PLAYER CONSTRUCTOR)
  // ----------------------------------------
  void addPlayer(Player* player);

private:

  // check win state
  Player* checkWinState();
  void nextTurn(int& turn);

public:
  // getters
  std::vector<Player*>* getPlayers();
  Player* getCurrentPlayerTurn();
  Deck* getDeck();
  Map* getMap();
  LogObserver* getLogObserver();
  CommandProcessor* getCommandProcessor();
  GameEngineState getCurrentState();
};