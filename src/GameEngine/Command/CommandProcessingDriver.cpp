#include "CommandProcessingDriver.h"

void testCommandProcessor() {

  auto gameEngine = new GameEngine;

    // Command line or file
    std::string decision;

    // More commands to enter or not
    bool moreCommands = true;
    std::string moreCommandsDecision;

    // Initializing file reading classes
    FileLineReader flr;
    FileCommandProcessorAdapter adapter(gameEngine);

    // Initializing command line reading class
    CommandProcessor cpr = CommandProcessor(gameEngine);


    // Get user input (command line or file)
    std::cout << "\nDo you want to read from the console or from a file?" << std::endl;
    std::cout << "Enter 1 for console or 0 for file" << std::endl;
    getline(std::cin, decision);

    // Command line
    if (decision == "1"){
        do {
            cpr.getCommand();
            cpr.printCommandCollection(cpr.getCommandCollection());
            std::cout << "Do you want to enter another command? (y/n)" << std::endl;
            getline(std::cin, moreCommandsDecision);
            if (!(moreCommandsDecision == "y")){
                moreCommands = false;
            }
        }while(moreCommands);


    // File
    } else if (decision == "0"){
        std::string fileName;
        std::cout << "Enter File Name: " << std::endl;
        std::cin >> fileName;
        flr.setFile(fileName);

        // Adapter functionality
        adapter.commandLineToFile(&flr);
        
        while(!flr.getReadComplete()){
            adapter.getCommand();
        }
        
        adapter.printCommandCollection(adapter.getCommandCollection());

    }
    else {
        throw std::runtime_error("Invalid User Input");
    }
}