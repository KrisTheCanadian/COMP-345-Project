#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "Map/Territory/Territory.h"

class Continent
{
private:
  std::string name;
  int bonus;
  std::vector<Territory*> territories;

public:
  // ----------------------------------------
  // Constructors
  // ----------------------------------------
  Continent(std::string name, int bonus);
  Continent(const Continent& other);


  // ----------------------------------------
  // Adders
  // ----------------------------------------
  void addTerritory(Territory* territory);

  // ----------------------------------------
  // Getters
  // ----------------------------------------
  std::string getName();
  int getBonus() const;
  std::vector<Territory *> * getTerritories();

  // ----------------------------------------
  // Operator Overloads
  // ----------------------------------------
  Continent& operator=(const Continent& other);
public:
  // ----------------------------------------
  // Ostream Overload
  // ----------------------------------------
  friend std::ostream& operator<<(std::ostream& stream, const Continent& other);
};
