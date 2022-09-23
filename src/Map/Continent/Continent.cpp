#include "Continent.h"

Continent::Continent(std::string name, int bonus)
{
  this->name = name;
  this->bonus = bonus;
}

void Continent::addTerritory(std::shared_ptr<Territory> territory)
{
  this->territories.push_back(territory);
}

std::string Continent::getName()
{
  return this->name;
}

int Continent::getBonus()
{
  return this->bonus;
}

std::vector<std::shared_ptr<Territory>> Continent::getTerritories()
{
  return this->territories;
}
