#pragma once

#include "Orders.h"

class Blockade : public Order
{
public:
  string getLabel() const override;
  bool validate() const override;
  void execute() const override;
  ~Blockade() override;

private:
  const static string label;
  Order *clone() const override;
  ostream &orderCout(ostream &) const override;
};
