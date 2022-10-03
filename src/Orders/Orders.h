#pragma once
#include <iostream>
// will use a vector to create the orders list
#include <vector>
// used string library for adding labels within order objects
#include <string>

// iomanip library required for setfill and setw to manipulate the output
#include <iomanip>

using std::cout;
using std::endl;
using std::left;
using std::ostream;
using std::string;
using std::vector;

using std::setfill;
using std::setw;

// Abstract Order class data members and methods to be implemented by derived classes
class Order
{
public:
  virtual string getLabel() const = 0;
  virtual bool validate() const = 0;
  virtual void execute() const = 0;
  virtual ~Order() = 0;

private:
  virtual Order *clone() const = 0;
  virtual ostream &orderCout(ostream &) const = 0;

  friend ostream &operator<<(ostream &, const Order &);
  friend class OrdersList;
};

class Deploy : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Deploy();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

class Advance : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Advance();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

class Bomb : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Bomb();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

class Blockade : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Blockade();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

class Airlift : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Airlift();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

class Negotiate : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Negotiate();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

// Initially would use user cin to allocated type and create an order
class UserInputOrder
{
public:
  Order *create(string) const;
};

class OrdersList
{
public:
  OrdersList();
  ~OrdersList();
  OrdersList(const OrdersList &);
  OrdersList &operator=(const OrdersList &);

  void add(Order *o);
  void remove(int);
  void move(int, int);

  // Run user orders and remove them from order list
  void orderExecuter();

private:
  vector<Order *> orders;

  friend ostream &operator<<(ostream &, const OrdersList &);
};