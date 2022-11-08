#include "GameEngineDriver.h"

void printInvalidCommand(const std::string& command){
  std::cout << "Incorrect Command: \"" << command << "\". Please input a correct command." << std::endl;
}

void testGameStates(){
  // create the instance of game_engine
  GameEngine gameEngine;
  // run game while not in a final state

    gameEngine.startupPhase(true);
//  // get user input
//  std::string input;
//  while(true){
//    std::cout << "Current Game State: " << gameEngine.getCurrentStateToString() << std::endl;
//    std::cout << "Please enter an action: ";
//    std::cin >> input;
//
//    switch(gameEngine.getCurrentState()){
//      case GE_Start:
//        if(input == "loadmap"){ gameEngine.setCurrentState(GameEngineState::GE_Map_Loaded); }
//        else { printInvalidCommand(input); }
//        break;
//      case GE_Map_Loaded:
//        if(input == "loadmap"){ continue; }
//        else if(input == "validatemap"){ gameEngine.setCurrentState(GameEngineState::GE_Map_Validated); }
//        else { printInvalidCommand(input); }
//        break;
//      case GE_Map_Validated:
//        if(input == "addplayer"){ gameEngine.setCurrentState(GameEngineState::GE_Players_Added); }
//        else { printInvalidCommand(input); }
//        break;
//      case GE_Players_Added:
//        if(input == "addplayer"){ continue; }
//        else if(input == "assigncountries"){ gameEngine.setCurrentState(GameEngineState::GE_Reinforcement); }
//        else { printInvalidCommand(input); }
//        break;
//      case GE_Reinforcement:
//        if(input == "issueorder"){ gameEngine.setCurrentState(GameEngineState::GE_Issue_Orders); }
//        else { printInvalidCommand(input); }
//        break;
//      case GE_Issue_Orders:
//        if(input == "issueorder"){ continue; }
//        else if(input == "endissueorders"){ gameEngine.setCurrentState(GameEngineState::GE_Execute_Orders); }
//        else { printInvalidCommand(input); }
//        break;
//      case GE_Execute_Orders:
//        if(input == "execorder"){ continue; }
//        else if(input == "execorders"){ gameEngine.setCurrentState(GameEngineState::GE_Reinforcement); }
//        else if(input == "win"){ gameEngine.setCurrentState(GameEngineState::GE_Win); }
//        else { printInvalidCommand(input); }
//        break;
//      case GE_Win:
//        if(input == "play"){ gameEngine.setCurrentState(GameEngineState::GE_Start); }
//        else if(input == "end"){ return; }
//        else { printInvalidCommand(input); }
//        break;
//    }
//    std:: cout << "------------------------------" << std::endl;
//  }
}
