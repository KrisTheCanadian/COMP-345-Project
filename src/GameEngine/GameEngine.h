#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include "Player/Player.h"
#include "Map/Map.h"

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

class GameEngine {
private:
  // current state
  GameEngineState state = GE_Start;
  // Players
  unsigned int playerTurn = 0;
  std::vector<Player*> players;
  std::vector<std::string> commands = {"loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit"};
  // Deck
  Deck* deck = nullptr;
  // Map
  Map* map = nullptr;
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
  ~GameEngine();

  // ----------------------------------------
  // add players to game
  // ----------------------------------------
  void addPlayer(Player* player);

  // ----------------------------------------
  // creates and adds the player to the game
  // ----------------------------------------
  void addPlayer(const std::string& name);

  // ----------------------------------------
  // load game map
  // ----------------------------------------
  void loadMap(const std::string& path);

  // ----------------------------------------
  // Validate game map
  // ----------------------------------------
  bool validateMap();

  // ----------------------------------------
  // gameStart
  // ----------------------------------------
  void gameStart();

    // ----------------------------------------
    // initiates startup phase
    // ----------------------------------------
    //different method depending on command mode (command line/file)
private:void cStartupPhase();
        void fStartupPhase();

        //redirects to the appropriate startup method
public: void startupPhase(bool cmd);
        void printCommands();

  // ----------------------------------------
  // convert current state to string
  // ----------------------------------------
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