#include "Command.h"
#include <iostream>

using namespace std;


Command::Command(string _command){
    command = _command;
    effect = "Command has not been executed yet";
}

Command::Command(const Command &c){
    command = c.command;
    effect = c.effect;
}

void Command::saveEffect(string _effect){
    effect = _effect;
}

// string getEffect(){
//     return effect;
// }

// string getCommand(){
//     return command;
// }