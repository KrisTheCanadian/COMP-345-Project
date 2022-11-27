#include "TournamentDriver.h"
#include "GameEngine.h"

void testTournament(int argc, char* argv[]){
//  tournament -M res/TestMap2_invalid.map res/TestMap1_valid.map -P Aggressive Aggressive -G 2 -D 20
  auto gameEngine = new GameEngine(argc, argv);
  gameEngine->startupPhase();
}