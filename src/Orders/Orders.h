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
  friend class ordersList;
};

class deploy : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~deploy();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

class advance : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~advance();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

class bomb : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~bomb();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

class blockade : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~blockade();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

class airlift : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~airlift();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

class negotiate : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~negotiate();

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};

// Initially would use user cin to allocated type and create an order
class userInputOrder
{
public:
  Order *create(string) const;
};

class ordersList
{
public:
  ordersList();
  ~ordersList();
  ordersList(const ordersList &);
  ordersList &operator=(const ordersList &);

  void add(Order *o);
  void remove(int);
  void move(int, int);

  // Run user orders and remove them from order list
  void orderExecuter();

private:
  vector<Order *> orders;

  friend ostream &operator<<(ostream &, const ordersList &);
};