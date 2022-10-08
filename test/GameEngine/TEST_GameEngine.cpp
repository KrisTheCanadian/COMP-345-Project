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

  // act
  GameEngine gameEngine = GameEngine();
  gameEngine.loadMap("res/TestMap1_valid.map");
  // assert
  auto map = gameEngine.getMap();
  EXPECT_FALSE(map == nullptr);
  EXPECT_FALSE(map->getTerritories()->empty());
  EXPECT_FALSE(map->getContinents()->empty());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
