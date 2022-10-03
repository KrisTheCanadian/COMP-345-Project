#pragma once

#include <iostream>

#include "Orders.h"

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