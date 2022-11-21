#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameEngine/GameEngine.h"

TEST(GameEngineTestSuite, GameEngineInit)
{
  // arrange
  // act
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv, true);
  // assert

  EXPECT_FALSE(gameEngine.getMap() == nullptr);
  EXPECT_FALSE(gameEngine.getDeck() == nullptr);

  EXPECT_TRUE(gameEngine.getMap()->getTerritories()->empty());
  EXPECT_TRUE(gameEngine.getDeck()->getDeckCards()->empty());
  EXPECT_TRUE(gameEngine.getPlayers()->empty());
}

TEST(GameEngineTestSuite, GameEngineLoadMap)
{
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv, true);
  // act

  gameEngine.loadMap("res/TestMap1_valid.map");
  // assert
  auto map = gameEngine.getMap();
  EXPECT_FALSE(map == nullptr);
  EXPECT_FALSE(map->getTerritories()->empty());
  EXPECT_FALSE(map->getContinents()->empty());
}

TEST(GameEngineTestSuite, GameEngineReinforcementPhase)
{
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv, true);
  gameEngine.loadMap("res/TestMap1_valid.map");

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

  auto player1 = new Player(&gameEngine, new Hand(), "Rick Astley", "Aggressive");
  auto player2 = new Player(&gameEngine, new Hand(), "Bob Ross", "Aggressive");
  auto player3 = new Player(&gameEngine, new Hand(), "Felix Kjellberg", "Aggressive");

  // adding sets of territories just for testing
  auto map = gameEngine.getMap();
  auto continents = map->getContinents();

  for(auto t : *continents->at(0)->getTerritories()){
    player1->addTerritory(*t);
  }

  player2->addTerritory(*continents->at(1)->getTerritories()->at(0));

  for(auto t : *continents->at(1)->getTerritories()){
    player3->addTerritory(*t);
  }

  // act
  gameEngine.reinforcementPhase();

  int player1ExpectedPool = gameEngine.getMap()->getContinents()->at(0)->getBonus() + (int)(player1->getTerritories()->size() / 3) * 3;
  int player3ExpectedPool = gameEngine.getMap()->getContinents()->at(1)->getBonus() + (int)(player1->getTerritories()->size() / 3) * 3;
  // assert
  EXPECT_EQ(player1->getReinforcementPool(), player1ExpectedPool);
  EXPECT_EQ(player2->getReinforcementPool(), 3);
  EXPECT_EQ(player3->getReinforcementPool(), player3ExpectedPool);

  EXPECT_EQ(player1->getPhase(), "Reinforcement");
  EXPECT_EQ(player2->getPhase(), "Reinforcement");
  EXPECT_EQ(player3->getPhase(), "Reinforcement");
}

TEST(GameEngineTestSuite, GameEngineIssueOrderPhase)
{
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv, true);
  gameEngine.loadMap("res/TestMap1_valid.map");

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

  auto player1 = new Player(&gameEngine, new Hand(), "Rick Astley", "Aggressive");
  auto player2 = new Player(&gameEngine, new Hand(), "Bob Ross", "Aggressive");
  auto player3 = new Player(&gameEngine, new Hand(), "Felix Kjellberg", "Aggressive");

  // adding sets of territories just for testing
  auto map = gameEngine.getMap();
  auto continents = map->getContinents();

  for(auto t : *continents->at(0)->getTerritories()){
    player1->addTerritory(*t);
  }

  player2->addTerritory(*continents->at(2)->getTerritories()->at(0));

  for(auto t : *continents->at(1)->getTerritories()){
    player3->addTerritory(*t);
  }

  gameEngine.reinforcementPhase();

  // act
  gameEngine.issueOrdersPhase();


  // assert
  EXPECT_EQ(player1->getDeployedArmiesThisTurn(), 0);
  EXPECT_EQ(player2->getDeployedArmiesThisTurn(), 0);
  EXPECT_EQ(player3->getDeployedArmiesThisTurn(), 0);

  EXPECT_FALSE(player1->getOrdersListObject()->getList()->empty());
  EXPECT_FALSE(player2->getOrdersListObject()->getList()->empty());
  EXPECT_FALSE(player3->getOrdersListObject()->getList()->empty());

  EXPECT_EQ(player1->getHand()->getHandCards()->size(), 0);
  EXPECT_EQ(player2->getHand()->getHandCards()->size(), 0);
  EXPECT_EQ(player3->getHand()->getHandCards()->size(), 0);

  EXPECT_EQ(player1->getPhase(), "Issue Orders");
  EXPECT_EQ(player2->getPhase(), "Issue Orders");
  EXPECT_EQ(player3->getPhase(), "Issue Orders");
}


TEST(GameEngineTestSuite, GameEngineExecuteOrdersPhase)
{
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv, true);
  gameEngine.loadMap("res/TestMap1_valid.map");

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

  auto player1 = new Player(&gameEngine, new Hand(), "Rick Astley", "Aggressive");
  auto player2 = new Player(&gameEngine, new Hand(), "Bob Ross", "Aggressive");
  auto player3 = new Player(&gameEngine, new Hand(), "Felix Kjellberg", "Aggressive");

  // adding sets of territories just for testing
  auto map = gameEngine.getMap();
  auto continents = map->getContinents();

  for(auto t : *continents->at(0)->getTerritories()){
    player1->addTerritory(*t);
  }

  player2->addTerritory(*continents->at(2)->getTerritories()->at(0));

  for(auto t : *continents->at(1)->getTerritories()){
    player3->addTerritory(*t);
  }

  gameEngine.reinforcementPhase();
  gameEngine.issueOrdersPhase();

  // act
  gameEngine.executeOrdersPhase();


  // assert
  EXPECT_TRUE(player1->getOrdersListObject()->getList()->empty());
  EXPECT_TRUE(player2->getOrdersListObject()->getList()->empty());
  EXPECT_TRUE(player3->getOrdersListObject()->getList()->empty());

  EXPECT_EQ(player1->getPhase(), "Execute Orders Phase");
  EXPECT_EQ(player2->getPhase(), "Execute Orders Phase");
  EXPECT_EQ(player3->getPhase(), "Execute Orders Phase");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
