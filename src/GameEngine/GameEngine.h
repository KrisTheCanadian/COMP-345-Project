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
  std::string fileName;
  Player* currentPlayerTurn = nullptr;
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

  // CL Args
  int argc;
  char** argv;

  // testing
  bool testing = false;


public:
  // ----------------------------------------
  // Constructors
  // ----------------------------------------
  GameEngine(int argc, char** argv, bool testing = false);
  explicit GameEngine(GameEngineState state, int argc, char** argv, bool testing = false);

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
  // convert current state to string
  // ----------------------------------------
  std::string stringToLog() override;

  // ----------------------------------------
  // initiates startup phase for commands read from the console
  // ----------------------------------------
  void startupPhase();

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
  // distributes all territories evenly between the players
  // ----------------------------------------
  void distributeTerritories();

  // ----------------------------------------
  // determines a random order of play for players
  // ----------------------------------------
  void playerOrder();

  Deck* getDeck();

  Map* getMap();

  void mainGameLoop();

  LogObserver* getLogObserver();

  bool isTesting() const;

  Player* getCurrentPlayerTurn();

  void validateMaxPlayers();

  void validateMinPlayers();

  void addPlayer(Player* player);

  void resetGame();

  // getters
  std::vector<Player*>* getPlayers();

  GameEngineState getCurrentState();

  CommandProcessor* getCommandProcessor();

  FileLineReader* getFlir();

  FileCommandProcessorAdapter* getFileCommandProcessorAdapter();

  // setters
  void setCurrentPlayer(Player* player);

private:
  // check win state
  Player* checkWinState();
  void nextTurn(int& turn);
  // ----------------------------------------
  // remove players with no territories
  // ----------------------------------------
  void removePlayersWithNoTerritories();


private:
    // ----------------------------------------
    // prints all the commands available for the user to use
    // ----------------------------------------
    void printCommands();

    // ----------------------------------------
    // checks whether a command is valid or not
    // ----------------------------------------
    static bool isValid(const std::string& strCommand);

    // ----------------------------------------
    // convert current state to string
    // ----------------------------------------
    std::string getCurrentStateToString();

};