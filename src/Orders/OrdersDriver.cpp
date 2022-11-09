#include "Orders.h"
#include "OrdersDriver.h"
#include "GameEngine/GameEngine.h"
using namespace std;

void testOrderExecution()
{
    // --------------------------------
    // DUMMY VALUES FOR TESTING
    // --------------------------------
    int id1 = 10;
    int id2 = 20;

    int reinforcementPool1 = 20;
    int reinforcementPool2 = 20;

    cout << "-> Creating territories" << endl;
    Territory* t1 = new Territory("t1");
    t1->addArmyUnits(10);
    Territory* t2 = new Territory("t2");
    t2->addArmyUnits(10);
    Territory* t3 = new Territory("t3");
    t3->addArmyUnits(10);
    Territory* t4 = new Territory("t4");
    t4->addArmyUnits(10);
    Territory* t5 = new Territory("t5");
    t5->addArmyUnits(10);

    t1->addAdjacentTerritory(t2);
    t2->addAdjacentTerritory(t1);
    t2->addAdjacentTerritory(t3);
    t3->addAdjacentTerritory(t2);
    t3->addAdjacentTerritory(t4);
    t3->addAdjacentTerritory(t5);
    t4->addAdjacentTerritory(t3);
    t4->addAdjacentTerritory(t5);
    t5->addAdjacentTerritory(t3);
    t5->addAdjacentTerritory(t4);

    vector<Territory*> tList1 = { t1,t2, t4 };
    vector<Territory*> tList2 = { t3, t5 };


    Deck* deck = new Deck;
    //TODO: Figure out how to create a fake deck with fake cards
    //deck->create_deck();

    Hand* hand1 = new Hand;
    Hand* hand2 = new Hand;

    for (int i = 0; i < 6; i++) {
        deck->draw(*hand1);
    }
    for (int i = 0; i < 6; i++) {
        deck->draw(*hand2);
    }

    cout << "-> Creating list of orders" << endl;
    OrdersList* ordersList1 = new OrdersList();
    OrdersList* ordersList2 = new OrdersList();
    OrdersFactory factory;

    ordersList1->add(factory.createOrder("deploy", nullptr, nullptr, nullptr, nullptr, nullptr));
    ordersList1->add(factory.createOrder("advance", nullptr, nullptr, nullptr, nullptr, nullptr));
    ordersList1->add(factory.createOrder("bomb", nullptr, nullptr, nullptr, nullptr, nullptr));
    ordersList1->add(factory.createOrder("blockade", nullptr, nullptr, nullptr, nullptr, nullptr));
    ordersList1->add(factory.createOrder("airlift", nullptr, nullptr, nullptr, nullptr, nullptr));
    ordersList1->add(factory.createOrder("negotiate", nullptr, nullptr, nullptr, nullptr, nullptr));

    ordersList2->add(factory.createOrder("deploy", nullptr, nullptr, nullptr, nullptr, nullptr));
    ordersList2->add(factory.createOrder("advance", nullptr, nullptr, nullptr, nullptr, nullptr));
    ordersList2->add(factory.createOrder("bomb", nullptr, nullptr, nullptr, nullptr, nullptr));
    ordersList2->add(factory.createOrder("blockade", nullptr, nullptr, nullptr, nullptr, nullptr));
    ordersList2->add(factory.createOrder("airlift", nullptr, nullptr, nullptr, nullptr, nullptr));
    ordersList2->add(factory.createOrder("negotiate", nullptr, nullptr, nullptr, nullptr, nullptr));


    Player* player1 = new Player(id1, reinforcementPool1, tList1, hand1, ordersList1);
    Player* player2 = new Player(id2, reinforcementPool2, tList2, hand2, ordersList2);

    cout << "-> Setting the players as territory owners" << endl;
    for (int i = 0; i < tList1.size(); i++) {
        tList1.at(i)->setOwnerId(player1->getId());
    }
    for (int i = 0; i < tList2.size(); i++) {
        tList2.at(i)->setOwnerId(player2->getId());
    }

    cout << "-> Adding the players to a list" << endl;
    Player* allPlayers = new Player();
    allPlayers->addPlayer(player1);
    allPlayers->addPlayer(player2);

    string sourceTerritory;
    string targetTerritory;

    int nbArmies;



//    auto gameEngine = new GameEngine;
//    auto player = new Player(gameEngine, new Hand());
//    gameEngine->addPlayer(player);
//    OrdersFactory factory;
//    auto orderList = player->getOrdersListObject();
//
//    cout << "-> Order Addition" << endl;
//    orderList->add(factory.createOrder("deploy", nullptr, nullptr, nullptr, nullptr, nullptr));
//    orderList->add(factory.createOrder("advance", nullptr, nullptr, nullptr, nullptr, nullptr));
//    orderList->add(factory.createOrder("bomb", nullptr, nullptr, nullptr, nullptr, nullptr));
//    orderList->add(factory.createOrder("blockade", nullptr, nullptr, nullptr, nullptr, nullptr));
//    orderList->add(factory.createOrder("airlift", nullptr, nullptr, nullptr, nullptr, nullptr));
//    orderList->add(factory.createOrder("negotiate", nullptr, nullptr, nullptr, nullptr, nullptr));
//
//    cout << "-> Order Execution" << endl;
//    orderList->execute();
}
