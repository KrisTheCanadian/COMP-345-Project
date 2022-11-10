#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameEngine/GameEngine.h"

TEST(GameEngineTestSuite, GameEngineInit)
{
  // arrange
  // act
  GameEngine gameEngine = GameEngine();
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
  GameEngine gameEngine = GameEngine();
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
  GameEngine gameEngine = GameEngine();
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

  auto player1 = new Player(&gameEngine, new Hand(), "Rick Astley");
  auto player2 = new Player(&gameEngine, new Hand(), "Bob Ross");
  auto player3 = new Player(&gameEngine, new Hand(), "Felix Kjellberg");

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
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
