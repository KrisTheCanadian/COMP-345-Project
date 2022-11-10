#include <memory>
#include <gtest/gtest.h>
#include "GameEngine/GameEngine.h"

// Logging Order and OrderList
TEST(LoggerTestSuite, ExecuteAndAddOrder){


    auto gameEngine = new GameEngine;
    auto player = new Player(gameEngine, new Hand());
    gameEngine->addPlayer(player);
    auto observer = gameEngine->getLogObserver();
    std::string output;
    std::fstream file;
    file.open("gamelog.txt", std::ios::in | std::ios::out | std::ios::trunc);

    // Create order and attach observer
    auto order = (Bomb*) OrdersFactory::CreateOrder(CardType::CT_Bomb);
    ((Subject*)order)->attach((ILogObserver*)observer);
    order->execute();

    // Get orderList and attach observer
    auto orderList = player->getOrdersListObject();
    ((Subject*)orderList)->attach((ILogObserver*)observer);
    orderList->add(order);


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

EXPECT_TRUE(output == "ORDER: Order Executed -> Bomb order.ORDER LIST: Order List Added Bomb");
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