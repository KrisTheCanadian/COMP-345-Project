#pragma once

#include "Orders.h"

// Initially would use user cin to allocated type and create an order
class UserInputOrder
{
public:
  static Order *create(const std::string&) ;
};