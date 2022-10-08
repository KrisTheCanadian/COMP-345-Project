#include "Map/MapDriver.h"
#include "GameEngine/GameEngineDriver.h"
#include "Orders/OrdersDriver.h"
#include "Cards/CardsDriver.h"
#include "Player/PlayerDriver.h"

using namespace std;

int main()
{
  testLoadMaps();
  testGameStates();
  testOrdersLists();
  testCards();
  testPlayers();
  return 0;
}

