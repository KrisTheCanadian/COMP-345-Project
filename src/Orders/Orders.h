#pragma once

#include <iostream>
#include <sstream>

#include "Cards/Cards.h"
#include "Logger/LogObserver.h"

class Card;
class Player;
class Territory;
enum CardType : int;

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Orders
//
// -----------------------------------------------------------------------------------------------------------------

// --------------------------------
// Abstract Order class data members and methods to be implemented by derived classes
// --------------------------------
class Order
{
public:
  virtual ~Order() = default;
  // gets label
  virtual std::string getLabel() const = 0;
  // validates order
  virtual bool validate() const = 0;
  // executes order
  virtual void execute() = 0;
  // cloner (copy)
  virtual Order *clone() const = 0;
private:
  // --------------------------------
  // Operator Overloads
  // --------------------------------
  virtual std::ostream &orderCout(std::ostream &) const = 0;

  friend std::ostream &operator<<(std::ostream &, const Order &);
};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                OrdersList
//
// -----------------------------------------------------------------------------------------------------------------



class OrdersList : public Subject, ILoggable
{
private:
  // vector of Order pointers
  std::vector<Order *> orders{};
  GameEngine* game;

public:
  // --------------------------------
  // Constructors + destructors
  // --------------------------------
  explicit OrdersList(GameEngine* gameEngine);
  ~OrdersList() override;
  OrdersList(const OrdersList &);

  // --------------------------------
  // Operator Overloads
  // --------------------------------
  OrdersList &operator=(const OrdersList &);

  // --------------------------------
  // Adders + mutators
  // --------------------------------
  void add(Order *o);
  void remove(int);
  void move(int, int);

  // Run user orders and remove them from order list
  void execute();

  size_t getOrdersListSize();
  Order* getOrder(int index);

  // --------------------------------
  // Getters
  // --------------------------------
  std::vector<Order *>* getList();

  // Logging
  static std::string castOrderType(Order * o);
  std::string stringToLog() override;

private:
  // --------------------------------
  // ostream overload
  // --------------------------------
  friend std::ostream &operator<<(std::ostream &, const OrdersList &);
};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Advance
//
// -----------------------------------------------------------------------------------------------------------------

class Advance : public Order, Subject, ILoggable{
private:
  GameEngine* game;
  Player* currentPlayer;
  Territory* source;
  Territory* target;
  int amount = 0;

public:
  Advance(GameEngine* game, Territory* src, Territory* dest, Player* player, int amount);
  ~Advance() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;
  static void attackSimulation(Territory*, Territory*, Player*, int);

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Airlift
//
// -----------------------------------------------------------------------------------------------------------------



class Airlift : public Order, Subject, ILoggable
{
private:
  GameEngine* game;
  Player* currentPlayer;
  Territory* source;
  Territory* target;
  int amount = 0;

public:
  Airlift(GameEngine* game, Territory* source, Territory* target, Player* player, int amount);
  ~Airlift() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Blockade
//
// -----------------------------------------------------------------------------------------------------------------




class Blockade : public Order, Subject, ILoggable
{
private:
  GameEngine* game;
  Territory* target;
  Player* currentPlayer;

public:
  Blockade(GameEngine* game, Territory* target, Player* player);
  ~Blockade() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Bomb
//
// -----------------------------------------------------------------------------------------------------------------



class Bomb : public Order, Subject, ILoggable
{
private:
  GameEngine* game;
  Territory* target;
  Player* currentPlayer;

public:
  Bomb(GameEngine* game, Territory* target, Player* player);
  ~Bomb() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;

};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Deploy
//
// -----------------------------------------------------------------------------------------------------------------



class Deploy : public Order, Subject, ILoggable
{
private:
  GameEngine* game;
  Player* currentPlayer;
  Territory* target;
  int amount;

public:
  Deploy(GameEngine* game, Territory* target, Player* player, int amount);
  ~Deploy() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;

private:
  const static std::string label;
  Order* clone() const override;
  std::ostream &orderCout(std::ostream &) const override;

};




// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Negotiate
//
// -----------------------------------------------------------------------------------------------------------------


class Negotiate : public Order, Subject, ILoggable
{
private:
  GameEngine* game;
  Player* currentPlayer;
  Player* targetPlayer;
  std::vector<Player*> friendlyPlayers;

public:
  Negotiate(GameEngine* game, Player* currentPlayer, Player* targetPlayer);
  ~Negotiate() override;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};