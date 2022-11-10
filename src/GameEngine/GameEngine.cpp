#include "GameEngine.h"

void GameEngine::setCurrentState(GameEngineState engineState) {
  this->state = engineState;
  Subject::notify(this);
}

GameEngineState GameEngine::getCurrentState() {
  return this->state;
}

GameEngine::GameEngine(GameEngineState state) {
  this->state = state;
  this->deck = new Deck(this);
  this->map = new Map(this);
  this->logObserver = new LogObserver(this);
  this->commandProcessor = new CommandProcessor(this);
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
  delete deck;
  delete map;
  delete logObserver;
  delete commandProcessor;

  for(auto player : players){
    delete player;
  }
}

GameEngine::GameEngine() {
  this->map = new Map(this);
  this->deck = new Deck(this);
  this->logObserver = new LogObserver(this);
  this->commandProcessor = new CommandProcessor(this);
  Subject::attach((ILogObserver*)logObserver);
}

void GameEngine::loadMap(const std::string& path) {
  MapLoader::load(path, this->map);
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
    if(currentPlayerTurn->getReinforcementPool() == 0 && currentPlayerTurn->getHand()->getHandCards()->empty()){
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to issue." << endl;
      completed[phaseTurn] = true;
      continue;
    }

    currentPlayerTurn->issueOrder();

    nextTurn(phaseTurn);
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
}

void GameEngine::mainGameLoop() {
  if(players.empty()){throw std::runtime_error("GameEngine::mainGameLoop::Assert Player size is 0.");}
  Player* winner = nullptr;
  // check win state
  while((winner = checkWinState()) == nullptr){
    reinforcementPhase();
    issueOrdersPhase();
    executeOrdersPhase();
    // TODO: Remove when logic from part 4 is added (or else it infinite loops)
    cin.get();
  }
  cout << "Congratulations" << winner->getName() << endl;
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


