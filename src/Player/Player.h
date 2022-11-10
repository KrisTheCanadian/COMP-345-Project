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
  int reinforcementPool;
  std::vector<Territory*> territories;
  std::vector<Player*> players;
  Hand* hand;
  OrdersList* orders;
  GameEngine* game;
  std::vector<int> friendlyPlayers; // returns all the players who you can not attack for the remainder of the turn

public:
  // --------------------------------
  // Constructors
  // --------------------------------
  Player() = default;;
  Player(GameEngine* game, Hand* cards);
  Player(int id, int reinforcementPool, std::vector<Territory*> territories, Hand* cards, OrdersList* orders); //constructor for the OrdersDriver
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

  // --------------------------------
  // Setters
  // --------------------------------
  void setReinforcementPool(int n);

  // --------------------------------
  // Getters
  // --------------------------------
  Hand* getHand();
  OrdersList* getOrdersListObject();
  std::vector<Territory*>* getTerritories();
  int getId() const;
  int getReinforcementPool();

public:
  friend std::ostream& operator <<(std::ostream &out, const Player &player);
  bool canAttack(int);
  GameEngine* getGE();
  void addFriendly(int);
  void addPlayer(Player* p);
  std::vector<Player*> getListOfPlayers();
};