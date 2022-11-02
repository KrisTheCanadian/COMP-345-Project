#include "CommandProcessingDriver.h"
#include "CommandProcessor.h"
#include <iostream>

void testCommandProcessor() {
    CommandProcessor testCommandProcessor = CommandProcessor();
    testCommandProcessor.getCommand();
}
