#pragma once

#include <iostream>
#include "Cards/Cards.h"

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



class OrdersList
{
private:
  // vector of Order pointers
  std::vector<Order *> orders{};

public:
  // --------------------------------
  // Constructors + destructors
  // --------------------------------
  OrdersList() = default;
  ~OrdersList();
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




class Advance : public Order
{
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Advance() override;

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



class Airlift : public Order
{
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Airlift() override;

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




class Blockade : public Order
{
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Blockade() override;

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



class Bomb : public Order
{
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Bomb() override;

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



class Deploy : public Order
{
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Deploy() override;

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


class Negotiate : public Order
{
public:
  std::string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Negotiate() override;

private:
  const static std::string label;
  Order *clone() const override;
  std::ostream &orderCout(std::ostream &) const override;
};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                UserInputOrder - For Driver
//
// -----------------------------------------------------------------------------------------------------------------


class UserInputOrder
{
public:
  static Order *create(const std::string&) ;
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
