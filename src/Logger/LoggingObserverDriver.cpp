#include "LoggingObserverDriver.h"
#include "Orders/Orders.h"
#include "GameEngine/Command/CommandProcessor.h"


void testLoggingObserver(){

  auto gameEngine = new GameEngine;
  auto player1 = new Player(gameEngine, new Hand(), "Player1");
  auto player2 = new Player(gameEngine, new Hand(), "Player2");

  player2->addTerritory(*gameEngine->getMap()->getTerritories()->at(0));

  auto observer = gameEngine->getLogObserver();
  // Create order and attach observer
  auto order = new Bomb(player2->getTerritories()->at(0), player1);
  ((Subject*)order)->attach((ILogObserver*)observer);

  // Get orderList and attach observer
  auto orderList = player1->getOrdersListObject();
  ((Subject*)orderList)->attach((ILogObserver*)observer);

  // Create commandProcessor and attach observer
  auto processor = new CommandProcessor(gameEngine);
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