#include "FileCommandProcessorAdapter.h"
#include <iostream>

void FileCommandProcessorAdapter::commandLineToFile(FileLineReader* _flr){
    flr = _flr;
}

std::string FileCommandProcessorAdapter::readCommand(){
    return flr->readLineFromFile();
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine* game): CommandProcessor(game){}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpA, GameEngine* game): CommandProcessor(game){
    flr = fcpA.flr;
}

std::ostream & operator << (std::ostream &out, const FileCommandProcessorAdapter &fcpA){
    out << "Adapter connected to: " << fcpA.flr << std::endl;
    return out;
}

FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter& other){
    if(this == &other){
        return *this;
    }

    this->flr = other.flr;

    return *this;
}