#include "Map.h"

bool Map::validate()
{
  return isMapStronglyConnected() && isTerritories1to1Continents();
}

void Map::DFS(const std::shared_ptr<Territory>& territory, std::vector<std::shared_ptr<Territory>> &visited)
{
  visited.push_back(territory);
  for (auto &adjacent : territory->getAdjacentTerritories())
  {
    if (std::find(visited.begin(), visited.end(), adjacent) == visited.end())
    {
      DFS(adjacent, visited);
    }
  }
}

bool Map::isTerritoryStronglyConnected(const std::shared_ptr<Territory>& territory)
{
  std::vector<std::shared_ptr<Territory>> visited;
  DFS(territory, visited);
  return visited.size() == territories.size();
}

bool Map::isMapStronglyConnected()
{
  return std::all_of(territories.begin(), territories.end(), [this](
      const std::shared_ptr<Territory>& t)
      {
          auto val = isTerritoryStronglyConnected(t);
          return val;
      });
}

bool Map::isTerritories1to1Continents()
{
  return std::all_of(continents.begin(), continents.end(), [](const std::shared_ptr<Continent>& c){return !c->getTerritories().empty();});
}

void Map::addContinent(const std::shared_ptr<Continent> &continent)
{
  this->continents.push_back(continent);
}

void Map::addTerritory(const std::shared_ptr<Territory> &territory)
{
  this->territories.push_back(territory);
}

// --------------------------------------------------
// Getters
// --------------------------------------------------
std::string Map::getName()
{
  return this->name;
}

std::string Map::getImage()
{
  return this->image;
}

std::string Map::getAuthor()
{
  return this->author;
}

bool Map::getWrap() const
{
  return this->wrap;
}

bool Map::getScroll() const
{
  return this->scroll;
}

bool Map::getWarn() const
{
  return this->warn;
}

std::vector<std::shared_ptr<Territory>> Map::getTerritories()
{
  return this->territories;
}

std::vector<std::shared_ptr<Continent>> Map::getContinents()
{
  return this->continents;
}

// --------------------------------------------------
// setters
// --------------------------------------------------

void Map::setName(std::string _name)
{
  this->name = std::move(_name);
}

void Map::setImage(std::string _image)
{
  this->image = std::move(_image);
}

void Map::setAuthor(std::string _author)
{
  this->author = std::move(_author);
}

void Map::setWrap(bool _wrap)
{
  this->wrap = _wrap;
}

void Map::setScroll(bool _scroll)
{
  this->scroll = _scroll;
}

void Map::setWarn(bool _warn)
{
  this->warn = _warn;
}
