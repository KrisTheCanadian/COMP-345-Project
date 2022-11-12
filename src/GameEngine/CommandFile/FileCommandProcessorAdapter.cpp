#include "FileCommandProcessorAdapter.h"


void FileCommandProcessorAdapter::commandLineToFile(FileLineReader* _flr){
    flr = _flr;
}

std::string FileCommandProcessorAdapter::readCommand(){
    return flr->readLineFromFile();
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(GameEngine* game, int argc, char** argv): CommandProcessor(game, argc, argv){}

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
