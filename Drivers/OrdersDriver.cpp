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

  //   cout << "-> Copy constructor copying the list :";
  //   ordersList CopyConstList = ordersList(list);
  //   cout << CopyConstList;

  //   cout << "-> Assignment operator copying the list"<< endl;
  //   ordersList oL;
  //   oL.add(userinputorder.create("deploy"));
  //   oL.add(userinputorder.create("bomb"));
  //   oL = list;
  //   cout << oL;

  cout << "-> List order execution" << endl;
  list.orderExecuter();

  //   cout << "-> Cout the lists" << endl;

  //   cout << "The initial list: "<< list << endl;
  //   cout << "Constructor list: "<< CopyConstList << endl;
  //   cout << "Assignment operator list: "<< oL << endl;

  //   cout << "-> Cout copied lists and operations:";

  //   list.add(userinputorder.create("deploy"));
  //   list.add(userinputorder.create("airlift"));
  //   CopyConstList.remove(2);
  //   cout << "-> Cout the original list:\n"
  //       << list << endl;
  //   cout << "-> Cout the copy constructor list:\n"
  //       << CopyConstList << endl;
  //   cout << "-> Cout assignment operator list:\n"
  //       << oL << endl;
}