#include <gtest/gtest.h>
#include "Orders/Orders.h"

TEST(OrdersListSuite, listInitialized)
{
  // arrange
  OrdersList list;
  // act
  list = OrdersList();
  // assert
  auto orders = list.getList();
  EXPECT_EQ(orders->size(), 0);
}

TEST(OrdersListSuite, listAddOrders)
{

  // arrange

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

  for(auto t : *continents->at(0)->getTerritories()){
    player1->addTerritory(*t);
  }

  for(auto t : *continents->at(1)->getTerritories()){
    player2->addTerritory(*t);
  }

  for(auto t : *continents->at(2)->getTerritories()){
    player3->addTerritory(*t);
  }


  // act
  player1->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  gameEngine.reinforcementPhase();
  gameEngine.issueOrdersPhase();

  // issue orders

  gameEngine.setCurrentPlayer(player1);
  auto cards = player1->getHand()->getCards();
  for(auto& card : *cards){
    card->play();
  }

  // assert
  EXPECT_FALSE(player1->getOrdersListObject()->getList()->empty());
}

TEST(OrdersListSuite, listRemoveOrder)
{
  // arrange

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

  for(auto t : *continents->at(2)->getTerritories()){
    player3->addTerritory(*t);
  }


  // act
  player1->getHand()->addToHand(new Card(CardType::CT_Reinforcement, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Blockade, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Bomb, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Diplomacy, &gameEngine));
  player1->getHand()->addToHand(new Card(CardType::CT_Airlift, &gameEngine));

  gameEngine.reinforcementPhase();
  // issue orders
  gameEngine.issueOrdersPhase();



  auto list = player1->getOrdersListObject();
  // assert
  auto originalSize = list->getList()->size();
  list->remove(0);
  list->remove(0);
  EXPECT_EQ(list->getList()->size(), originalSize - 2);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

