#include "Orders.h"

const string deploy::label = "Deploy";
const string advance::label = "Advance";
const string bomb::label = "Bomb";
const string blockade::label = "Blockade";
const string airlift::label = "Airlift";
const string negotiate::label = "Negotiate";

// Default constructor
ordersList::ordersList() {}

ordersList::~ordersList()
{

  int listLength = orders.size();
  // delete dynamically allocated orders
  for (int o = 0; o < listLength; o++)
    delete orders[o];
}

// Copy constructor to make deep copy of the order list
ordersList::ordersList(const ordersList &oldList)
{
  int listLength = oldList.orders.size();
  orders = vector<Order *>(listLength);
  // cloning the same object into another memory slot
  for (int o = 0; o < listLength; o++)
    orders[o] = oldList.orders[o]->clone();
  cout << "->Order list copy completed." << endl;
}

// different order destructors
Order::~Order() {}
deploy::~deploy() {}
advance::~advance() {}
bomb::~bomb() {}
blockade::~blockade() {}
airlift::~airlift() {}
negotiate::~negotiate() {}

// Method adding order to the order list vector
void ordersList::add(Order *o)
{
  // grabbing nullptr from userInputOrder
  if (o == nullptr)
    cout << "Can't add the order as o is a null pointer." << endl;
  else
  {
    orders.push_back(o);
    cout << "User's order has been added to the list. Updated List: \n"
         << *this << endl;
  }
}

// method that removes an order
void ordersList::remove(int pos)
{
  int listLength = orders.size();
  // as listLength is 0 the list is empty no need to remove an order
  if (listLength == 0)
    cout << "The order list is empty, can't remove any more orders." << endl;
  // make sure order position is valid
  else if (pos > listLength || pos < 1)
    cout << "The inputed position isn't valid please make another entry." << endl;
  else
  {
    // need to empty memory for dynamically created order objs
    delete orders[pos - 1];
    // when the memory is deleted need to remove the pointer from the list as well to avoid memory leak
    orders.erase(orders.begin() + pos - 1);
    cout << "Requested order was deleted at " << pos << " Updated List: \n"
         << *this << endl;
  }
}

// method moving the orders positions
void ordersList::move(int pos1, int pos2)
{
  // checks number of orders in order list to make sure the move is valid
  int listLength = orders.size();
  // checks if the order list is empty if so no need to move anything
  if (listLength == 0)
    cout << "Order list is empty, won't move anything." << endl;
  else if (listLength == 1)
    cout << "There is only one order in the list, need more than one orders for the move." << endl;
  // check to make sure user inputted positions are valid
  else if (pos1 > listLength || pos2 > listLength || pos1 < 1 || pos2 < 1)
    cout << "None or only one inputted position is valid. Please try again." << endl;
  else
  {
    // change the 2 pointers together without changing the address of objects that are being pointed to
    Order *temp = orders[pos1 - 1];
    orders[pos1 - 1] = orders[pos2 - 1];
    orders[pos2 - 1] = temp;
    cout << "Two order " << pos1 << " & " << pos2 << " have been moved and replace eachother, updated list \n"
         << *this << endl;
  }
}

// order executer method
void ordersList::orderExecuter()
{
  int listLength = orders.size();
  if (listLength == 0)
    cout << "As order list is empty won't execute an order." << endl;
  else
  {
    for (int o = 0; o < listLength; o++)

    {
      orders[o]->execute();
      delete orders[o];
    }

    orders.clear();

    cout << "Completed orders execution." << endl;
  }
}

// ordersList class assignment operator
ordersList &ordersList::operator=(const ordersList &copyList)
{
  // let go of left hand side memory and deep copy to right hand side
  // checks if we're self assigning
  if (&copyList == this)
    return *this;

  int initialListLength = orders.size();
  int copyListLength = copyList.orders.size();

  for (int o = 0; o < initialListLength; o++)
    delete orders[o];
  // Grab memory same size as the right hand side vector
  orders = vector<Order *>(copyListLength);

  for (int i = 0; i < copyListLength; i++)
    // clone copied element to left hand side
    orders[i] = copyList.orders[i]->clone();

  return *this;
}

// print out the order list
ostream &operator<<(ostream &stream, const ordersList &ol)
{
  int listLength = ol.orders.size();

  for (int l = 0; l < listLength; l++)
  {
    stream << l + 1 << " --> " << ol.orders[l]->getLabel() << " // ";
  }
  stream << "\n";
  return stream;
}

// returning names of each order
string deploy::getLabel() const { return label; }
string advance::getLabel() const { return label; }
string bomb::getLabel() const { return label; }
string blockade::getLabel() const { return label; }
string airlift::getLabel() const { return label; }
string negotiate::getLabel() const { return label; }

// Polymorphism use of orderCout to cout paramters on each order
ostream &operator<<(ostream &stream, const Order &o) { return o.orderCout(stream); }

// Just a place holder, should be populated by accurate data for assignments 2 and 3.
ostream &deploy::orderCout(ostream &output) const { return output << "-> Deploy order."; }
ostream &advance::orderCout(ostream &output) const { return output << "-> Advance order."; }
ostream &bomb::orderCout(ostream &output) const { return output << "-> Bomb order."; }
ostream &blockade::orderCout(ostream &output) const { return output << "-> Blockade order."; }
ostream &airlift::orderCout(ostream &output) const { return output << "-> Airlift order."; }
ostream &negotiate::orderCout(ostream &output) const { return output << "-> Negotiate order."; }

// Just a place holder, should check order validation accuracy for assignments 2 and 3.
bool deploy::validate() const
{
  cout << "-> Deploy order validation check" << endl;
  return true;
}

bool advance::validate() const
{
  cout << "-> Advance order validation check" << endl;
  return true;
}

bool bomb::validate() const
{
  cout << "-> Bomb order validation check" << endl;
  return true;
}

bool blockade::validate() const
{
  cout << "-> Blockade order validation check" << endl;
  return true;
}

bool airlift::validate() const
{
  cout << "-> Airlift order validation check" << endl;
  return true;
}

bool negotiate::validate() const
{
  cout << "-> Negotiate order validation check" << endl;
  return true;
}

// Just a place holder, will execute order after validation check for assignments 2 and 3.
void deploy::execute() const
{
  if (validate())
    cout << "Deploy execution." << endl;
}
void advance::execute() const
{
  if (validate())
    cout << "Advance execution." << endl;
}
void bomb::execute() const
{
  if (validate())
    cout << "Bomb execution." << endl;
}
void blockade::execute() const
{
  if (validate())
    cout << "Blockade execution." << endl;
}
void airlift::execute() const
{
  if (validate())
    cout << "Airlift execution." << endl;
}
void negotiate::execute() const
{
  if (validate())
    cout << "Negotiate execution." << endl;
}

// As each object created from order sub classes doesn't have unique data members,
// the default copy constructor can be used in addition
// to the pointers list pointing to our abstract class to clone order objects
// in the order list using polymorphism.
Order *deploy::clone() const { return new deploy(*this); }
Order *advance::clone() const { return new advance(*this); }
Order *bomb::clone() const { return new bomb(*this); }
Order *blockade::clone() const { return new blockade(*this); }
Order *airlift::clone() const { return new airlift(*this); }
Order *negotiate::clone() const { return new negotiate(*this); }

// Here depnding on the player's cin we create an order.
// If player cins an invalid string a null pointer is returned and
// handled through ordersList::addOrder()
Order *userInputOrder::create(string orderType) const
{
  if (orderType == "deploy")
    return new deploy;
  else if (orderType == "advance")
    return new advance;
  else if (orderType == "bomb")
    return new bomb;
  else if (orderType == "blockade")
    return new blockade;
  else if (orderType == "airlift")
    return new airlift;
  else if (orderType == "negotiate")
    return new negotiate;
  else
    return nullptr;
}