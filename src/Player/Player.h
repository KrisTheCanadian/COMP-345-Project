#pragma once

#include "OrdersList.h"
#include "Hand.h"
#include "Territory.h"
#include "Deck.h"
#include "Orders.h"
#include "Bomb.h"
#include "Blockade.h"
#include "Airlift.h"
#include "Negotiate.h"

#include <vector>

class Order;

class Player {
private:
  std::vector<Territory*> territories;
  Deck* deck;
  Hand* hand;
  OrdersList orders;

public:
  // --------------------------------
  // Constructors
  // --------------------------------
  Player(Deck* deck, Hand* cards);
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

  void issueOrder(const CardType* cardType);
  void addTerritory(Territory& territory);
  void removeTerritory(Territory& territory);

  // --------------------------------
  // Getters
  // --------------------------------
  Hand* getHand();
  Deck* getDeck();
  OrdersList* getOrdersList();
  std::vector<Territory*>* getTerritories();

public:
  friend std::ostream& operator <<(std::ostream &out, const Player &player);

};