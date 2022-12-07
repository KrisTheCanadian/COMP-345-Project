#include "GameEngine.h"
#include "Player/PlayerStrategies.h"
#include <random>
#include <iomanip>


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

        else if(effect == "Tournament started"){
          runTournament();
          strCommand = "quit";
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

void GameEngine::validateTournament() {
  if (allMaps.size() < 1 || allMaps.size() > 5)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of maps must be between 1 to 5";
    exit(0);
  }
  if (allPlayerStrategies.size() < 2 || allPlayerStrategies.size() > 4)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of player strategies must be between 2 to 4";
    exit(0);
  }
  if (numberOfGames < 1 || numberOfGames > 5)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of games must be between 1 to 5";
    exit(0);
  }
  if (maxNumberOfTurns < 10 || maxNumberOfTurns > 50)
  {
    std::cout << "GameEngine::validateTournament::Error | Number of turns must be between 10 to 50";
    exit(0);
  }
  // validate strategy
  string strategies[5] = {"Aggressive", "Benevolent", "Neutral", "Cheater", "Human"};
  int invalidStrategyCounter = 0;

  for (int i = 0; i < allPlayerStrategies.size(); i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (allPlayerStrategies[i] == strategies[j])
      {
        break;
      }
      else if (allPlayerStrategies[i] != strategies[j] && j == 4)
      {
        cout << allPlayerStrategies[i] + " X NOT VALID" << endl;
        invalidStrategyCounter++;
      }
    }
  }
  if (invalidStrategyCounter > 0)
  {
    cout << invalidStrategyCounter;
    throw std::runtime_error("GameEngine::validateTournament::Error | Player strategies entered are not valid");
  }
}

std::string GameEngine::stringToLog() {
  std::stringstream ss;
  if(tournamentEnd) return getTournamentResults();
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

    auto human = dynamic_cast<Human*>(currentPlayerTurn->getStrategy());

    // when no more orders need to be issued
    if(currentPlayerTurn->getDeployedArmiesThisTurn() >= currentPlayerTurn->getReinforcementPool() && human == nullptr){
      completed[phaseTurn] = true;
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to issue." << endl;
      continue;
    }

    if(human != nullptr && human->isTurnDone){
      completed[phaseTurn] = true;
      cout << "Player: " << currentPlayerTurn->getName() << " has no more orders to issue." << endl;
      continue;
    }

    currentPlayerTurn->issueOrder();

    nextTurn(phaseTurn);
  }

  for(auto& player : players){
    player->clearDeploymentArmies();
    // clear the deployment troops for all human players
    if(auto strategy = dynamic_cast<Human*>(player->getStrategy())){
      strategy->reset();
    }
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

void GameEngine::mainGameLoop(int maxRounds) {
  if(players.empty()){throw std::runtime_error("GameEngine::mainGameLoop::Assert Player size is 0.");}
  Player* winner;
  // check win state
  int round = 0;
  isDraw = false;

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
      cout << "This game is gonna take forever. Draw.." << endl;
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

  if(multipleTournaments){
    allPlayerStrategies = {};
    numberOfGames = 0;
    maxNumberOfTurns = 0;
  }

  for(auto player : players){
    delete player;
  }

  delete deck;
  delete map;
  delete adapter;
  delete flr;
  delete logObserver;

  this->players = vector<Player*>();
  this->currentPlayerTurn = nullptr;
  this->logObserver = new LogObserver(this);
  this->map = new Map(this);
  this->deck = new Deck(this);
  this->adapter = new FileCommandProcessorAdapter(this, argc, argv);
  this->flr = new FileLineReader();
  this->resetObservers();

  if(!multipleTournaments){
    delete commandProcessor;
    this->commandProcessor = new CommandProcessor(this, argc, argv);
  }

  Subject::attach((ILogObserver*)logObserver);

}
bool GameEngine::isTesting() const {
  return testing;
}

void GameEngine::runTournament() {
    tournamentEnd = false;
  for(int i = 0; i < allMaps.size(); i++){
    loadMap(allMaps[i]);
    std::vector<std::string> currMap{};
    currMap.push_back(allMaps.at(i));
    int localNumGames = numberOfGames;
    int localMaxTurns = maxNumberOfTurns;
    std::vector<std::string> localAllPlayerStrategies = allPlayerStrategies;
    if(validateMap()){
      for(int j = 0; j < localNumGames; j++){
        generateRandomDeck();
        for (auto & allPlayerStrategie : localAllPlayerStrategies){
          new Player(this, new Hand(), allPlayerStrategie, allPlayerStrategie);
        }
        assignCardsEvenly();
        distributeTerritories();
        mainGameLoop(localMaxTurns);
        currMap.push_back(isDraw? "draw" : checkWinState()->getName());

        resetGame();
        state = GE_Tournament;
        loadMap(allMaps[i]);
      }
      resetGame();
    }
    else{
      std::cout << "" << std::endl;
      std::cout << "Map " + std::to_string(i+1) + " is invalid" << std::endl;
      resetGame();
      state = GE_Tournament;
    }
      tournamentResults.push_back(currMap);
  }
    tournamentEnd = true;
    Subject::notify(this);
}

std::string GameEngine::getTournamentResults() {
    std::stringstream str;
    const char separator = ' ';
    const int mapNameWidth = 25;
    const int nameWidth = 15;
    str << "Tournament Mode: " << endl;
    str << "M: ";
    for(int i = 0; i < tournamentResults.size(); i++){
        str << (tournamentResults.at(i))[0] << ((i != tournamentResults.size()-1)? ',' : ' ');
    }
    str << endl << "P: ";
    for(int i = 0; i < allPlayerStrategies.size(); i++ ){
        str << (allPlayerStrategies.at(i)) << ((i != allPlayerStrategies.size()-1)? ',' : ' ');
    }
    str << endl << "G: " << numberOfGames << endl << "D: " << maxNumberOfTurns << endl;
    str << std::left << std::setw(mapNameWidth) << std::setfill(separator) << "Map Name";

    for(int s = 1; s <= numberOfGames; s++){
        str << std::left << std::setw(nameWidth) << std::setfill(separator) << ("Game " + std::to_string(s));
    }
    str << endl;

    for(auto & tournamentResult : tournamentResults){
        str << std::left << std::setw(mapNameWidth) << std::setfill(separator) << tournamentResult.at(0);

        for(int j = 1; j < tournamentResult.size(); j++) {
            str << std::left << std::setw(nameWidth) << std::setfill(separator) << tournamentResult.at(j);
        }
        str << endl;
    }
    return str.str();
}

void GameEngine::generateRandomDeck(int deckSize){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distribution(0, 4);

  CardType cardOptions[5] = {CT_Bomb,
                             CT_Reinforcement,
                             CT_Blockade,
                             CT_Airlift,
                             CT_Diplomacy
  };

  for(int i = 0; i < deckSize; i++){
    int randomNum = distribution(gen);
    deck->addCardToDeck(new Card(cardOptions[randomNum], this));
  };
}

//Or Randomly?
void GameEngine::assignCardsEvenly(){
  for(auto & player : players){
    player->getHand()->addToHand(new Card(CardType::CT_Reinforcement, this));
    player->getHand()->addToHand(new Card(CardType::CT_Blockade, this));
    player->getHand()->addToHand(new Card(CardType::CT_Bomb, this));
    player->getHand()->addToHand(new Card(CardType::CT_Diplomacy, this));
    player->getHand()->addToHand(new Card(CardType::CT_Airlift, this));
  }

}


