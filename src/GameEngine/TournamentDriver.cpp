#include "TournamentDriver.h"
#include "GameEngine.h"
#include <iostream>

void testTournament(int argc, char* argv[]){
  auto gameEngine = new GameEngine(argc, argv);
  std::string option = "1";
  std::cout << "Do you want to enter tournament mode via console or via file?" << std::endl;
  std::cout << "1. Console" << std::endl;
  std::cout << "2. File" << std::endl;
  std::cout << "-> ";
  getline(std::cin, option);


  if(option == "1"){
    gameEngine->startupPhase();
  }
  else if(option == "2"){
    std::string fileName;
    std::cout << "Enter the file name: ";
    std::cin >> fileName;
    gameEngine->getCommandProcessor()->FileTournamentFunctionInput(fileName);
  }
  else{
    exit(0);
  }

}