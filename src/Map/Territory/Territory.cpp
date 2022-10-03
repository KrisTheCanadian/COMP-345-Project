#include "Territory.h"

Territory::Territory(std::string name)
{
  this->name = std::move(name);
}

void Territory::addAdjacentTerritory(const std::shared_ptr<Territory>& territory)
{
  this->adjacentTerritories.push_back(territory);
}

std::string Territory::getName()
{
  return this->name;
}

std::vector<std::shared_ptr<Territory>> Territory::getAdjacentTerritories()
{
  return this->adjacentTerritories;
}

int Territory::getX() const
{
  return this->x;
}

int Territory::getY() const
{
  return this->y;
}

void Territory::setX(int _x)
{
  this->x = _x;
}

void Territory::setY(int _y)
{
  this->y = _y;
}

std::shared_ptr<Continent> Territory::getContinent()
{
  return this->continent;
}

void Territory::setContinent(std::shared_ptr<Continent> c)
{
  this->continent = std::move(c);
}