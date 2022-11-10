#include "GameEngineDriver.h"

void printInvalidCommand(const std::string& command){
  std::cout << "Incorrect Command: \"" << command << "\". Please input a correct command." << std::endl;
}

void testGameStates(){
  GameEngine gameEngine;

    gameEngine.preStartupPhase();
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
