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
  this->adapter = new FileCommandProcessorAdapter(this);
  this->flr = new FileLineReader();
}

void GameEngine::preStartupPhase() {
    std::string result;
    cout << "Welcome to the startup phase of the game!"<< endl;


    while(true){
        cout <<"Use \'-console\' if you want to input commands for the startup phase through the console." << endl
             << "Use \'-file \' if you want to complete the startup phase using commands from a file." << endl;
        cin >> result;
        if(result.find("-console") != string::npos) {
            printCommands();
            startupPhase();
        }
        else if(result.find("-file") != string::npos ){
            cout << "Please enter the name of the file you would like to use: " << endl;
            cin >> result;
            std::string fileName = "res/" + MapLoader::trim(result);
            try{
                flr->setFile(fileName);
                adapter->commandLineToFile(flr);
                commandProcessor = adapter;
                startupPhase();
            }
            catch(std::runtime_error err){
                cout<< "Invalid file name or file does not exist!"<<endl;
                continue;
            }
        }
        else{
            cout<< "Please enter a valid command: " <<endl;
            continue;
        }
    }
}

void GameEngine::startupPhase() {
    Command* command;
    std::string strCommand = "";
    std::string effect = "";

    do{
        command = commandProcessor->getCommand();
        strCommand = command->getCommand();
        effect = command->getEffect();

        if(!isValid(effect)){
            cout << "The command or its argument is invalid" << endl;
            continue;
        }

        if(strCommand.find("loadmap") != string::npos){
            size_t pos = strCommand.find(' ');
            std::string mapName = "res/" + MapLoader::trim(strCommand.substr(pos));
            try{
                loadMap(mapName);
            }
            catch(std::runtime_error err){
                cout<< err.what()<< endl << "Please enter a valid map name!"<<endl;
                continue;
            }
            cout<<"Map successfully loaded!"<<endl;
        }
        else if(strCommand == "validatemap"){
            try{
                validateMap();
            }
            catch(std::runtime_error err){
                cout<< "Can't validate map before loading map, please load a map first."<<endl;
                setCurrentState(GE_Start);
                continue;
            }
            cout<< "Map successfully validated!" << endl;
        }
        else if(strCommand.find("addplayer")!= string::npos){
            if(getCurrentState() < GE_Map_Loaded){
                cout <<"Please load and validate a map first!" << endl;
                continue;
            }
            if(players.size() == 6){
                cout << "Maximum number of players(6) reached! Game is ready to be started." << endl;
                setCurrentState(GE_Players_Added);
            }
            size_t pos = strCommand.find(' ');
            std::string playerName = strCommand.substr(pos);
            Player* p = new Player(this, new Hand());
            cout<< "Player " << playerName << " was successfully added!"<<endl;

            if(players.size() < 2){
                cout << "Please add at least one more player! Minimum number of players required is two(2)." << endl;
                continue;
            }
            setCurrentState(GE_Players_Added);
        }
        else if(strCommand == "gamestart"){
            distributeTerritories();
            cout<< "Territories distributed."<<endl;

            playerOrder();
            cout<< "Order of play of players determined."<<endl;

            try{
                for(Player* player : players){
//                    player->setReinforcementPool(50);
                    Hand &hand = *player->getHand();
                    deck->draw(hand);
                    deck->draw(hand);
                }
            }
            catch(std::runtime_error err){
                cout << err.what() <<endl;
            }
            //mainGameLoop();
        }
    }while(strCommand != "quit" );
}
void GameEngine::distributeTerritories(){
    std::vector<Territory*>* territories = map->getTerritories();
    int numPlayers = players.size();
    int territoriesDistr[numPlayers];
    int terrPerPlayer = floor(territories->size() / numPlayers);
    int remainingTerr = territories->size() - (numPlayers * terrPerPlayer);
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
        t->setOwnerId(player->getId());
        t->setPlayer(player);
        player->addTerritory(*t);
        tempTerr++;
    }
}

void GameEngine::playerOrder(){
    int index;
    std::vector<int> temp(players.size());
    Player* tempPlayer;
    std::srand(std::time(0));

    for(int i = 0; i < players.size(); i++){
        do{
            index = 1 + rand()%(players.size());
        }while(std::count(temp.begin(), temp.end(),index));
        temp.push_back(index);
        tempPlayer = new Player(*players.at(index - 1));
        players.at((index - 1)) = players.at(i);
        players.at(i) = tempPlayer;
    }
    delete tempPlayer;
}

bool GameEngine::isValid(const std::string strCommand){return strCommand.find("Invalid") == string::npos;}

void GameEngine::printCommands() {
    cout<< "Here are the commands available to you: "<<endl;
    for (string cmd: commands) {
        cout << cmd << " ";
    }
    cout << endl;
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
  return players.at(playerTurn);
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
  delete adapter;
  delete flr;
  delete logObserver;
  delete commandProcessor;

  for(auto player : players){
    delete player;
  }
}

GameEngine::GameEngine() {
  this->map = new Map(this);
  this->deck = new Deck(this);
  this->adapter = new FileCommandProcessorAdapter(this);
  this->flr = new FileLineReader();
  this->logObserver = new LogObserver(this);
  this->commandProcessor = new CommandProcessor(this);
  Subject::attach((ILogObserver*)logObserver);

}

void GameEngine::loadMap(const std::string& path) {
  if(state >= GE_Map_Loaded && state != GE_Win){ throw runtime_error("Map is already loaded."); }
  MapLoader::load(path, this->map);
  setCurrentState(GE_Map_Loaded);
}

bool GameEngine::validateMap() {
  if(state != GE_Map_Loaded){ throw runtime_error("ASSERT: Cannot Validate Map Before Loading Map."); }
  if(map == nullptr){ throw runtime_error("ASSERT: Map is null."); }
  setCurrentState(GE_Map_Validated);
  return map->validate();
}

void GameEngine::gameStart() {
  // Loading the map
  while(this->state != GE_Map_Loaded){
    std::string mapPath;
    std::cout << "Enter the path for the map: ";
    std::cin >> mapPath;
    std::cout << std::endl;
    try{
      loadMap(mapPath);
    } catch (const runtime_error& error){
      std::cout << "Error: " << error.what() << endl;
      std::cout << "Please Try Again." << error.what() << endl;
    }

    std::cout << "Validating Map..." << std::endl;
    std::cout << "Map is " << (validateMap() ? "Valid":"Invalid") << std::endl;
  }
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
    for (auto & player : players)
    {
        player->setPhase("Reinforcement");
        cout << "Player No: " << player->getId() << "'s old Reinforcement Pool Looks Like----> "<< player->getReinforcementPool();
        // if (number of territories owned) / 3 is less than 3, assigns 3 to the player reinforcement pool
        if(((player->getTerritories()->size()) / 3) < 3) // removed round
        {
            cout << "| Player: " << player->getId() << "'s updated Reinforcement Pool Looks Like----> ";
            player->setReinforcementPool(player->getReinforcementPool() + 3);
            cout << player->getReinforcementPool() << endl;
        }

        // check if players owned number of territories matches a continent that hold n amount of territories in order to gain control bonus
        else if (player->ownsAllTerritoryInContinent())
        {
            cout << "| Player: " << player->getId() << "'s updated Reinforcement Pool Looks Like----> ";
            player->setReinforcementPool(player->getReinforcementPool() + 10);
            cout << player->getReinforcementPool() << endl;
        }

        else
        {
            cout << "| Player: " << player->getId() << "'s updated Reinforcement Pool Looks Like----> ";
            player->setReinforcementPool(player->getReinforcementPool() + (int)((player->getTerritories()->size()) / 3)); // removed round
            cout << player->getReinforcementPool() << endl;
        }
    }
}

/*
* ISSUE ORDERS PHASE
*/

void GameEngine::issueOrdersPhase() {
  int phaseTurn = 0;
  vector<bool> completed(players.size());
  for(auto& player : players){ player->setPhase("Issue Orders"); }

  while(std::all_of(completed.begin(), completed.end(), [](bool v) { return v; })){
    auto currentPlayer = players[phaseTurn];

    // when no more orders need to be issued
    if(currentPlayer->getReinforcementPool() == 0 && currentPlayer->getHand()->getHandCards()->empty()){
      completed[phaseTurn] = true;
    }

    currentPlayer->issueOrder();

    phaseTurn = phaseTurn + 1 % (int) players.size();
  }
}

/*
* Execute Orders PHASE
*/

void GameEngine::executeOrdersPhase() {
  int phaseTurn = 0;
  vector<bool> completed(players.size());
  for(auto& player : players){ player->setPhase("Execute Orders Phase"); }
  while(std::all_of(completed.begin(), completed.end(), [](bool v) { return v; })){
    auto currentPlayer = players[phaseTurn];
    auto currentPlayerOrders = currentPlayer->getOrdersListObject()->getList();
    // when no more orders need to be issued
    if(currentPlayerOrders->empty()){
      completed[phaseTurn] = true;
    }

    auto topOrder = currentPlayerOrders->at(0);
    topOrder->execute();
    currentPlayerOrders->erase(currentPlayerOrders->cbegin());
    delete topOrder;

    phaseTurn = phaseTurn + 1 % (int) players.size();
  }
}

void GameEngine::mainGameLoop() {
  Player* winner = nullptr;
  // check win state
  while((winner = checkWinState()) == nullptr){
    reinforcementPhase();
    issueOrdersPhase();
    executeOrdersPhase();
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


