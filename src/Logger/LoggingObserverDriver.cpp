#include "LoggingObserverDriver.h"
#include "Orders/Orders.h"
#include "GameEngine/Command/CommandProcessor.h"


void testLoggingObserver(){

  auto gameEngine = new GameEngine;
  auto player = new Player(gameEngine, new Hand());
  gameEngine->addPlayer(player);
  auto observer = gameEngine->getLogObserver();

  // Create order and attach observer
  auto order = (Bomb*) OrdersFactory::CreateOrder(CardType::CT_Bomb);
  ((Subject*)order)->attach((ILogObserver*)observer);

  // Get orderList and attach observer
  auto orderList = player->getOrdersListObject();
  ((Subject*)orderList)->attach((ILogObserver*)observer);

  // Create commandProcessor and attach observer
  CommandProcessor *processor = new CommandProcessor(gameEngine);
  ((Subject*)processor)->attach((ILogObserver*)observer);

  // TEST GAME STATE CHANGE
  gameEngine->setCurrentState(GE_Map_Loaded);

  // TEST ADDITION OF ORDER TO ORDER LIST
  orderList->add(order);

  // TEST ORDER EXECUTION
  order->execute();

  // TEST EFFECT SAVED and COMMAND SAVED
  processor->getCommand();

}