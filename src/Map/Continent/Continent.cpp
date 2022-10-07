#include "Continent.h"

Continent::Continent(std::string name, int bonus)
{
  this->name = std::move(name);
  this->bonus = bonus;
}

void Continent::addTerritory(Territory* territory)
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

std::vector<Territory*>* Continent::getTerritories()
{
  return &this->territories;
}

std::ostream &operator<<(std::ostream &stream, const Continent &other) {
  stream << "Continent Name: " << other.name << '\n'
  << "Continent Bonus: " << other.bonus << '\n';

  stream << "Continent Territories: " << '\n';
  for(auto t: other.territories){
    stream << (*t) << '\n';
  }
  return stream;
}

Continent &Continent::operator=(const Continent &other) {
  if(&other == this){
    return *this;
  }
  this->name = other.name;
  this->bonus = other.bonus;
  this->territories = other.territories;

  return *this;
}

Continent::Continent(const Continent &other) = default;



