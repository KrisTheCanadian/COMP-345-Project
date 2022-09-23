#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "Map.h"

class MapLoader
{
private:
    enum ReadingState
    {
        ReadingState_Idle,
        ReadingState_Map,
        ReadingState_Continents,
        ReadingState_Territories
    };
    Map map;
    // territory name -> Territory Shared Pointer
    std::unordered_map<std::string, std::shared_ptr<Territory>> territories;

    // territories to add to the map
    std::unordered_map<std::string, std::shared_ptr<Territory>> territoriesToCreate;

    // continent name -> Continent Shared Pointer
    std::unordered_map<std::string, std::shared_ptr<Continent>> continents;

    ReadingState state = ReadingState_Idle;

public:
    Map* load(const std::string& path);
    void parse(std::string &line);
};