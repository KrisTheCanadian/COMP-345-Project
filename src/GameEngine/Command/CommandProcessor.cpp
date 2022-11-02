#include "CommandProcessor.h"
#include "Command.h"
#include <iostream>
#include <vector>

CommandProcessor::CommandProcessor(){
    commandCollection = {};
}

void CommandProcessor::getCommand(){
    string userInput = readCommand();
    Command* temp = validate(userInput);
    saveCommand(temp);
}

string CommandProcessor::readCommand(){
    string userInput;
    cout << "Please enter a command: " << endl;
    cin >> userInput;
    return userInput;
}

void CommandProcessor::saveCommand(Command* c){
    commandCollection.push_back(c);
}

Command* validate(string userInputCommand){

    Command *temp;
    Command tempCommandObject = Command(userInputCommand);
    temp = &tempCommandObject;

    switch(current_game_state){
        case GE_Start:
            if (userInputCommand == "loadmap"){current_game_state = GE_Map_Loaded;};
            temp->saveEffect("Map successfully loaded");
            return temp;

        case GE_Map_Loaded:
            if (userInputCommand == "validatemap"){current_game_state = GE_Map_Validated;};
            temp->saveEffect("Map successfully validated");
            return temp;

        case GE_Map_Validated:
            if (userInputCommand == "addplayer"){current_game_state = GE_Players_Added;};
            temp->saveEffect("Player successfully added");
            return temp;

        case GE_Players_Added:
            if (userInputCommand == "addplayer"){
                current_game_state = GE_Players_Added;
                temp->saveEffect("Player successfully added");
                return temp;
            };
            if(userInputCommand == "gamestart"){
                current_game_state = GE_Reinforcement;
                temp->saveEffect("Game successfully started");
                return temp;
            };

        case GE_Win:
            if (userInputCommand == "replay"){
                current_game_state = GE_Start;
                temp->saveEffect("Game successfully restarted");
                return temp;
            };
            if(userInputCommand == "quit"){
                cout << "Quit";
            };
    }

    temp->saveEffect("Error occured when trying to execute command");
    return temp;

}


void printInvalidCommand(const std::string& command){
  std::cout << "Incorrect Command: \"" << command << "\". Please input a correct command." << std::endl;
}

// void printCommandCollection(vector<Command*> commandCollection){
//     for(int i = 0; i < commandCollection.size(); i++){
//         cout << (*commandCollection[i]).getCommand() << " : " << (*commandCollection[i]).getEffect() << endl;
//     }
// }
