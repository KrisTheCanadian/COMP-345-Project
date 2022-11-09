#include "GameEngineDriver.h"

void printInvalidCommand(const std::string& command){
  std::cout << "Incorrect Command: \"" << command << "\". Please input a correct command." << std::endl;
}

void testGameStates(){
  GameEngine gameEngine;

    gameEngine.startupPhase(true);
}
