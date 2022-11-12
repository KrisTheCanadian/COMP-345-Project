#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <utility>

class Continent;
class Player;

class Territory
{
private:
    Continent* continent;
    std::string name;
    std::vector<Territory*> adjacentTerritories;

    int armies = 0;
    Player* player = nullptr;

    int x = -1;
    int y = -1;

public:
  // ----------------------------------------
  // Constructors
  // ----------------------------------------
  explicit Territory(std::string name);
  Territory(const Territory &other);

  std::string getName();
  std::vector<Territory *>* getAdjacentTerritories();


  // ----------------------------------------
  // getters and setters
  // ----------------------------------------

  Player* getPlayer();
  void setPlayer(Player*);

  int getArmies() const;
  void setArmies(int);

  int getX() const;
  int getY() const;

  void setX(int x);
  void setY(int y);

  // ----------------------------------------
  // adders and removers
  // ----------------------------------------

  Continent* getContinent();
  void setContinent(Continent* c);

  int removeArmyUnits(int);
  int addArmyUnits(int);

  void addAdjacentTerritory(Territory* territory);

  // ----------------------------------------
  // Operator Overloads
  // ----------------------------------------
  Territory& operator=(const Territory& other);

public:
  // ----------------------------------------
  // ostream overload
  // ----------------------------------------
    friend std::ostream& operator<<(std::ostream& stream, const Territory& other);
};
