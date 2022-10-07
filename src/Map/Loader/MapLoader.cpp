#include "MapLoader.h"

Map* MapLoader::load(const std::string& path)
{
  std::ifstream input_file(path, std::ios::in);
  std::string line;

  // check if file is open
  if (!input_file.is_open())
  {
    throw std::runtime_error("Could not open file: " + path);
  }

  std::string map_name = path.substr(path.find_last_of('/') + 1);
  this->map.setName(map_name);

  while (getline(input_file, line))
  {
    // remove \r from line
    if (line[line.length() - 1] == '\r')
    {
      line = line.substr(0, line.length() - 1);
    }
    parse(line);
  }

  this->state = ReadingState_Idle;
  input_file.close();
  return &this->map;
}

void MapLoader::parse(std::string &line)
{

  switch (this->state)
  {
  case ReadingState_Idle:
    if (line == "[Map]")
    {
      this->state = ReadingState_Map;
    }
    else
    {
      throw std::runtime_error("Invalid map file");
    }
    break;

  case ReadingState_Map:
    if (line == "[Continents]")
    {
      this->state = ReadingState_Continents;
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
          this->map.setAuthor(value);
        }
        else if (key == "image")
        {
          this->map.setImage(value);
        }
        else if (key == "wrap")
        {
          this->map.setWrap(value == "yes");
        }
        else if (key == "scroll")
        {
          this->map.setScroll(value == "horizontal");
        }
        else if (key == "warn")
        {
          this->map.setWarn(value == "yes");
        }
      }
    }
    break;

  case ReadingState_Continents:
    if (line == "[Territories]")
    {
      this->state = ReadingState_Territories;
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

        this->map.addContinent(continent);
        this->continents[name] = continent;
      }
    }
    break;
    // FORMAT: Territory name, x, y, continent, adjacent territories
  case ReadingState_Territories:
      if(line.empty()){
          // blank line
          return;
      }
        // parse territories
        std::string delimiter = ",";
        // Territory
        Territory* territory = nullptr;

        if (line.find(delimiter) != std::string::npos)
        {
          std::string name = line.substr(0, line.find(delimiter));
          line = line.substr(line.find(delimiter) + 1, line.length());
          // check if territory exists in territoriesToCreate before creating a new one
          if (this->territoriesToCreate.find(name) != this->territoriesToCreate.end())
          {
            territory = this->territoriesToCreate[name];
            // remove from territoriesToCreate
            this->territoriesToCreate.erase(name);
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
            if (this->continents.find(value) == this->continents.end())
            {
              throw std::runtime_error("Invalid continent: " + value);
            }
            else
            {
              territory->setContinent(this->continents[value]);
              continents[value]->addTerritory(territory);
            }
              continue;
          }
          // adjacent territories
          else
          {
            // check if territory exists in hashmap
            if (this->territories.find(value) != this->territories.end())
            {
              territory->addAdjacentTerritory(territories[value]);
            }
            else
            {
              Territory* adjacentTerritory;
              // check inside territories to create
              if(this->territoriesToCreate.find(value) != this->territoriesToCreate.end()){
                // use previously created
                adjacentTerritory = territoriesToCreate[value];
              } else {
                // create new territory
                adjacentTerritory = new Territory(value);
              }
              territory->addAdjacentTerritory(adjacentTerritory);
              // add to territoriesToCreate
              this->territoriesToCreate[value] = adjacentTerritory;
            }
        }
    }
        this->territories[territory->getName()] = territory;
        this->map.addTerritory(territory);
        break;
    }


}

MapLoader::MapLoader(const MapLoader &other) {
  this->map = other.map;
  this->state = other.state;

  for(const auto& t : territoriesToCreate){
    this->territoriesToCreate[t.first] = t.second;
  }

  for(const auto& t: territories){
    this->territoriesToCreate[t.first] = t.second;
  }

  for(const auto& c : continents){
    this->continents[c.first] = c.second;
  }
}

MapLoader &MapLoader::operator=(const MapLoader &other) {
  if(this == &other){
    return *this;
  }

  this->map = other.map;
  this->territoriesToCreate = other.territoriesToCreate;
  this->state = other.state;
  this->continents = other.continents;
  this->territories = other.territories;
  return *this;
}

std::ostream &operator<<(std::ostream &stream, const MapLoader &other) {
  stream << "Maploader State: " << MapLoader::stateToString(other.state) << '\n';
  return stream;
}

std::string MapLoader::stateToString(MapLoader::ReadingState state) {
  switch (state) {
    case ReadingState_Idle:
      return "Idle";
    case ReadingState_Map:
      return "Reading Map";
    case ReadingState_Continents:
      return "Reading Continents";
    case ReadingState_Territories:
      return "Reading Territories";
    default:
      return "Invalid State";
  }
}

MapLoader::MapLoader() = default;
