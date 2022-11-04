#include "CommandProcessingDriver.h"
#include "CommandProcessor.h"
#include <iostream>

void testCommandProcessor() {
    CommandProcessor testCommandProcessor = CommandProcessor();
    while(true){
        testCommandProcessor.getCommand();
        testCommandProcessor.printCommandCollection(testCommandProcessor.getCommandCollection());
    };
}