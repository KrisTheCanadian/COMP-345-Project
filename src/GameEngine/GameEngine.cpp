#include "GameEngine.h"
#include "Command/CommandProcessor.h"
#include "Command/Command.h"


void GameEngine::setCurrentState(GameEngineState engineState) {
  this->state = engineState;
}

GameEngineState GameEngine::getCurrentState() {
  return this->state;
}

GameEngine::GameEngine(GameEngineState state) {
  this->state = state;
  this->deck = new Deck(this);
  this->map = new Map(this);
}

void GameEngine::startupPhase(bool cmd) {
    if(cmd){cStartupPhase();}
    else if(!cmd){fStartupPhase();}
}

void GameEngine::fStartupPhase() {

}

void GameEngine::cStartupPhase() {
    CommandProcessor* commandProcessor = new CommandProcessor ();
    Command* command = NULL;
    std::string strCommand = "";
    std::string effect = "";
    cout << "Welcome to the startup phase of the game! Here are the list of commands available to you: " << endl;
    printCommands();
    do{
//        cout << "Enter the command you wish to use: ";
        command = commandProcessor->getCommand();
        strCommand = command->getCommand();
        effect = command->getEffect();

        if(!isValid(effect)){
            cout << effect << endl;
            cout << "The command or its argument is invalid" << endl;
            continue;
        }

        if(strCommand.find("loadmap") != string::npos){
            size_t pos = strCommand.find(' ');
            std::string mapName= "res/" + MapLoader::trim(strCommand.substr(pos));
            cout << "Map Name:" << mapName << endl;
            loadMap(mapName);
            if(state != GE_Map_Loaded) {
                cout << "Please enter a valid map name!"<<endl;
                continue;
            }
        }
        else if(strCommand == "validatemap"){
            if(validateMap()) {
                cout<< "Map successfully validated!" << endl;
                continue;
            }
            else {
                cout << "Please first load a valid map then validate it again!" << endl;
                state = GE_Start;
            }
        }
        else if(strCommand.find("addplayer")!= string::npos){
            if(players.size() == 6){
                cout << "Maximum number of players(6) reached! Game is ready to be started with command gamestart." << endl;
                continue;
            }
            size_t pos = strCommand.find(' ');
            std::string playerName = strCommand.substr(pos);
            addPlayer(playerName);

            if(players.size() < 2){
                cout << "Please add at least one more player! Minimum number of players required is two(2)." << endl;
                continue;
            }
            state = GE_Players_Added;
        }
        else if(strCommand == "gamestart"){
            cout << "gamestart"<< endl;
            distributeTerritories();
            cout << "territories distr"<< endl;
            playerOrder();
            cout << "players ord"<< endl;
            //each player draws 2 cards
//            for(Player* player : playersOrder){
//                //add 50 units to reinforcement pool
//                Hand &hand = *player->getHand();
//                deck->draw(hand);
//                deck->draw(hand);
//            }
            state = GE_Reinforcement;
            for(Player* player : playersOrder) {
                cout<< player->getId() << endl;
                for(Territory *t : *player->getTerritories()){
                    cout << "Territory name: " << t->getName();
                }
            }
            for(Territory* terr : *map->getTerritories()) cout << "territory name: " << terr->getName() << " owner id: " << terr->getOwnerId() << endl;
            //mainGameLoop();
        }
    }while(strCommand != "quit");

}

void GameEngine::distributeTerritories(){
    int numPlayers = players.size();
    std::vector<Territory*>* territories = map->getTerritories();
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
    cout << "num of territories: " << territories->size()<< endl;
    //iterates through all territories
    for(Territory *terr : *territories){
        Territory* t = terr;
        if(tempTerr == (territoriesDistr[currPlayer])){
            cout << "tempTerr: " << tempTerr << endl;
            currPlayer++;
            player = players.at(currPlayer);
            tempTerr = 0;
        }
        cout << "FUCK " << endl;
        t->setOwnerId(player->getId());
        t->setPlayer(player);
        player->addTerritory(*t);
        tempTerr++;
    }
}

void GameEngine::playerOrder(){
    int index;
    std::vector<int> temp(players.size());
    for(int i = 0; i < players.size(); i++){
        playersOrder.push_back(nullptr);
    }

    for(int i = 0; i < players.size(); i++){
        do{
            index = 1 + rand()%(players.size());
        }while(std::count(temp.begin(), temp.end(),index));
        temp.push_back(index);
        playersOrder.at((index - 1)) = players.at(i);
    }
}

bool GameEngine::isValid(std::string strCommand){return strCommand.find("Invalid") == string::npos;}

void GameEngine::printCommands() {
    for(string cmd : commands){
        cout << cmd << ((std::equal(cmd.begin(), cmd.end(),"loadmap"))?" <filename>": "" )<< ((std::equal(cmd.begin(), cmd.end(),"addplayer"))?" <playername>": "" ) << " ";
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

void GameEngine::nextPlayerTurn() {
  playerTurn++;
  playerTurn %= players.size();
}

std::vector<Player *> *GameEngine::getPlayers() {
  return &this->players;
}

Player* GameEngine::getCurrentPlayerTurn() {
  return players.at(playerTurn);
}

Deck *GameEngine::getDeck() {
  return this->deck;
}

Map* GameEngine::getMap() {
  return this->map;
}

void GameEngine::addPlayer(const std::string& name) {
  auto* p = new Player(this, new Hand());
//  this->players.push_back(p);
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

  for(auto player : players){
    delete player;
  }
}

GameEngine::GameEngine() {
  this->map = new Map(this);
  this->deck = new Deck(this);
}

void GameEngine::loadMap(const std::string& path) {
  if(state >= GE_Map_Loaded && state != GE_Win){ throw runtime_error("Map is already loaded."); }
  MapLoader::load(path, this->map);
  state = GE_Map_Loaded;
}

bool GameEngine::validateMap() {
  if(state != GE_Map_Loaded){ throw runtime_error("ASSERT: Cannot Validate Map Before Loading Map."); }
  if(map == nullptr){ throw runtime_error("ASSERT: Map is null."); }
  state = GE_Map_Validated;
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
