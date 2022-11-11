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
  // gets label
  virtual std::string getLabel() const = 0;
  // validates order
  virtual bool validate() const = 0;
  // executes order
  virtual void execute() const = 0;
  // destructor
  virtual ~Order() = 0;
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

public:
  // --------------------------------
  // Constructors + destructors
  // --------------------------------
  OrdersList() = default;
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
  Player* currentPlayer;
  Territory* source;
  Territory* target;
  int amount = 0;

public:
  Advance(Territory* src, Territory* dest, Player* player, int amount);
  ~Advance() override = default;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  std::string stringToLog() override;

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
  Player* currentPlayer;
  Territory* source;
  Territory* target;
  int amount = 0;

public:
  Airlift(Territory* source, Territory* target, Player* player, int amount);
  ~Airlift() override = default;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
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
  Territory* target;
  Player* currentPlayer;

public:
  Blockade(Territory* target, Player* player);
  ~Blockade() override = default;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
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
  Territory* target;
  Player* currentPlayer;

public:
  Bomb(Territory* target, Player* player);
  ~Bomb() override = default;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
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
  Player* currentPlayer;
  Territory* target;
  int amount;

public:
  Deploy(Territory* target, Player* player, int amount);
  ~Deploy() override = default;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
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
  Player* currentPlayer;
  Player* targetPlayer;
  std::vector<Player*> friendlyPlayers;

public:
  Negotiate(Player* currentPlayer, Player* targetPlayer);
  ~Negotiate() override = default;
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

void attackSimulation(Territory*, Territory*, Player*, int);
