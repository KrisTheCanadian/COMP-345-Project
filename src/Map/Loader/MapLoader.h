#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "Map.h"

class MapLoader
{
private:
    enum ReadingState
    {
        ReadingState_Error,
        ReadingState_Idle,
        ReadingState_Start,
        ReadingState_Map,
        ReadingState_Continents,
        ReadingState_Territories
    };
    Map map;
    // territory name -> List of Adjacent territories
    std::unordered_map<std::string, std::vector<std::string>> territories;
    std::unordered_map<std::string, int> continents;
    ReadingState state = ReadingState_Idle;

private:
    void load(std::string path);
    void parse(std::string &line);
};