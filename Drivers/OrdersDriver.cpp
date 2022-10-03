#include "Orders.h"
#include "OrdersDriver.h"

void testOrdersLists()
{
  ordersList list;
  userInputOrder userinputorder;
  cout << "-> Order Addition" << endl;
  list.add(userinputorder.create("deploy"));
  list.add(userinputorder.create("advance"));
  list.add(userinputorder.create("bomb"));
  list.add(userinputorder.create("blockade"));
  list.add(userinputorder.create("airlift"));
  list.add(userinputorder.create("negotiate"));

  cout << "-> Move 4 with 2" << endl;
  list.move(4, 2);
  list.remove(2);

  cout << "-> List order execution" << endl;
  list.orderExecuter();
}