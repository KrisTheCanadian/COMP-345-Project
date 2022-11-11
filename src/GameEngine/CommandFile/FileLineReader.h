#pragma once
#include <iostream>
#include <fstream>
#include <limits>
#include <utility>

class FileLineReader{

    private:
        std::string fileName;
        bool readComplete = false;
        int currentLine = 1;

    public:
    
        // Default constructor
        FileLineReader() = default;

        // Copy constructor
        FileLineReader(const FileLineReader &flr);

        // Reading line from file
        virtual std::string readLineFromFile();
        
        // Jump to num line number
        std::ifstream& GotoLine(std::ifstream& file, unsigned int num);
        
        // Return maximum number of lines in _fileName
        int maxNumberOfLines(const std::string& _fileName);
        
        // Relevant getters and setters
        void setFile(std::string _fileName);
        bool getReadComplete();
        int getCurrentLine();
        
        void incrementCurrentLine();

        //Operator Overloading
        friend std::ostream & operator << (std::ostream &out, const FileLineReader &flr);
        FileLineReader& operator=(const FileLineReader& other);
};