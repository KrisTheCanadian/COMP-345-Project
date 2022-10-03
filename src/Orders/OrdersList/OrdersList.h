#pragma once
#include <iostream>
#include <vector>

#include "Orders.h"

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
  std::vector<Order *> orders{};

  friend std::ostream &operator<<(std::ostream &, const OrdersList &);
};
