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
    // territory name -> Territory
    std::unordered_map<std::string, Territory*> territories;

    // territories to add to the map
    std::unordered_map<std::string, Territory*> territoriesToCreate;

    // continent name -> Continent
    std::unordered_map<std::string, Continent*> continents;

    ReadingState state = ReadingState_Idle;

public:
  Map * load(const std::string& path);
  void parse(std::string &line);

  MapLoader(const MapLoader &other);
  MapLoader& operator=(const MapLoader& other);

  static std::string stateToString(ReadingState state);

  MapLoader();

public:
  friend std::ostream& operator<<(std::ostream& stream, const MapLoader& other);
};