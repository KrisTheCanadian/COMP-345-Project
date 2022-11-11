#pragma once
#include <string>
#include <stdexcept>
#include <vector>
#include "Player/Player.h"
#include "Map/Map.h"
#include "Logger/LogObserver.h"
#include "CommandFile/FileCommandProcessorAdapter.h"
#include "CommandFile/FileLineReader.h"
#include "Command/Command.h"

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
  std::string fileName;
  Player* currentPlayerTurn;
  std::vector<Player*> players;

  std::vector<std::string> commands = {"loadmap <filename>", "validatemap", "addplayer <playername>", "gamestart", "replay", "quit"};

  // Deck
  Deck* deck = nullptr;

  // Map
  Map* map = nullptr;


  // Logger
  LogObserver* logObserver = nullptr;

  // Command Processor
  CommandProcessor* commandProcessor = nullptr;
  FileCommandProcessorAdapter* adapter = nullptr;
  FileLineReader* flr = nullptr;


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
  // ----------------------------------------
  // initiates startup phase for commands read from the console
  // ----------------------------------------
  void startupPhase();
  // check win state
  Player* checkWinState();
  void nextTurn(int& turn);

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
  // setters
  void setCurrentPlayer(Player* player);
  LogObserver* getLogObserver();
  CommandProcessor* getCommandProcessor();
};