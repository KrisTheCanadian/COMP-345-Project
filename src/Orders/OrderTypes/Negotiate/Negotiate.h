#pragma once

#include <string>

#include "Orders/Orders.h"

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