#include "Map/MapDriver.h"
#include "GameEngine/GameEngineDriver.h"
#include "Orders/OrdersDriver.h"
#include "Cards/CardsDriver.h"
#include "Player/PlayerDriver.h"
#include "GameEngine/Command/CommandProcessingDriver.h"
#include "Logger/LoggingObserverDriver.h"

using namespace std;

int main()
{
  testGameLoop();
  testCommandProcessor();
  testLoadMaps();
  testGameStates();
  testOrdersLists();
  testCards();
  testPlayers();
  testLoggingObserver();
  return 0;
}