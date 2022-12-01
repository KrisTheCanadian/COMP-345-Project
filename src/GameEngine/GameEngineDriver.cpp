#include "GameEngineDriver.h"

void testStartupPhase(int argc, char** argv){
  auto gameEngine = GameEngine(argc,argv);
  gameEngine.startupPhase();
}
void testGameLoop(int argc, char** argv){
  // create a game engine
  auto gameEngine = GameEngine(argc, argv);

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
  auto player1 = new Player(&gameEngine, new Hand(), "Rick Astley", "Human");
  auto player2 = new Player(&gameEngine, new Hand(), "Bob Ross", "Aggressive");
  auto player3 = new Player(&gameEngine, new Hand(), "Felix Kjellberg", "Aggressive");
  auto player4 = new Player(&gameEngine, new Hand(), "Elon Musk", "Aggressive");
  auto player5 = new Player(&gameEngine, new Hand(), "Steve Jobs", "Aggressive");
  auto player6 = new Player(&gameEngine, new Hand(), "James Bond", "Aggressive");

  // adding sets of territories just for testing
  auto map = gameEngine.getMap();
  auto continents = map->getContinents();

  for(auto t : *continents->at(0)->getTerritories()){
    player1->addTerritory(*t);
  }

  for(auto t : *continents->at(1)->getTerritories()){
    player2->addTerritory(*t);
  }

  for(auto t : *continents->at(2)->getTerritories()){
    player3->addTerritory(*t);
  }

  for(auto t : *continents->at(3)->getTerritories()){
    player4->addTerritory(*t);
  }

  for(auto t : *continents->at(4)->getTerritories()){
    player5->addTerritory(*t);
  }

  for(auto t : *continents->at(5)->getTerritories()){
    player6->addTerritory(*t);
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

  player4->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player4->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player4->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player4->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player4->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  player5->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player5->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player5->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player5->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player5->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  player6->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player6->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player6->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player6->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player6->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  gameEngine.mainGameLoop();
}
