#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameEngine/GameEngine.h"
#include "Player/Player.h"

TEST(PlayerTestSuite, PlayerAddTerritories)
{
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv, true);
  auto p = new Player(&gameEngine, new Hand(), "Bob", "Aggressive");

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
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv, true);
  auto p = new Player(&gameEngine, new Hand(), "Bob", "Aggressive");

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
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv, true);
  auto p1 = new Player(&gameEngine, new Hand(), "Bob", "Aggressive");
  auto p2 = new Player(&gameEngine, new Hand(), "Joe", "Aggressive");

  gameEngine.loadMap("res/TestMap1_valid.map");
  auto mapContinents = gameEngine.getMap()->getContinents();
  auto continentOneTerritories = *mapContinents->at(0)->getTerritories();

  auto players = *gameEngine.getPlayers();

  for(int i = 0; i < continentOneTerritories.size(); i++){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,100);
    int randomReinforcement = (int) dist6(rng);

    auto t = continentOneTerritories.at(i);
    t->setArmies(randomReinforcement);
    players.at(i % players.size())->addTerritory(*t);
  }

  // set armies for testing

  // act
  auto defend1 = p1->toDefend();
  auto attack1 = p1->toAttack();

  auto defend2 = p1->toDefend();
  auto attack2 = p1->toAttack();

  // assert
  EXPECT_FALSE(defend1.empty());
  EXPECT_FALSE(attack1.empty());

  EXPECT_FALSE(defend2.empty());
  EXPECT_FALSE(attack2.empty());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
