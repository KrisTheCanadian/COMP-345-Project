#pragma once

#include "Orders/Orders.h"

class Order;

// Initially would use user cin to allocated type and create an order
class UserInputOrder
{
public:
  static Order *create(const std::string&) ;
};