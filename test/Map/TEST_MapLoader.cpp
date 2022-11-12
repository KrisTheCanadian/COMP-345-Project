#include <memory>
#include <gtest/gtest.h>
#include "Map/Map.h"
#include "GameEngine/GameEngine.h"

TEST(MapLoaderTestSuite, TestMap1LoadBasic)
{
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  // arrange
  GameEngine gameEngine = GameEngine(argc, argv);
  auto map = gameEngine.getMap();
  // act

  MapLoader::load("../res/TestMap1_valid.map", map);

  // assert
  // Map Name
  EXPECT_EQ(map->getName(), "TestMap1_valid.map");
  // Image Name
  EXPECT_EQ(map->getImage(), "Asia.bmp");
  // Author Name
  EXPECT_EQ(map->getAuthor(), "Rustin Terry");
  // Extra Properties
  EXPECT_TRUE(map->getWrap());
  EXPECT_TRUE(map->getScroll());
  EXPECT_TRUE(map->getWarn());

  // Scanned Correct Number of Continents & Territories
  EXPECT_EQ(map->getTerritories()->size(), 48);
  EXPECT_EQ(map->getContinents()->size(), 7);

  // check for nullptr in territories
  for(const auto t : *map->getTerritories()) {
      EXPECT_FALSE(t == nullptr);
  }

  // check for nullptr in continents
  for(const auto c : *map->getContinents()){
      EXPECT_FALSE(c == nullptr);
  }
}

TEST(MapLoaderTestSuite, TestMap1LoadTerritoriesCorrectly)
{
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  // arrange
  GameEngine gameEngine = GameEngine(argc, argv);
  auto map = gameEngine.getMap();

  // act
  MapLoader::load("../res/TestMap1_valid.map", map);

  auto territories = map->getTerritories();

  // assert

  // check first territory
  auto first = territories->at(0);
  EXPECT_EQ(first->getName(), "Saudi Arabia");
  EXPECT_EQ(first->getX(), 77);
  EXPECT_EQ(first->getY(), 295);
  EXPECT_EQ(first->getContinent()->getName(), "Arabian Peninsula");

  auto first_adj = first->getAdjacentTerritories();

  // check first territory adjacent in adj
  EXPECT_EQ(first_adj->at(0)->getName(), "Yemen");
  EXPECT_EQ(first_adj->at(0)->getX(), 89);
  EXPECT_EQ(first_adj->at(0)->getY(), 361);
  EXPECT_EQ(first_adj->at(0)->getContinent()->getName(), "Arabian Peninsula");

  // check all x & y are initialized
  for(const auto territory: *territories){
    EXPECT_TRUE(territory->getX() != -1);
    EXPECT_TRUE(territory->getY() != -1);
  }

  // check for null ptr in vector
  for(const auto territory: *territories){
    for(const auto& adj: *territory->getAdjacentTerritories()){
      EXPECT_TRUE(adj != nullptr);
      // x and y should be initialized
      EXPECT_TRUE(adj->getX() != -1);
      EXPECT_TRUE(adj->getY() != -1);

    }
  }
}

TEST(MapLoaderTestSuite, TestMap1LoadContinentsCorrectly){
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  // arrange
  GameEngine gameEngine = GameEngine(argc, argv);
  auto map = gameEngine.getMap();
  // act
  MapLoader::load("../res/TestMap1_valid.map", map);
  // assert
  auto continents = map->getContinents();

  EXPECT_EQ(continents->size(), 7);
  // check number of territories in first continent
  EXPECT_EQ(continents->at(0)->getTerritories()->size(), 7);
  // check if all territories in all continents are correctly initialized
  for(const auto& c: *continents){
    for(const auto& t: *c->getTerritories()){
      EXPECT_FALSE(t == nullptr);
      EXPECT_FALSE(t->getX() == -1);
      EXPECT_FALSE(t->getY() == -1);
      EXPECT_EQ(t->getContinent()->getName(), c->getName());
    }
  }

}

TEST(MaploaderTestSuite, TestMap1LoadValid){
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  // arrange
  GameEngine gameEngine = GameEngine(argc, argv);
  auto map = gameEngine.getMap();

  MapLoader::load("../res/TestMap1_valid.map", map);
  // act
  auto isValid = map->validate();
  // assert
  EXPECT_TRUE(isValid);
}

TEST(MaploaderTestSuite, TestMap4LoadValid){
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv);
  auto map = gameEngine.getMap();
  MapLoader::load("../res/TestMap4_valid.map", map);
  // act
  auto isValid = map->validate();
  // assert
  EXPECT_TRUE(isValid);
}

TEST(MaploaderTestSuite, TestMap2LoadInvalid) {
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv);
  auto map = gameEngine.getMap();
  MapLoader::load("../res/TestMap2_invalid.map", map);
  // act
  auto isValid = map->validate();
  // assert
  EXPECT_FALSE(isValid);
}

TEST(MaploaderTestSuite, TestMap3LoadInvalid){
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv);
  auto map = gameEngine.getMap();
  MapLoader::load("../res/TestMap3_invalid.map", map);
  // act
  auto isValid = map->validate();
  // assert
  EXPECT_FALSE(isValid);
}

TEST(MaploaderTestSuite, TestMap5LoadInvalidFormat){
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv);
  auto map = gameEngine.getMap();
  MapLoader::load("../res/TestMap5_invalid_format.map", map);
  // act
  auto isValid = map->validate();
  // assert
  EXPECT_FALSE(isValid);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}