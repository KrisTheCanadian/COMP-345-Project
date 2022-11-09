#pragma once

#include "GameEngine/GameEngine.h"
#include "Cards/Cards.h"
#include "Orders/Orders.h"
#include "Map/Map.h"

#include <vector>
using std::string;

class Territory;
enum CardType : int;
class GameEngine;
class Hand;
class OrdersList;

class Player {
private:
  static int nextId;
  int id;
  string phase;
  int reinforcementPool;
  std::vector<Territory*> territories;
  Hand* hand;
  OrdersList* orders;
  GameEngine* game;

public:
  // --------------------------------
  // Constructors
  // --------------------------------
  Player(GameEngine* game, Hand* cards);
  ~Player();
  Player(const Player &p);

  // --------------------------------
  // Operator Overloads
  // --------------------------------
  Player& operator=(const Player &other);

  // --------------------------------
  // Actions
  // --------------------------------
  std::vector<Territory *> toDefend();
  std::vector<Territory *> toAttack();

  void issueOrder(CardType cardType);
  void addTerritory(Territory& territory);
  void removeTerritory(Territory& territory);
  bool ownsAllTerritoryInContinent();

  // --------------------------------
  // Getters
  // --------------------------------
  Hand* getHand();
  OrdersList* getOrdersListObject();
  std::vector<Territory*>* getTerritories();
  int getId() const;
  string getPhase();
  int getReinforcementPool() const;

  // --------------------------------
  // Setters
  // --------------------------------
  void setPhase(string ph);
  void setReinforcementPool(int i);

public:
  friend std::ostream& operator <<(std::ostream &out, const Player &player);

};