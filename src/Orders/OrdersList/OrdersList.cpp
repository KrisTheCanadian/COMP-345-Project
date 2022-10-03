#include "OrdersList.h"

OrdersList::OrdersList() = default;

OrdersList::~OrdersList()
{

  unsigned listLength = orders.size();
  // delete dynamically allocated orders
  for (unsigned o = 0; o < listLength; o++){
    delete orders[o];
  }
}

// Copy constructor to make deep copy of the order list
OrdersList::OrdersList(const OrdersList &oldList)
{
  unsigned listLength = oldList.orders.size();
  orders = std::vector<Order *>(listLength);
  // cloning the same object into another memory slot
  for (unsigned o = 0; o < listLength; o++)
    orders[o] = oldList.orders[o]->clone();
  std::cout << "->Order list copy completed." << std::endl;
}

// Method adding order to the order list vector
void OrdersList::add(Order *o)
{
  // grabbing nullptr from UserInputOrder
  if (o == nullptr)
    std::cout << "Can't add the order as o is a null pointer." << std::endl;
  else
  {
    orders.push_back(o);
    std::cout << "User's order has been added to the list. Updated List: \n"
         << *this << std::endl;
  }
}

// method that removes an order
void OrdersList::remove(int pos)
{
  unsigned listLength = orders.size();
  // as listLength is 0 the list is empty no need to remove an order
  if (listLength == 0){
    std::cout << "The order list is empty, can't remove any more orders." << std::endl;
  }
    // make sure order position is valid
  else if (pos > listLength || pos < 1) {
    std::cout << "The inputed position isn't valid please make another entry." << std::endl;
  }
  else
  {
    // need to empty memory for dynamically created order objs
    delete orders[pos - 1];
    // when the memory is deleted need to remove the pointer from the list as well to avoid memory leak
    orders.erase(orders.begin() + pos - 1);
    std::cout << "Requested order was deleted at " << pos << ", Updated List: \n"
         << *this << std::endl;
  }
}

// method moving the orders positions
void OrdersList::move(int pos1, int pos2)
{
  // checks number of orders in order list to make sure the move is valid
  unsigned listLength = orders.size();
  // checks if the order list is empty if so no need to move anything
  if (listLength == 0){
    std::cout << "Order list is empty, won't move anything." << std::endl;
  }
  else if (listLength == 1)
  {
    std::cout << "There is only one order in the list, need more than one orders for the move." << std::endl;
  }
  // check to make sure user inputted positions are valid
  else if (pos1 > listLength || pos2 > listLength || pos1 < 1 || pos2 < 1)
  {
    std::cout << "None or only one inputted position is valid. Please try again." << std::endl;
  }
  else
  {
    // change the 2 pointers together without changing the address of objects that are being pointed to
    Order *temp = orders[pos1 - 1];
    orders[pos1 - 1] = orders[pos2 - 1];
    orders[pos2 - 1] = temp;
    std::cout << "Two order " << pos1 << " & " << pos2 << " have been moved and replace each other, Updated list \n"
         << *this << std::endl;
  }
}

// order executer method
void OrdersList::orderExecuter()
{
  unsigned listLength = orders.size();
  if (listLength == 0){
    std::cout << "As order list is empty won't execute an order." << std::endl;
  }
  else
  {
    for (int o = 0; o < listLength; o++)

    {
      orders[o]->execute();
      delete orders[o];
    }

    orders.clear();

    std::cout << "Completed orders execution." << std::endl;
  }
}

// OrdersList class assignment operator
OrdersList &OrdersList::operator=(const OrdersList &copyList)
{
  // let go of left hand side memory and deep copy to right hand side
  // checks if we're self assigning
  if (&copyList == this){
    return *this;
  }

  unsigned initialListLength = orders.size();
  unsigned copyListLength = copyList.orders.size();

  for (int o = 0; o < initialListLength; o++)
    delete orders[o];
  // Grab memory same size as the right hand side vector
  orders = std::vector<Order *>(copyListLength);

  for (int i = 0; i < copyListLength; i++)
    // clone copied element to left hand side
    orders[i] = copyList.orders[i]->clone();

  return *this;
}

// print out the order list
std::ostream &operator<<(std::ostream &stream, const OrdersList &ol)
{
  unsigned listLength = ol.orders.size();

  for (unsigned l = 0; l < listLength; l++)
  {
    stream << l + 1 << " --> " << ol.orders[l]->getLabel() << " // ";
  }
  stream << "\n";
  return stream;
}