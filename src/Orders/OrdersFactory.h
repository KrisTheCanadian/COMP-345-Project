#pragma once

#include "Orders/Orders.h"
#include "Orders/OrderTypes/Bomb/Bomb.h"
#include "Orders/OrderTypes/Blockade/Blockade.h"
#include "Orders/OrderTypes/Airlift/Airlift.h"
#include "Orders/OrderTypes/Negotiate/Negotiate.h"
#include "Cards/Cards.h"

enum CardType : int;

class OrdersFactory {

public:
  static Order* CreateOrder(CardType cardType);

};
