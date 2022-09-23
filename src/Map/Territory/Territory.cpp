#include "Territory.h"

Territory::Territory(std::string name)
{
  this->name = name;
}

void Territory::addAdjacentTerritory(std::shared_ptr<Territory> territory)
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