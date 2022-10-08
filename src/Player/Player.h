#pragma once

#include "Orders/OrdersList/OrdersList.h"
#include "Orders/OrdersFactory.h"
#include "Map/Territory/Territory.h"
#include "Cards/Deck/Deck.h"
#include "GameEngine/GameEngine.h"
#include "Cards/Hand/Hand.h"
#include "Cards/Cards.h"

#include <vector>

class Hand;
class GameEngine;

class Player {
private:
  static int nextId;
  int id;
  std::vector<Territory*> territories;
  Hand* hand;
  OrdersList orders;
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

  // --------------------------------
  // Getters
  // --------------------------------
  Hand* getHand();
  OrdersList* getOrdersListObject();
  std::vector<Territory*>* getTerritories();
  int getId() const;

public:
  friend std::ostream& operator <<(std::ostream &out, const Player &player);

};