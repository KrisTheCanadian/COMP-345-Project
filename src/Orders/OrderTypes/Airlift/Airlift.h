#pragma once

#include "Orders.h"

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
