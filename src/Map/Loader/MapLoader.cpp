#include <fstream>

#include "MapLoader.h"

void MapLoader::load(std::string path)
{
  std::ifstream input_file(path, std::ios::in);
  std::string line;

  // check if file is open
  if (!input_file.is_open())
  {
    throw std::runtime_error("Could not open file: " + path);
  }

  std::string map_name = path.substr(path.find_last_of("/") + 1).substr(0, path.find_last_of("."));
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
      }
    }
    break;

  case ReadingState_Territories:
    // parse territories
    std::string delimiter = ",";
    if (line.find(delimiter) != std::string::npos)
    {
      std::string name = line.substr(0, line.find(delimiter));
      std::string value = line.substr(line.find(delimiter) + 1, line.length());
      std::shared_ptr<Territory> territory = std::make_shared<Territory>(name);
      this->map.addTerritory(territory);
    }
    break;
  }
}
