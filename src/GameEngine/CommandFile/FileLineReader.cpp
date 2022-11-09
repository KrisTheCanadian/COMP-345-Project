#include "FileLineReader.h"
#include <fstream>
#include <iostream>


FileLineReader::FileLineReader(){}

FileLineReader::FileLineReader(const FileLineReader &flr){
    fileName = flr.fileName;
    readComplete = flr.readComplete;
}

std::string FileLineReader::readLineFromFile(){

    std::ifstream fileInputStream(fileName);
    int maxLines = maxNumberOfLines(fileName);
    std::string line;
    
    if (fileInputStream.is_open() && !readComplete){
      GotoLine(fileInputStream, getCurrentLine());
      getline(fileInputStream, line);
      if (getCurrentLine() == maxLines){
        this->readComplete = true;
      }
      incrementCurrentLine();
      return line;
    } else {
      throw std::runtime_error("Could not open file");
    }
    
    return "";
}

std::ifstream& FileLineReader::GotoLine(std::ifstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

int FileLineReader::maxNumberOfLines(std::string _fileName){
  std::ifstream temp(_fileName);
  int lines_count = 0;
  std::string line;
  while (std::getline(temp , line)){
    lines_count++;
  }
  return lines_count;
}

void FileLineReader::setFile(std::string _fileName){
  fileName = _fileName;
}

bool FileLineReader::getReadComplete(){
  return this->readComplete;
}

int FileLineReader::getCurrentLine(){
  return this->currentLine;
}

void FileLineReader::incrementCurrentLine(){
  currentLine++;
}

std::ostream & operator << (std::ostream &out, const FileLineReader &flr)
{
    out << "Current file: " << flr.fileName << std::endl;
    return out;
}

FileLineReader& FileLineReader::operator=(const FileLineReader &other) {
  if(this == &other){
    return *this;
  }

  this->fileName = other.fileName;
  this->readComplete = other.readComplete;

  return *this;
}