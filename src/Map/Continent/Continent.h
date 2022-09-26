#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "Territory.h"

class Territory;

class Continent
{
private:
  std::string name;
  int bonus;
  std::vector<std::shared_ptr<Territory>> territories;

public:
  Continent(std::string name, int bonus);
  void addTerritory(const std::shared_ptr<Territory>& territory);
  std::string getName();
  int getBonus() const;
  std::vector<std::shared_ptr<Territory>> getTerritories();
};
