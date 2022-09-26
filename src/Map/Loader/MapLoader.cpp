#include "MapLoader.h"

std::shared_ptr<Map> MapLoader::load(const std::string& path)
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
  return std::make_shared<Map>(this->map);
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
          this->map.setScroll(value == "yes");
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
        std::shared_ptr<Continent> continent = std::make_shared<Continent>(name, std::stoi(value));
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
        std::shared_ptr<Territory> territory = nullptr;

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
            territory = std::make_shared<Territory>(name);
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
            territory->setX(std::stoi(value));
              continue;
          }
          // y
          else if (territory->getY() == -1)
          {
            territory->setY(std::stoi(value));
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
              if (territory == nullptr)
              {
                throw std::runtime_error("Invalid territory: " + value);
              }

              territory->addAdjacentTerritory(territories[value]);
            }
            else
            {
              std::shared_ptr<Territory> adjacentTerritory;
              // check inside territories to create
              if(this->territoriesToCreate.find(value) != this->territoriesToCreate.end()){
                // use previously created
                adjacentTerritory = territoriesToCreate[value];
              } else {
                // create new territory
                adjacentTerritory = std::make_shared<Territory>(value);
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
