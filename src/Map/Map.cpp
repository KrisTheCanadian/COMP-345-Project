#include "Map.h"

void Map::validate()
{
  // TODO implement
}

void Map::addContinent(std::shared_ptr<Continent> continent)
{
  this->continents.push_back(continent);
}

void Map::addTerritory(std::shared_ptr<Territory> territory)
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

bool Map::getWrap()
{
  return this->wrap;
}

bool Map::getScroll()
{
  return this->scroll;
}

bool Map::getWarn()
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

void Map::setName(std::string name)
{
  this->name = name;
}

void Map::setImage(std::string image)
{
  this->image = image;
}

void Map::setAuthor(std::string author)
{
  this->author = author;
}

void Map::setWrap(bool wrap)
{
  this->wrap = wrap;
}

void Map::setScroll(bool scroll)
{
  this->scroll = scroll;
}

void Map::setWarn(bool warn)
{
  this->warn = warn;
}

void Map::setTerritories(std::vector<std::shared_ptr<Territory>> territories)
{
  this->territories = territories;
}

void Map::setContinents(std::vector<std::shared_ptr<Continent>> continents)
{
  this->continents = continents;
}
