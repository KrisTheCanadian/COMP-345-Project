#include "TournamentDriver.h"
#include "GameEngine.h"

void testTournament(int argc, char* argv[]){
  auto gameEngine = new GameEngine(argc, argv);
  gameEngine->startupPhase();
}