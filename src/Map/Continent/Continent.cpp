#include "Continent.h"

#include <utility>

Continent::Continent(std::string name, int bonus)
{
  this->name = std::move(name);
  this->bonus = bonus;
}

void Continent::addTerritory(const std::shared_ptr<Territory>& territory)
{
  this->territories.push_back(territory);
}

std::string Continent::getName()
{
  return this->name;
}

int Continent::getBonus() const
{
  return this->bonus;
}

std::vector<std::shared_ptr<Territory>> Continent::getTerritories()
{
  return this->territories;
}
