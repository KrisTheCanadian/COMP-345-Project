#include "GameEngineDriver.h"

void printInvalidCommand(const std::string& command){
  std::cout << "Incorrect Command: \"" << command << "\". Please input a correct command." << std::endl;
}

void testGameStates(){
  // create the instance of game_engine
  GameEngine gameEngine;
  // run game while not in a final state

  // get user input
  std::string input;
  while(true){
    std::cout << "Current Game State: " << gameEngine.getCurrentStateToString() << std::endl;
    std::cout << "Please enter an action: ";
    std::cin >> input;

    switch(gameEngine.getCurrentState()){
      case GE_Start:
        if(input == "loadmap"){ gameEngine.setCurrentState(GameEngineState::GE_Map_Loaded); }
        else { printInvalidCommand((string)input); }
        break;
      case GE_Map_Loaded:
        if(input == "loadmap"){ continue; }
        else if(input == "validatemap"){ gameEngine.setCurrentState(GameEngineState::GE_Map_Validated); }
        else { printInvalidCommand((string)input); }
        break;
      case GE_Map_Validated:
        if(input == "addplayer"){ gameEngine.setCurrentState(GameEngineState::GE_Players_Added); }
        else { printInvalidCommand((string)input); }
        break;
      case GE_Players_Added:
        if(input == "addplayer"){ continue; }
        else if(input == "assigncountries"){ gameEngine.setCurrentState(GameEngineState::GE_Reinforcement); }
        else { printInvalidCommand((string)input); }
        break;
      case GE_Reinforcement:
        if(input == "issueorder"){ gameEngine.setCurrentState(GameEngineState::GE_Issue_Orders); }
        else { printInvalidCommand((string)input); }
        break;
      case GE_Issue_Orders:
        if(input == "issueorder"){ continue; }
        else if(input == "endissueorders"){ gameEngine.setCurrentState(GameEngineState::GE_Execute_Orders); }
        else { printInvalidCommand((string)input); }
        break;
      case GE_Execute_Orders:
        if(input == "execorder"){ continue; }
        else if(input == "execorders"){ gameEngine.setCurrentState(GameEngineState::GE_Reinforcement); }
        else if(input == "win"){ gameEngine.setCurrentState(GameEngineState::GE_Win); }
        else { printInvalidCommand((string)input); }
        break;
      case GE_Win:
        if(input == "play"){ gameEngine.setCurrentState(GameEngineState::GE_Start); }
        else if(input == "end"){ return; }
        else { printInvalidCommand((string)input); }
        break;
    }
    std:: cout << "------------------------------" << std::endl;
  }
}

void testGameLoop(){
  // create a game engine
  auto gameEngine = GameEngine();

  // add cards to the gameEngine deck
  auto deck = gameEngine.getDeck();
  deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Reinforcement, &gameEngine));

  deck->addCardToDeck(new Card(CardType::CT_Airlift, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Airlift, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Airlift, &gameEngine));

  deck->addCardToDeck(new Card(CardType::CT_Diplomacy, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Diplomacy, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Diplomacy, &gameEngine));

  deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));

  deck->addCardToDeck(new Card(CardType::CT_Blockade, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Blockade, &gameEngine));
  deck->addCardToDeck(new Card(CardType::CT_Blockade, &gameEngine));


  // load a map before game starts
  gameEngine.loadMap("../res/TestMap1_valid.map");

  // create players
  auto player1 = new Player(&gameEngine, new Hand(), "Rick Astley");
  auto player2 = new Player(&gameEngine, new Hand(), "Bob Ross");
  auto player3 = new Player(&gameEngine, new Hand(), "Felix Kjellberg");

  // adding sets of territories just for testing
  auto map = gameEngine.getMap();
  auto continents = map->getContinents();
  auto mapTerritories = map->getTerritories();

  for(auto t : *continents->at(0)->getTerritories()){
    player1->addTerritory(*t);
  }

  for(auto t : *continents->at(1)->getTerritories()){
    player2->addTerritory(*t);
  }

  for(auto t : *continents->at(1)->getTerritories()){
    player3->addTerritory(*t);
  }


  // manually add cards to player
  player1->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  player2->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player2->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player2->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player2->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player2->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  player3->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player3->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player3->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player3->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player3->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  gameEngine.mainGameLoop();
}
