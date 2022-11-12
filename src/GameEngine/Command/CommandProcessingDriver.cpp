#include "CommandProcessingDriver.h"

void testCommandProcessor(int argc, char* argv[]) {
  auto gameEngine = new GameEngine(argc, argv);

    // Command line or file
    std::string decision;

    // More commands to enter or not
    bool moreCommands = true;
    std::string moreCommandsDecision;

    // Initializing file reading classes
    FileCommandProcessorAdapter adapter(gameEngine, argc, argv);

    // Initializing command line reading class
    CommandProcessor cpr = CommandProcessor(gameEngine, argc, argv);

    // get raw command line inputs
    auto inputCommandsRaw = cpr.getRawCommands();
    if(inputCommandsRaw->empty()){
      std::cout << "You must choose between -console or -file <filename>" << endl;
      exit(0);
    }

    // Command line
    if (inputCommandsRaw->at(0) == "-console"){
        do {
            cpr.getCommand();
            cpr.printCommandCollection(cpr.getCommandCollection());
            std::cout << "Please enter a command: ";
            getline(std::cin, moreCommandsDecision);
            std::cout << std::endl;
            if (!(moreCommandsDecision == "y")){
                moreCommands = false;
            }
        }while(moreCommands);


    // File
    } else if (inputCommandsRaw->at(0) == "-file"){

      // check for file name
      if(inputCommandsRaw->size() < 2) {
        std::cout << "You must give a file as an argument" << std::endl;
        exit(0);
      }

      gameEngine->getFlir()->setFile(inputCommandsRaw->at(0));

      // Adapter functionality
      adapter.commandLineToFile(gameEngine->getFlir());

      while(!gameEngine->getFlir()->getReadComplete()){

          adapter.getCommand();
      }

      adapter.printCommandCollection(adapter.getCommandCollection());

    }
    else {
        throw std::runtime_error("Invalid Command line arguments");
    }
}