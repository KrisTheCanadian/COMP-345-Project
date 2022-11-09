#pragma once

#include "GameEngine/GameEngine.h"
#include "Cards/Cards.h"
#include "Orders/Orders.h"
#include "Map/Map.h"

#include <vector>

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
  std::string name;

public:
  // --------------------------------
  // Constructors
  // --------------------------------
  Player(GameEngine* game, Hand* cards, std::string  name);
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

  void issueOrder();
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
  std::string getPhase();
  std::string* getPlayerName();
  string getPhase();
  int getReinforcementPool() const;
  std::string getName() const;

  // --------------------------------
  // Setters
  // --------------------------------
  void setPhase(std::string ph);
  void setReinforcementPool(int i);

public:
  friend std::ostream& operator <<(std::ostream &out, const Player &player);

};