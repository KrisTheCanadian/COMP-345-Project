#pragma once
#include "Player/Player.h"
#include "Map/Map.h"
#include "Command/CommandProcessor.h"
#include "CommandFile/FileCommandProcessorAdapter.h"

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
  unsigned int playerTurn = 0;
  std::string fileName;
  std::vector<Player*> players;

  std::vector<std::string> commands = {"loadmap <filename>", "validatemap", "addplayer <playername>", "gamestart", "replay", "quit"};

  // Deck
  Deck* deck = nullptr;

  // Map
  Map* map = nullptr;


  FileCommandProcessorAdapter* adapter;
  FileLineReader* flr;
  CommandProcessor* commandProcessor;

  // Logger
  LogObserver* logObserver = nullptr;

  // Command Processor
  CommandProcessor* commandProcessor = nullptr;


public:
   bool isConsole;
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
  // Validate game map
  // ----------------------------------------
  bool validateMap();

  // ----------------------------------------
  // gameStart
  // ----------------------------------------
  void gameStart();

  // ----------------------------------------
  // convert current state to string
  // ----------------------------------------
  std::string stringToLog() override;

private:
    // ----------------------------------------
    // initiates startup phase for commands read from the console
    // ----------------------------------------
    void startupPhase();

    // ----------------------------------------
    // prints all the commands available for the user to use
    // ----------------------------------------
    void printCommands();

    // ----------------------------------------
    // checks whether a command is valid or not
    // ----------------------------------------
    bool isValid(const std::string strCommand);

    // ----------------------------------------
    // distributes all territories evenly between the players
    // ----------------------------------------
    void distributeTerritories();

    // ----------------------------------------
    // determines a random order of play for players
    // ----------------------------------------
    void playerOrder();

    // ----------------------------------------
    // convert current state to string
    // ----------------------------------------
    std::string getCurrentStateToString();

public:
    // ----------------------------------------
    // redirects to the appropriate startup method
    // ----------------------------------------
    void preStartupPhase();

    // getters
    std::vector<Player*>* getPlayers();
    Player* getCurrentPlayerTurn();
    Deck* getDeck();
    Map* getMap();
    GameEngineState getCurrentState();
    
  LogObserver* getLogObserver();
  CommandProcessor* getCommandProcessor();
};