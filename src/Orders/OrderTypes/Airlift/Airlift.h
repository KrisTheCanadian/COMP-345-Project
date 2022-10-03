#pragma once

#include "Orders.h"

class Airlift : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Airlift() override;

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
  ~Negotiate() override;

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};
