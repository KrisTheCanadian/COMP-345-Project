#pragma once
#include <vector>
#include "OrdersList.h"
#include "Hand.h"
#include "Territory.h"

class Order;

class Player {
private:
  std::vector<Territory*> territories;
  Hand* cards;
  OrdersList* orders;

public:
  std::vector<Territory *> toDefend();
  std::vector<Territory *> toAttack();
  void issueOrder(Order& order);
  void addTerritory(Territory& territory);
  void removeTerritory(Territory& territory);
  std::vector<Territory*> getTerritories();
  ~Player();
  Player();
  Player(const Player &p);
  friend std::ostream& operator <<(std::ostream &out, const Player &player);
  Player& operator=(const Player &other);
};