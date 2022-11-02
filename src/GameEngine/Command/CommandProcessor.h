#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Command;


enum GameEngineState {
  GE_Start = 0,
  GE_Map_Loaded,
  GE_Map_Validated,
  GE_Players_Added,
  GE_Reinforcement,
  GE_Win
};

GameEngineState current_game_state = GE_Start;

class CommandProcessor{

    private:
        vector<Command*> commandCollection;
        string readCommand();
        void saveCommand(Command* c);

    public:
        void getCommand();
        CommandProcessor();
        Command* validate(string userInputCommand);
        void printInvalidCommand(string& command);
        void printCommandCollection(vector<Command*> commandCollection);

};