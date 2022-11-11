#pragma once

#include "GameEngine/GameEngine.h"
#include "Cards/Cards.h"
#include "Orders/Orders.h"
#include "Map/Map.h"

#include <vector>
#include <utility>
#include <algorithm>

class Territory;
enum CardType : int;
class GameEngine;
class Hand;
class OrdersList;

class Player {
private:
  static int nextId;
  int id;
  std::string phase;
  int reinforcementPool;
  std::vector<Territory*> territories;
  Hand* hand;
  OrdersList* orders;
  GameEngine* game;
  std::string name;
  std::vector<Player*> friendlyPlayers;

public:
  // --------------------------------
  // Constructors
  // --------------------------------
  Player(GameEngine* game, Hand* cards, std::string name);
  ~Player();
  Player(const Player &p) = default;

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
  void addReinforcement(int reinforcement);
  int getContinentBonus();

  // --------------------------------
  // Setters
  // --------------------------------
  void setReinforcementPool(int n);
  void addFriendly(Player *pPlayer);
  void clearFriendly();

  // --------------------------------
  // Getters
  // --------------------------------
  Hand* getHand();
  OrdersList* getOrdersListObject();
  std::vector<Territory*>* getTerritories();
  int getId() const;
  std::string getPhase();
  int getReinforcementPool() const;
  std::string getName() const;

  // --------------------------------
  // Setters
  // --------------------------------
  void setPhase(std::string ph);

public:
  friend std::ostream& operator <<(std::ostream &out, const Player &player);
  bool canAttack(Player *pPlayer);
};