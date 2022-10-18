#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameEngine/GameEngine.h"
#include "Player/Player.h"

TEST(PlayerTestSuite, PlayerAddTerritories)
{
  // arrange
  GameEngine gameEngine = GameEngine();
  auto p = new Player(&gameEngine, new Hand());

  gameEngine.loadMap("res/TestMap1_valid.map");
  auto map_territories = gameEngine.getMap()->getTerritories();

  auto t1 = *map_territories->at(0);
  auto t2 = *map_territories->at(1);
  auto t3 = *map_territories->at(2);
  auto t4 = *map_territories->at(3);

  // act
  p->addTerritory(t1);
  p->addTerritory(t2);
  p->addTerritory(t3);
  p->addTerritory(t4);

  auto territories = *p->getTerritories();
  // assert
  EXPECT_EQ(territories.size(), 4);
}

TEST(PlayerTestSuite, PlayerRemoveTerritories)
{
  // arrange
  GameEngine gameEngine = GameEngine();
  auto p = new Player(&gameEngine, new Hand());

  gameEngine.loadMap("res/TestMap1_valid.map");
  auto map_territories = gameEngine.getMap()->getTerritories();

  auto t1 = *map_territories->at(0);
  auto t2 = *map_territories->at(1);
  auto t3 = *map_territories->at(2);
  auto t4 = *map_territories->at(3);

  p->addTerritory(t1);
  p->addTerritory(t2);
  p->addTerritory(t3);
  p->addTerritory(t4);

  // act
  p->removeTerritory(t1);
  p->removeTerritory(t2);
  p->removeTerritory(t3);
  p->removeTerritory(t4);

  auto territories = *p->getTerritories();
  // assert
  EXPECT_TRUE(territories.empty());
}

TEST(PlayerTestSuite, PlayerAttacknDefendTerritories)
{
  // arrange
  GameEngine gameEngine = GameEngine();
  auto p = new Player(&gameEngine, new Hand());

  gameEngine.loadMap("res/TestMap1_valid.map");
  auto map_territories = gameEngine.getMap()->getTerritories();

  auto t1 = *map_territories->at(0);
  auto t2 = *map_territories->at(1);
  auto t3 = *map_territories->at(2);
  auto t4 = *map_territories->at(3);

  p->addTerritory(t1);
  p->addTerritory(t2);
  p->addTerritory(t3);
  p->addTerritory(t4);

  // act
  auto defend = p->toDefend();
  auto attack = p->toAttack();
  // assert
  EXPECT_FALSE(defend.empty());
  EXPECT_FALSE(attack.empty());
}

TEST(PlayerTestSuite, PlayerIssueOrders)
{
  // arrange
  GameEngine gameEngine = GameEngine();
  auto p = new Player(&gameEngine, new Hand());

  gameEngine.loadMap("res/TestMap1_valid.map");
  auto map_territories = gameEngine.getMap()->getTerritories();
  // act
  p->issueOrder(CT_Bomb);
  p->issueOrder(CT_Airlift);
  p->issueOrder(CT_Blockade);
  p->issueOrder(CT_Diplomacy);
  // assert
  auto orderList = p->getOrdersListObject()->getList();
  EXPECT_EQ(orderList->size(), 4);
  EXPECT_EQ(orderList->at(0)->getLabel(), "Bomb");
  EXPECT_EQ(orderList->at(1)->getLabel(), "Airlift");
  EXPECT_EQ(orderList->at(2)->getLabel(), "Blockade");
  EXPECT_EQ(orderList->at(3)->getLabel(), "Negotiate");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
