#pragma once

#include <iostream>
#include <sstream>

#include "Cards/Cards.h"
#include "Logger/LogObserver.h"

class Card;
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
  virtual void execute() = 0;
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

  // --------------------------------
  // Getters
  // --------------------------------
  std::vector<Order *>* getList();

  // Logging
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




class Advance : public Order, Subject, ILoggable
{
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  ~Advance() override;

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
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  ~Airlift() override;

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
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  ~Blockade() override;

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
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  ~Bomb() override;

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
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  ~Deploy() override;

  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
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
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() override;
  ~Negotiate() override;

  std::string stringToLog() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                OrdersFactory
//
// -----------------------------------------------------------------------------------------------------------------


// --------------------------------
// Static Class : OrdersFactory to create order subclasses according to card type enum
// --------------------------------
class OrdersFactory {

public:
  static Order* CreateOrder(CardType cardType);

};
