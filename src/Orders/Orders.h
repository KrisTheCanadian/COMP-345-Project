#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
// Abstract Order class data members and methods to be implemented by derived classes
class Order
{
public:
  virtual std::string getLabel() const = 0;
  virtual bool validate() const = 0;
  virtual void execute() const = 0;
  virtual ~Order() = 0;

private:
  virtual Order *clone() const = 0;
  virtual std::ostream &orderCout(std::ostream &) const = 0;

  friend std::ostream &operator<<(std::ostream &, const Order &);
  friend class OrdersList;
};

// Initially would use user cin to allocated type and create an order
class UserInputOrder
{
public:
  static Order *create(const std::string&) ;
};