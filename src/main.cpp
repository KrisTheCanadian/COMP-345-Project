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
  testCommandProcessor();
  testLoadMaps();
  testGameStates();
  testOrderExecution();
  testCards();
  testPlayers();
  testLoggingObserver();
  return 0;
}