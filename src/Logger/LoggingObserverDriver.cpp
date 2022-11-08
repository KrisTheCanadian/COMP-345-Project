#include "LoggingObserverDriver.h"
#include "Orders/Orders.h"


void testLoggingObserver(){

  auto gameEngine = new GameEngine;
  auto player = new Player(gameEngine, new Hand());
  gameEngine->addPlayer(player);
  auto orderList = player->getOrdersListObject();

  auto order = (Bomb*) OrdersFactory::CreateOrder(CardType::CT_Bomb);
  auto observer = new LogObserver();
  ((Subject*)order)->attach((ILogObserver*)observer);
  orderList->add(order);
  orderList->execute();
}