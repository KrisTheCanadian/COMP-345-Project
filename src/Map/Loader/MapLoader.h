#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "Map/Map.h"

class Map;

// Static Class
class MapLoader
{
private:

  // ----------------------------------------
  // State Enum
  // ----------------------------------------
  enum ReadingState
  {
    ReadingState_Idle,
    ReadingState_Map,
    ReadingState_Continents,
    ReadingState_Territories
  };

  // ----------------------------------------
  // Map Loader Data / State
  // ----------------------------------------
  struct MapLoaderState
  {
    std::unordered_map<std::string, Territory*> territories;
    // territories to add to the map
    std::unordered_map<std::string, Territory*> territoriesToCreate;
    // continent name -> Continent
    std::unordered_map<std::string, Continent*> continents;
    ReadingState parseState = ReadingState_Idle;
  };

  // ----------------------------------------
  // Map Loader Parse Line
  // ----------------------------------------
  static void parseLine(std::string &line, Map* map, MapLoaderState& mapLoaderState);

  // ----------------------------------------
  // Map Loader Line Trim Utilities
  // ----------------------------------------
  static std::string ltrim(const std::string &s);
  static std::string rtrim(const std::string &s);
  static std::string trim(const std::string &s);

public:
  // ----------------------------------------
  // Map Loader Load File
  // ----------------------------------------
  static void load(const std::string& path, Map* out_map);

  // ----------------------------------------
  // Map loader is a static class and should not have any constructor or assignment operator overloaded.
  // ----------------------------------------
  MapLoader() = delete;
  MapLoader(const MapLoader &other) = delete;
  MapLoader& operator=(const MapLoader& other) = delete;

public:
  // ----------------------------------------
  // Map loader cannot be instantiated and therefore cannot be printed out.
  // ----------------------------------------
  friend std::ostream& operator<<(std::ostream& stream, const MapLoader& other) = delete;
};