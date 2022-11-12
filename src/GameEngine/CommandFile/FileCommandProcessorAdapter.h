#pragma once
#include <iostream>
#include "../Command/CommandProcessor.h"
#include "FileLineReader.h"

class FileCommandProcessorAdapter : public CommandProcessor {
    
    private:
        FileLineReader *flr = nullptr;
    public:
        void commandLineToFile(FileLineReader* _flr);
        std::string readCommand() override;
        ~FileCommandProcessorAdapter() override = default;
        FileCommandProcessorAdapter(GameEngine* game, int argc, char** argv);

        // Copy constructor
        FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpA) = default;
        
        //Operator Overloading
        friend std::ostream & operator << (std::ostream &out, const FileCommandProcessorAdapter &ffcpAr);
        FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& other);
};
