#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#include "Orders.h"

class OrdersList
{
private:
  std::vector<Order *> orders{};

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

  std::vector<Order *>* getOrdersList();

private:
  friend std::ostream &operator<<(std::ostream &, const OrdersList &);
};
