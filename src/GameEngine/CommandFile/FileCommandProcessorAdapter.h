#pragma once
#include "../Command/CommandProcessor.h"
#include "FileLineReader.h"

class FileCommandProcessorAdapter : public CommandProcessor {
    
    private:
        FileLineReader *flr;
    public:
        void commandLineToFile(FileLineReader* _flr);
        std::string readCommand();

        FileCommandProcessorAdapter(GameEngine* game);

        // Copy constructor
        FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpA, GameEngine* game);
        
        //Operator Overloading
        friend std::ostream & operator << (std::ostream &out, const FileCommandProcessorAdapter &ffcpAr);
        FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& other);
};


