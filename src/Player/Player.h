#pragma once

#include "GameEngine/GameEngine.h"
#include "Map/Map.h"
#include "Orders/Orders.h"

#include <algorithm>
#include <utility>
#include <vector>

class Territory;
enum CardType : int;
class GameEngine;
class Hand;
class OrdersList;
class Order;
class Airlift;
class Bomb;
class Blockade;
class Negotiate;
class PlayerStrategy;
class Card;

class Player {
private:
  std::string phase;
  int reinforcementPool;
  std::vector<Territory*> territories;
  Hand* hand;
  OrdersList* orders;
  GameEngine* game;
  std::string name;
  std::vector<Player*> friendlyPlayers;

  PlayerStrategy* strategy;


  int deployedArmiesThisTurn = 0;

public:
  // --------------------------------
  // Constructors
  // --------------------------------
  Player(GameEngine* game, Hand* cards, std::string  name, const std::string& strategy);
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

  void removeArmies(int n);

  void issueOrder();
  void addTerritory(Territory& territory);
  void removeTerritory(Territory& territory);
  void addReinforcement(int reinforcement);
  int getContinentBonus();
  Territory* findFirstNeighbourTerritory(Territory* target);
  std::vector<Player*> getEnemies();

  PlayerStrategy* getStrategy() const;

  Order* createOrderFromCard(Card* card);

  // --------------------------------
  // Setters
  // --------------------------------
  void setReinforcementPool(int n);
  void addFriendly(Player *pPlayer);
  void clearFriendly();
  void setPhase(std::string ph);
  void addDeployedArmies(int a);
  void clearDeploymentArmies();
  void setDeployedArmiesThisTurn(int a);
  void setStrategy(const std::string& strategy);

  // --------------------------------
  // Getters
  // --------------------------------
  Hand* getHand();
  OrdersList* getOrdersListObject();
  std::vector<Territory*>* getTerritories();
  std::string getPhase();
  int getReinforcementPool() const;
  std::string getName() const;
  int getDeployedArmiesThisTurn() const;
  GameEngine* getGameInstance();



public:
  friend std::ostream& operator <<(std::ostream &out, const Player &player);
  bool canAttack(Player *pPlayer);
};