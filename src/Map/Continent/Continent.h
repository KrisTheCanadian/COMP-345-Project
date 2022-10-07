#pragma once

#include <string>
#include <vector>
#include <utility>

#include "Territory.h"

class Territory;

class Continent
{
private:
  std::string name;
  int bonus;
  std::vector<Territory*> territories;

public:
  Continent(std::string name, int bonus);

  Continent(const Continent& other);
  Continent& operator=(const Continent& other);

  void addTerritory(Territory* territory);
  std::string getName();
  int getBonus() const;
  std::vector<Territory *> * getTerritories();

public:
  friend std::ostream& operator<<(std::ostream& stream, const Continent& other);
};
