#include "GameEngine/GameEngineDriver.h"
#include "Orders/OrdersDriver.h"
#include "GameEngine/Command/CommandProcessingDriver.h"
#include "Logger/LoggingObserverDriver.h"
#include "GameEngine/TournamentDriver.h"

using namespace std;

int main(int argc, char** argv)
{
  testTournament(argc, argv);
  std::cout << std::endl;
  testGameLoop(argc, argv);
  std::cout << std::endl;
  testCommandProcessor(argc, argv);
  testStartupPhase(argc, argv);
  testOrderExecution();
  std::cout << std::endl;
  testLoggingObserver(argc, argv);
  return 0;
}

