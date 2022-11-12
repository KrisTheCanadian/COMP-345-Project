#include <memory>
#include <gtest/gtest.h>
#include "GameEngine/GameEngine.h"

// Logging Order and OrderList
TEST(LoggerTestSuite, ExecuteAndAddOrder){
  GameEngine gameEngine = GameEngine();
  gameEngine.loadMap("res/TestMap1_valid.map");

  // add cards to the gameEngine deck
  auto deck = gameEngine.getDeck();
  deck->addCardToDeck(new Card(CardType::CT_Bomb, &gameEngine));

  auto player1 = new Player(&gameEngine, new Hand(), "Rick Astley");
  auto player2 = new Player(&gameEngine, new Hand(), "Bob Ross");

  // adding sets of territories just for testing
  auto map = gameEngine.getMap();
  auto continents = map->getContinents();

  for(auto t : *continents->at(0)->getTerritories()){
    player1->addTerritory(*t);
  }

  player2->addTerritory(*continents->at(1)->getTerritories()->at(0));

  gameEngine.reinforcementPhase();
  gameEngine.issueOrdersPhase();
  gameEngine.executeOrdersPhase();

  auto observer = gameEngine.getLogObserver();
  std::string output;
  std::fstream file;
  file.open("gamelog.txt", std::ios::in | std::ios::out | std::ios::trunc);

  // create a scenario for the bomb
  // Create order and attach observer
  auto order = player1->decideCardOrderBomb();
  ((Subject*)order)->attach((ILogObserver*)observer);
  order->execute();

  // Get orderList and attach observer
  auto orderList = player1->getOrdersListObject();
  ((Subject*)orderList)->attach((ILogObserver*)observer);
  orderList->add(order);

  orderList->execute();


  std::string line;
  if ( file.is_open() ) {
      while(file){
          std::getline(file, line);
          output += line;
      }
  }
  else {
      std::cout << "Couldn't open file\n";
  }

EXPECT_TRUE(output == "ORDER: Order Executed -> Bomb order.ORDER LIST: Order List Added BombORDER: Order Executed -> Bomb order.");
}

// Logging GameState
TEST(LoggerTestSuite, GameStateChange){


    auto gameEngine = new GameEngine;
    std::string output;
    std::fstream file;
    file.open("gamelog.txt", std::ios::in | std::ios::out | std::ios::trunc);

    // TEST GAME STATE CHANGE
    gameEngine->setCurrentState(GE_Map_Loaded);

    std::string line;
    if ( file.is_open() ) {
        while(file){
            std::getline (file, line);
            output += line;
        }
    }
    else {
        std::cout << "Couldn't open file\n";
    }

    EXPECT_TRUE(output == "GAME ENGINE: State transition to Map Loaded");
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}