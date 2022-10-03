#include "Orders.h"

const string Deploy::label = "Deploy";
const string Advance::label = "Advance";
const string Bomb::label = "Bomb";
const string Blockade::label = "Blockade";
const string Airlift::label = "Airlift";
const string Negotiate::label = "Negotiate";

// Default constructor
OrdersList::OrdersList() {}

OrdersList::~OrdersList()
{

  int listLength = orders.size();
  // delete dynamically allocated orders
  for (int o = 0; o < listLength; o++)
    delete orders[o];
}

// Copy constructor to make deep copy of the order list
OrdersList::OrdersList(const OrdersList &oldList)
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
Deploy::~Deploy() {}
Advance::~Advance() {}
Bomb::~Bomb() {}
Blockade::~Blockade() {}
Airlift::~Airlift() {}
Negotiate::~Negotiate() {}

// Method adding order to the order list vector
void OrdersList::add(Order *o)
{
  // grabbing nullptr from UserInputOrder
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
void OrdersList::remove(int pos)
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
    cout << "Requested order was deleted at " << pos << ", Updated List: \n"
         << *this << endl;
  }
}

// method moving the orders positions
void OrdersList::move(int pos1, int pos2)
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
    cout << "Two order " << pos1 << " & " << pos2 << " have been moved and replace eachother, Updated list \n"
         << *this << endl;
  }
}

// order executer method
void OrdersList::orderExecuter()
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

// OrdersList class assignment operator
OrdersList &OrdersList::operator=(const OrdersList &copyList)
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
ostream &operator<<(ostream &stream, const OrdersList &ol)
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
string Deploy::getLabel() const { return label; }
string Advance::getLabel() const { return label; }
string Bomb::getLabel() const { return label; }
string Blockade::getLabel() const { return label; }
string Airlift::getLabel() const { return label; }
string Negotiate::getLabel() const { return label; }

// Polymorphism use of orderCout to cout paramters on each order
ostream &operator<<(ostream &stream, const Order &o) { return o.orderCout(stream); }

// Just a place holder, should be populated by accurate data for assignments 2 and 3.
ostream &Deploy::orderCout(ostream &output) const { return output << "-> Deploy order."; }
ostream &Advance::orderCout(ostream &output) const { return output << "-> Advance order."; }
ostream &Bomb::orderCout(ostream &output) const { return output << "-> Bomb order."; }
ostream &Blockade::orderCout(ostream &output) const { return output << "-> Blockade order."; }
ostream &Airlift::orderCout(ostream &output) const { return output << "-> Airlift order."; }
ostream &Negotiate::orderCout(ostream &output) const { return output << "-> Negotiate order."; }

// Just a place holder, should check order validation accuracy for assignments 2 and 3.
bool Deploy::validate() const
{
  cout << "-> Deploy order validation check" << endl;
  return true;
}

bool Advance::validate() const
{
  cout << "-> Advance order validation check" << endl;
  return true;
}

bool Bomb::validate() const
{
  cout << "-> Bomb order validation check" << endl;
  return true;
}

bool Blockade::validate() const
{
  cout << "-> Blockade order validation check" << endl;
  return true;
}

bool Airlift::validate() const
{
  cout << "-> Airlift order validation check" << endl;
  return true;
}

bool Negotiate::validate() const
{
  cout << "-> Negotiate order validation check" << endl;
  return true;
}

// Just a place holder, will execute order after validation check for assignments 2 and 3.
void Deploy::execute() const
{
  if (validate())
    cout << "Deploy execution." << endl;
}
void Advance::execute() const
{
  if (validate())
    cout << "Advance execution." << endl;
}
void Bomb::execute() const
{
  if (validate())
    cout << "Bomb execution." << endl;
}
void Blockade::execute() const
{
  if (validate())
    cout << "Blockade execution." << endl;
}
void Airlift::execute() const
{
  if (validate())
    cout << "Airlift execution." << endl;
}
void Negotiate::execute() const
{
  if (validate())
    cout << "Negotiate execution." << endl;
}

// As each object created from order sub classes doesn't have unique data members,
// the default copy constructor can be used in addition
// to the pointers list pointing to our abstract class to clone order objects
// in the order list using polymorphism.
Order *Deploy::clone() const { return new Deploy(*this); }
Order *Advance::clone() const { return new Advance(*this); }
Order *Bomb::clone() const { return new Bomb(*this); }
Order *Blockade::clone() const { return new Blockade(*this); }
Order *Airlift::clone() const { return new Airlift(*this); }
Order *Negotiate::clone() const { return new Negotiate(*this); }

// Here depnding on the player's cin we create an order.
// If player cins an invalid string a null pointer is returned and
// handled through OrdersList::addOrder()
Order *UserInputOrder::create(string orderType) const
{
  if (orderType == "Deploy")
    return new Deploy;
  else if (orderType == "Advance")
    return new Advance;
  else if (orderType == "Bomb")
    return new Bomb;
  else if (orderType == "Blockade")
    return new Blockade;
  else if (orderType == "Airlift")
    return new Airlift;
  else if (orderType == "Negotiate")
    return new Negotiate;
  else
    return nullptr;
}