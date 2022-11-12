#pragma once

#include <iostream>
#include <string>
#include "GameEngine.h"

// tester for main driver
void testGameStates(int argc, char** argv);
// tester for game loop
void testGameLoop(int argc, char** argv);
// helper function to print invalid command to std out
void printInvalidCommand(std::string& command);