#include "Orders.h"
#include "OrdersDriver.h"
#include "Orders/OrdersList/OrdersList.h"
#include "Orders//UserInputOrder/UserInputOrder.h"

void testOrdersLists()
{
  OrdersList list;
  std::cout << "-> Order Addition" << std::endl;
  list.add(UserInputOrder::create("Deploy"));
  list.add(UserInputOrder::create("Advance"));
  list.add(UserInputOrder::create("Bomb"));
  list.add(UserInputOrder::create("Blockade"));
  list.add(UserInputOrder::create("Airlift"));
  list.add(UserInputOrder::create("Negotiate"));

  std::cout << "-> Move 4 with 2" << std::endl;
  list.move(4, 2);
  list.remove(2);

  std::cout << "-> List order execution" << std::endl;
  list.orderExecuter();
}