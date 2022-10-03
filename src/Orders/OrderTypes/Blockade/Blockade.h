#pragma once

#include <string>

#include "Orders.h"

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
