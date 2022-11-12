#include "Map/MapDriver.h"
#include "GameEngine/GameEngineDriver.h"
#include "Orders/OrdersDriver.h"
#include "Cards/CardsDriver.h"
#include "Player/PlayerDriver.h"
#include "GameEngine/Command/CommandProcessingDriver.h"
#include "Logger/LoggingObserverDriver.h"

using namespace std;

int main(int argc, char** argv)
{
  testGameLoop(argc, argv);
  testCommandProcessor(argc, argv); // seg fault
  testLoadMaps();
  testGameStates(argc, argv);
  testOrderExecution();
  testCards(argc, argv);
  testPlayers();
  testLoggingObserver(argc, argv);
  return 0;
}

