#include "GameEngine.h"



void GameEngine::setCurrentState(GameEngineState engineState) {
  this->state = engineState;
  Subject::notify(this);
}

GameEngineState GameEngine::getCurrentState() {
  return this->state;
}

GameEngine::GameEngine(GameEngineState state, int argc, char** argv, bool testing) {
  this->state = state;
  this->deck = new Deck(this);
  this->map = new Map(this);
  this->logObserver = new LogObserver(this);
  this->commandProcessor = new CommandProcessor(this, argc, argv);
  this->adapter = new FileCommandProcessorAdapter(this, argc, argv);
  this->flr = new FileLineReader();
  Subject::attach((ILogObserver*)logObserver);

  this->argc = argc;
  this->argv = argv;

  this->testing = testing;
}

void GameEngine::startupPhase() {
    Command* command;
    std::string strCommand;
    std::string effect;

    if(!commandProcessor){ throw std::runtime_error("GameEngine::startupPhase::ASSERT commandProcessor is null"); }
    cout << "Welcome to the startup phase of the game!\n"<< endl;
    printCommands();
    do{
        command = commandProcessor->getCommand();
        strCommand = command->getCommand();
        effect = command->getEffect();

        if(effect == "Game successfully restarted") {
          resetGame();
          startupPhase();
        }

        else if(!isValid(effect) && strCommand != "quit"){
            cout << "The command or its argument is invalid" << endl;
            continue;
        }
    } while(strCommand != "quit" );
}

void GameEngine::validateMaxPlayers() {
  if(players.size() == 6){
    throw std::runtime_error("Maximum number of players(6) reached! Game is ready to be started.");
  }
}

void GameEngine::validateMinPlayers() {
  if(players.size() < 2){
    throw std::runtime_error("Please add at least one more player! Minimum number of players required is two(2).");
  }
}

void GameEngine::distributeTerritories(){
  if(!map){ throw std::runtime_error("GameEngine::distributeTerritories::ASSERT Map is null"); }
  std::vector<Territory*>* territories = map->getTerritories();
  int numPlayers = (int)players.size();
  int territoriesDistr[numPlayers];
  int terrPerPlayer = floor(territories->size() / numPlayers);
  int remainingTerr = (int)territories->size() - (numPlayers * terrPerPlayer);
  int currPlayer = 0;
  int tempTerr = 0;
  Player* player = players.at(currPlayer);

  for(int i = 0; i < numPlayers; i++){
      territoriesDistr[i] = terrPerPlayer;
      if(remainingTerr > 0){
              territoriesDistr[i] +=1;
              remainingTerr--;
      }
  }

  for(Territory *terr : *territories){
      Territory* t = terr;
      if(tempTerr == (territoriesDistr[currPlayer])){
          currPlayer++;
          player = players.at(currPlayer);
          tempTerr = 0;
      }
      player->addTerritory(*t);
      tempTerr++;
  }
}

void GameEngine::playerOrder(){
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(players), std::end(players), rng);
}

bool GameEngine::isValid(const std::string& strCommand){return strCommand.find("Invalid") == string::npos;}

void GameEngine::printCommands() {
    cout<< "Here are the commands available to you: "<<endl;
    for (const string& cmd: commands) {
        cout << cmd << " ";
    }
    cout << "\n" << endl;
}

std::string GameEngine::getCurrentStateToString() {
  switch (this->state) {
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
    case GE_Issue_Orders:
      return "Issue Orders";
    case GE_Execute_Orders:
      return "Execute Orders";
    case GE_Win:
      return "Win";
  }

  throw std::runtime_error("Invalid State");
}

std::vector<Player *> *GameEngine::getPlayers() {
  return &this->players;
}

Player* GameEngine::getCurrentPlayerTurn() {
  return currentPlayerTurn;
}

Deck* GameEngine::getDeck() {
  return this->deck;
}

Map* GameEngine::getMap() {
  return this->map;
}

LogObserver* GameEngine::getLogObserver() {
    return this->logObserver;
}

CommandProcessor* GameEngine::getCommandProcessor() {
    return this->commandProcessor;
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
  for(auto player : players){
    delete player;
  }

  delete deck;
  delete map;
  delete adapter;
  delete flr;
  delete logObserver;
  delete commandProcessor;
}

GameEngine::GameEngine(int argc, char** argv, bool testing) {
  this->logObserver = new LogObserver(this);
  this->map = new Map(this);
  this->deck = new Deck(this);
  this->adapter = new FileCommandProcessorAdapter(this, argc, argv);
  this->flr = new FileLineReader();
  this->commandProcessor = new CommandProcessor(this, argc, argv);
  this->argc = argc;
  this->argv = argv;
  Subject::attach((ILogObserver*)logObserver);
  this->testing = testing;
}

void GameEngine::loadMap(const std::string& path) {
  MapLoader::load(path, this->map);
}

bool GameEngine::validateMap() {
  if(map == nullptr){ throw runtime_error("ASSERT: Map is null."); }
  return map->validate();
}

bool GameEngine::validateTournament() {

}

std::string GameEngine::stringToLog() {
  std::stringstream ss;
  ss << "GAME ENGINE: ";
  ss << "State transition to ";
  ss << getCurrentStateToString();
  return ss.str();
}

/*
* REINFORCEMENT PHASE
*/
void GameEngine::reinforcementPhase()
{
  for (auto& player : players)
  {
    currentPlayerTurn = player;
    player->setPhase("Reinforcement");
    cout << "Player: " << player->getName() << "'s current Reinforcement Pool: "<< player->getReinforcementPool() << endl;
    // check for continents bonus before territories themselves
    // check if players owned number of territories matches a continent that hold n amount of territories in order to gain control bonus
    int reinforcementsToAdd = 0;

    // get continent bonus
    reinforcementsToAdd += player->getContinentBonus();
    if(reinforcementsToAdd > 0){cout << "Player: " << player->getName() << "'s continent bonus is: "<< player->getReinforcementPool() << endl;}

    // get territories reinforcement
    reinforcementsToAdd += (int)(player->getTerritories()->size() / 3) * 3;

    // check if they have min
    if(reinforcementsToAdd < 3){ reinforcementsToAdd = 3;}

    player->addReinforcement(reinforcementsToAdd);

    cout << "Player: " << player->getName() << "'s updated Reinforcement Pool: "<< player->getReinforcementPool() << endl;
  }
}

/*
* ISSUE ORDERS PHASE
*/

void GameEngine::issueOrdersPhase() {
  int phaseTurn = 0;
  vector<bool> completed(players.size());
  for(auto& player : players){ player->setPhase("Issue Orders"); }

  while(!std::all_of(completed.begin(), completed.end(), [](bool v) { return v; })){
    if(completed[phaseTurn]){ nextTurn(phaseTurn); continue; }
    currentPlayerTurn = players[phaseTurn];

    cout << "Player: " << currentPlayerTurn->getName() << "'s turn to issue an order!" << endl;

    // when no more orders need to be issued
    if(currentPlayerTurn->getDeployedArmiesThisTurn() >= currentPlayerTurn->getReinforcementPool()){
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to issue." << endl;
      completed[phaseTurn] = true;
      continue;
    }

    currentPlayerTurn->issueOrder();

    nextTurn(phaseTurn);
  }

  for(auto& player : players){
    player->clearDeploymentArmies();
  }
}

/*
* Execute Orders PHASE
*/

void GameEngine::executeOrdersPhase() {
  int phaseTurn = 0;
  vector<bool> completed(players.size());
  for(auto& player : players){ player->setPhase("Execute Orders Phase"); }

  while(!std::all_of(completed.begin(), completed.end(), [](bool v) { return v; })){
    if(completed[phaseTurn]){nextTurn(phaseTurn); continue; }
    currentPlayerTurn = players[phaseTurn];
    auto currentPlayerOrders = currentPlayerTurn->getOrdersListObject()->getList();

    // when no more orders need to be issued
    if(currentPlayerOrders->empty()){
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to execute." << endl;
      completed[phaseTurn] = true;
      continue;
    }

    auto topOrder = currentPlayerOrders->at(0);
    cout << "Player: " << currentPlayerTurn->getName() << "'s order: " + topOrder->getLabel() + " is being executed." << endl;
    topOrder->execute();
    currentPlayerOrders->erase(currentPlayerOrders->cbegin());

    delete topOrder;

    nextTurn(phaseTurn);
  }

  // reset player friendly
  for(auto player : players){
    player->clearFriendly();
  }
}

void GameEngine::mainGameLoop() {
  if(players.empty()){throw std::runtime_error("GameEngine::mainGameLoop::Assert Player size is 0.");}
  Player* winner;
  // check win state
  int round = 0;
  int maxRounds = 500;
  bool isDraw = false;

  while((winner = checkWinState()) == nullptr){
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Round: " << round << "" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    removePlayersWithNoTerritories();
    reinforcementPhase();
    issueOrdersPhase();
    executeOrdersPhase();
    round++;
    if(round > maxRounds){
      cout << "This game is gonna take forever. Draw..";
      isDraw = true;
      break;
    }
  }
  
  if(!isDraw){
    cout << "Congratulations " << winner->getName() << "!" << endl;
  }

  setCurrentState(GE_Win);
}

Player* GameEngine::checkWinState() {
  if(map == nullptr){throw std::runtime_error("checkWinState::Assert Map is null.");}

  int totalAmountOfTerritories = (int) map->getTerritories()->size();

  for(auto& player: players){
    // check if a player has all the territories
    if(player->getTerritories()->size() == totalAmountOfTerritories){
      return player;
    }
  }
  return nullptr;
}

void GameEngine::nextTurn(int &turn) {
  turn++;
  turn %= (int)players.size();
}

void GameEngine::setCurrentPlayer(Player* player) {
  currentPlayerTurn = player;
}

void GameEngine::removePlayersWithNoTerritories() {
  auto playersToBeDeleted = vector<Player*>();

  for(auto& player : players){
    if(player->getTerritories()->empty()){
      playersToBeDeleted.push_back(player);
    }
  }

  // remove from game
  players.erase(std::remove_if(players.begin(), players.end(), [&](Player* p) {
                  return p->getTerritories()->empty();
                }), players.end());


  // free memory
  for(auto& player : playersToBeDeleted){
    cout << player->getName() << " has been conquered!" << endl;
    delete player;
  }
}
FileLineReader* GameEngine::getFlir() {
  return flr;
}
FileCommandProcessorAdapter *GameEngine::getFileCommandProcessorAdapter() {
  return adapter;
}

void GameEngine::resetGame() {

  for(auto player : players){
    delete player;
  }

  delete deck;
  delete map;
  delete adapter;
  delete flr;
  delete logObserver;
  delete commandProcessor;

  this->players = vector<Player*>();
  this->currentPlayerTurn = nullptr;

  this->logObserver = new LogObserver(this);
  this->map = new Map(this);
  this->deck = new Deck(this);
  this->adapter = new FileCommandProcessorAdapter(this, argc, argv);
  this->flr = new FileLineReader();
  this->commandProcessor = new CommandProcessor(this, argc, argv);
  this->resetObservers();

  Subject::attach((ILogObserver*)logObserver);

}
bool GameEngine::isTesting() const {
  return testing;
}
