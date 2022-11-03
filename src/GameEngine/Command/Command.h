#pragma once
#include <iostream>

class Command{

    private:
        std::string command;
        std::string effect;    

    public:

        //Constructors
        Command(std::string _command);
        Command(const Command &c);

        //Getters & Setters 
        void saveEffect(std::string effect);
        std::string getEffect();
        std::string getCommand();
        void setCommand(std::string _command);

        //Operator Overloading
        friend std::ostream & operator << (std::ostream &out, const Command &c);
        Command& operator=(const Command& other);
};