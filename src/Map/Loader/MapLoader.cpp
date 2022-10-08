#include "MapLoader.h"


void MapLoader::load(const std::string& path, Map* out_map)
{
  std::ifstream input_file(path, std::ios::in);
  std::string line;

  // check if file is open
  if (!input_file.is_open())
  {
    throw std::runtime_error("Could not open file: " + path);
  }

  MapLoaderState state;

  std::string map_name = path.substr(path.find_last_of('/') + 1);
  out_map->setName(map_name);

  while (getline(input_file, line))
  {
    line = trim(line);
    if(line.empty()) { continue; }

    parseLine(line, out_map, state);
  }

  state.parseState = ReadingState_Idle;
  input_file.close();
}

void MapLoader::parseLine(std::string &line, Map* map, MapLoaderState& mapLoaderState)
{

  switch (mapLoaderState.parseState)
  {
  case ReadingState_Idle:
    if (line == "[Map]")
    {
      mapLoaderState.parseState = ReadingState_Map;
    }
    else
    {
      throw std::runtime_error("Invalid map file");
    }
    break;

  case ReadingState_Map:
    if (line == "[Continents]")
    {
      mapLoaderState.parseState = ReadingState_Continents;
    }
    else
    {
      std::string delimiter = "=";
      if (line.find(delimiter) != std::string::npos)
      {
        std::string key = line.substr(0, line.find(delimiter));
        std::string value = line.substr(line.find(delimiter) + 1, line.length());
        if (key == "author")
        {
          map->setAuthor(value);
        }
        else if (key == "image")
        {
          map->setImage(value);
        }
        else if (key == "wrap")
        {
          map->setWrap(value == "yes");
        }
        else if (key == "scroll")
        {
          map->setScroll(value == "horizontal");
        }
        else if (key == "warn")
        {
          map->setWarn(value == "yes");
        }
      }
    }
    break;

  case ReadingState_Continents:
    if (line == "[Territories]")
    {
      mapLoaderState.parseState = ReadingState_Territories;
    }
    else
    {
      // parse continents
      std::string delimiter = "=";
      if (line.find(delimiter) != std::string::npos)
      {
        std::string name = line.substr(0, line.find(delimiter));
        std::string value = line.substr(line.find(delimiter) + 1, line.length());
        Continent* continent;
        try {
          continent = new Continent(name, std::stoi(value));
        } catch (std::invalid_argument& e){
          throw std::runtime_error("Map Formatting Error: Invalid Continent Bonus.");
        } catch (std::out_of_range& e) {
          throw std::runtime_error("Map Formatting Error: Continent Bonus Coordinate Out Of Range.");
        }

        map->addContinent(continent);
        mapLoaderState.continents[name] = continent;
      }
    }
    break;
    // FORMAT: Territory name, x, y, continent, adjacent territories
  case ReadingState_Territories:

        // parse territories
        std::string delimiter = ",";
        // Territory
        Territory* territory = nullptr;

        if (line.find(delimiter) != std::string::npos)
        {
          std::string name = line.substr(0, line.find(delimiter));
          line = line.substr(line.find(delimiter) + 1, line.length());

          // check if territory exists in territoriesToCreate before creating a new one
          if (mapLoaderState.territoriesToCreate.find(name) != mapLoaderState.territoriesToCreate.end())
          {
            territory = mapLoaderState.territoriesToCreate[name];
            // remove from territoriesToCreate
            mapLoaderState.territoriesToCreate.erase(name);
          }
          else
          {
            territory = new Territory(name);
          }
        }

        // parse the rest of the line
        while (!line.empty())
        {
          auto delimiter_location = line.find(delimiter);
          std::string value = line.substr(0, delimiter_location);
          line = delimiter_location == std::string::npos ? "" : line.substr(delimiter_location + 1, line.length());

          // x
          if (territory->getX() == -1)
          {
            try{
              territory->setX(std::stoi(value));
            } catch (std::invalid_argument& e){
              throw std::runtime_error("Map Formatting Error: Invalid X Coordinate.");
            } catch (std::out_of_range& e) {
              throw std::runtime_error("Map Formatting Error: X Coordinate Out Of Range.");
            }
              continue;
          }
          // y
          else if (territory->getY() == -1)
          {
            try{
              territory->setY(std::stoi(value));
            } catch (std::invalid_argument& e){
              throw std::runtime_error("Map Formatting Error: Invalid Y Coordinate.");
            } catch (std::out_of_range& e) {
              throw std::runtime_error("Map Formatting Error: Y Coordinate Out Of Range.");
            }
              continue;
          }
          // continent
          else if (territory->getContinent() == nullptr)
          {
            // check if continents exists in hashmap
            if (mapLoaderState.continents.find(value) == mapLoaderState.continents.end())
            {
              throw std::runtime_error("Invalid continent: " + value);
            }
            else
            {
              territory->setContinent(mapLoaderState.continents[value]);
              mapLoaderState.continents[value]->addTerritory(territory);
            }
              continue;
          }
          // adjacent territories
          else
          {
            // check if territory exists in hashmap
            if (mapLoaderState.territories.find(value) != mapLoaderState.territories.end())
            {
              territory->addAdjacentTerritory(mapLoaderState.territories[value]);
            }
            else
            {
              Territory* adjacentTerritory;
              // check inside territories to create
              if(mapLoaderState.territoriesToCreate.find(value) != mapLoaderState.territoriesToCreate.end()){
                // use previously created
                adjacentTerritory = mapLoaderState.territoriesToCreate[value];
              } else {
                // create new territory
                adjacentTerritory = new Territory(value);
              }
              territory->addAdjacentTerritory(adjacentTerritory);
              // add to territoriesToCreate
              mapLoaderState.territoriesToCreate[value] = adjacentTerritory;
            }
        }
    }
      mapLoaderState.territories[territory->getName()] = territory;
      map->addTerritory(territory);
      break;
    }
}

// Utils
std::string MapLoader::ltrim(const std::string &s)
{
  size_t start = s.find_first_not_of(" \n\r\t\f\v");
  return (start == std::string::npos) ? "" : s.substr(start);
}

std::string MapLoader::rtrim(const std::string &s)
{
  size_t end = s.find_last_not_of(" \n\r\t\f\v");
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string MapLoader::trim(const std::string &s) {
  return rtrim(ltrim(s));
}
