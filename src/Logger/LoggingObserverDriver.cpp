#include "LoggingObserverDriver.h"


void testLoggingObserver(int argc, char** argv){

  auto gameEngine = new GameEngine(argc, argv);
  auto player1 = new Player(gameEngine, new Hand(), "Player1");
  auto player2 = new Player(gameEngine, new Hand(), "Player2");

  gameEngine->loadMap("../res/TestMap1_valid.map");

  player2->addTerritory(*gameEngine->getMap()->getTerritories()->at(0));

  auto observer = gameEngine->getLogObserver();
  // Create order and attach observer
  auto order = new Bomb(gameEngine, player2->getTerritories()->at(0), player1);
  ((Subject*)order)->attach((ILogObserver*)observer);

  // Get orderList and attach observer
  auto orderList = player1->getOrdersListObject();
  ((Subject*)orderList)->attach((ILogObserver*)observer);

  // Create commandProcessor and attach observer
  auto processor = new CommandProcessor(gameEngine, argc, argv);
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