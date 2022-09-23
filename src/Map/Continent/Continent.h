#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Territory.h"

class Continent
{
private:
  std::string name;
  int bonus;
  std::vector<std::shared_ptr<Territory>> territories;

public:
  Continent(std::string name, int bonus);
  void addTerritory(std::shared_ptr<Territory> territory);
  std::string getName();
  int getBonus();
  std::vector<std::shared_ptr<Territory>> getTerritories();
};
