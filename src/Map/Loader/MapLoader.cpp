#include <fstream>

#include "MapLoader.h"

void MapLoader::load(std::string path)
{
  std::ifstream file(path);
  std::string line;

  if (file.is_open())
  {
    while (getline(file, line))
    {
      parse(line);
    }
  }
  else
  {
    throw std::runtime_error("Could not open file: " + path);
  }
  this->state = ReadingState_Idle;
  file.close();
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

  case ReadingState_Map:
    if (line == "[Continents]")
    {
      this->state = ReadingState_Continents;
    }
    else
    {
      std::string delimiter = "=";
      size_t pos = 0;
      if (line.find(delimiter) != std::string::npos)
      {
        std::string token = line.substr(0, line.find(delimiter));
        std::string value = line.substr(line.find(delimiter) + 1, line.length());
        this->continents[token] = std::stoi(value);
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
      // delimiter is comma
      size_t pos = 0;
      std::string token;
      std::vector<std::string> tokens;
      while ((pos = line.find(",")) != std::string::npos)
      {
        token = line.substr(0, pos);
        tokens.push_back(token);
        line.erase(0, pos + 1);
      }
    }
  }
