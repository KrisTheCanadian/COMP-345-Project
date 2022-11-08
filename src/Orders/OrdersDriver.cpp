#include "Orders.h"
#include "OrdersDriver.h"
#include "GameEngine/GameEngine.h"

void testOrderExecution()
{
    auto gameEngine = new GameEngine;
    auto player = new Player(gameEngine, new Hand());
    gameEngine->addPlayer(player);
    OrdersFactory factory;
    auto orderList = player->getOrdersListObject();

    cout << "-> Order Addition" << endl;
    orderList->add(factory.createOrder("deploy", nullptr, nullptr, nullptr, nullptr, nullptr));
    orderList->add(factory.createOrder("advance", nullptr, nullptr, nullptr, nullptr, nullptr));
    orderList->add(factory.createOrder("bomb", nullptr, nullptr, nullptr, nullptr, nullptr));
    orderList->add(factory.createOrder("blockade", nullptr, nullptr, nullptr, nullptr, nullptr));
    orderList->add(factory.createOrder("airlift", nullptr, nullptr, nullptr, nullptr, nullptr));
    orderList->add(factory.createOrder("negotiate", nullptr, nullptr, nullptr, nullptr, nullptr));

    cout << "-> Order Execution" << endl;
    orderList->execute();
}
