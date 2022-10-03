#include "Orders.h"
#include "OrdersDriver.h"

void testOrdersLists()
{
  OrdersList list;
  UserInputOrder UserInputOrder;
  cout << "-> Order Addition" << endl;
  list.add(UserInputOrder.create("Deploy"));
  list.add(UserInputOrder.create("Advance"));
  list.add(UserInputOrder.create("Bomb"));
  list.add(UserInputOrder.create("Blockade"));
  list.add(UserInputOrder.create("Airlift"));
  list.add(UserInputOrder.create("Negotiate"));

  cout << "-> Move 4 with 2" << endl;
  list.move(4, 2);
  list.remove(2);

  cout << "-> List order execution" << endl;
  list.orderExecuter();
}