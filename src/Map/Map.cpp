#include "Map.h"

#include <utility>

void Map::validate()
{
  // TODO implement
}

void Map::addContinent(const std::shared_ptr<Continent>& continent)
{
  this->continents.push_back(continent);
}

void Map::addTerritory(const std::shared_ptr<Territory>& territory)
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

void Map::setTerritories(std::vector<std::shared_ptr<Territory>> _territories)
{
  this->territories = std::move(_territories);
}

void Map::setContinents(std::vector<std::shared_ptr<Continent>> _continents)
{
  this->continents = std::move(_continents);
}
