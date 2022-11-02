#pragma once
#include <iostream>

using namespace std;

class Command{

    private:
        string command;
        string effect;    

    public:
        Command(string _command);
        ~Command();
        Command(const Command &c);
        void saveEffect(string effect);
        string getEffect();
        string getCommand();

};