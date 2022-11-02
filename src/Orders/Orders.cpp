#include <iomanip> // To format output.
#include <cstdlib>
#include "Orders.h"
#include "Map/Map.h"
#include "Player/Player.h"
#include "Cards/Cards.h"
using std::ostream;
using std::setw;
using std::setfill;
using std::left;
using std::cout;
using std::endl;

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Orders
//
// -----------------------------------------------------------------------------------------------------------------


Order::Order()
{
    currentPlayer = nullptr;
    enabled = true;
}
Order::Order(Player& currentPlayer)
{
    this->currentPlayer = &currentPlayer;
    enabled = true;
}
/**
 * Destructor
 */
Order::~Order()
{
    currentPlayer = nullptr;
}
std::ostream &operator<<(std::ostream &stream, const Order &o) { return o.orderCout(stream); }




// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                OrdersList
//
// -----------------------------------------------------------------------------------------------------------------


/**
 * Default constructor
 */
//OrdersList::OrdersList(){}

/**
 * Destructor
 */
OrdersList::~OrdersList(){ for(auto order: orders){ delete order; } }

// Copy constructor to make deep copy of the order list
OrdersList::OrdersList(const OrdersList &oldList)
{
  unsigned listLength = oldList.orders.size();
  orders = std::vector<Order *>(listLength);
  // cloning the same object into another memory slot
  for (unsigned o = 0; o < listLength; o++) { orders[o] = oldList.orders[o]->clone(); }
}

// Method adding order to the order list vector
void OrdersList::add(Order *o)
{
  if(o){ orders.push_back(o); } else { throw std::runtime_error("Inserting a nullptr in OrderList."); }
}

// method that removes an order
void OrdersList::remove(int pos)
{
  unsigned listLength = orders.size();
  // as listLength is 0 the list is empty no need to remove an order
  if (listLength == 0){
    throw std::runtime_error("The order list is empty, can't remove any more orders.");
  }
    // make sure order position is valid
  else if (pos >= listLength || pos < 0) {
    throw std::runtime_error("The inputed position isn't valid please make another entry.");
  }
  else
  {
    // need to empty memory for dynamically created order objs
    delete orders[pos];
    // when the memory is deleted need to remove the pointer from the list as well to avoid memory leak
    orders.erase(orders.begin() + pos);
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
    throw std::runtime_error("There is only one order in the list, need more than one orders for the move.");
  }
    // check to make sure user inputted positions are valid
  else if (pos1 >= listLength || pos2 >= listLength || pos1 < 0 || pos2 < 0)
  {
    throw std::runtime_error("None or only one inputted position is valid. Please try again.");
  }
  else
  {
    // change the 2 pointers together without changing the address of objects that are being pointed to
    Order *temp = orders[pos1];
    orders[pos1] = orders[pos2];
    orders[pos2] = temp;
  }
}

// order executer method
void OrdersList::execute()
{
  unsigned listLength = orders.size();
  if (listLength == 0){
    throw std::runtime_error("As order list is empty won't execute an order.");
  }
  else
  {
    for(auto order : orders){
      order->execute();
      delete order;
    }
    orders.clear();
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

  for (int o = 0; o < initialListLength; o++) { delete orders[o]; }

  // Grab memory same size as the right hand side vector
  orders = std::vector<Order *>(copyListLength);


  for (int i = 0; i < copyListLength; i++) {
    // clone copied element to left hand side
    orders[i] = copyList.orders[i]->clone();
  }

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

std::vector<Order *> *OrdersList::getList() {
  return &this->orders;
}




// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Advance
//
// -----------------------------------------------------------------------------------------------------------------



Advance::Advance() : Order()
{
    source = nullptr;
    target = nullptr;
    amount = nullptr;
}

std::ostream &Advance::orderCout(std::ostream &output) const { return output << "-> Advance order."; }

std::string Advance::getLabel() const { return label; }

Advance::Advance(Territory& source, Territory& target, Player& currentPlayer, int amount) : Order(currentPlayer)
{
    this->source = &source;
    this->target = &target;
    int* copiedAmount = new int(amount);
    this->amount = copiedAmount;
}

/**
 * Destructor
 */
Advance::~Advance()
{
    source = nullptr;
    target = nullptr;
    delete amount;
}

const std::string Advance::label = "Advance";

bool Advance::validate() const
{
  std::cout << "-> Advance order validation check" << std::endl;
  return true;
}

void Advance::execute() const
{
  if (validate()) { std::cout << "Advance execution." << std::endl; }
}

Order *Advance::clone() const { return new Advance(*this); }







// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Airlift
//
// -----------------------------------------------------------------------------------------------------------------






const std::string Airlift::label = "Airlift";

Airlift::~Airlift() = default;

std::string Airlift::getLabel() const { return label; }

std::ostream &Airlift::orderCout(std::ostream &output) const { return output << "-> Airlift order."; }

bool Airlift::validate() const
{
  std::cout << "-> Airlift order validation check" << std::endl;
  return true;
}

void Airlift::execute() const
{
  if (validate()) { std::cout << "Airlift execution." << std::endl; }
}

Order *Airlift::clone() const { return new Airlift(*this); }








// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Blockade
//
// -----------------------------------------------------------------------------------------------------------------







const std::string Blockade::label = "Blockade";

Blockade::~Blockade() = default;

std::string Blockade::getLabel() const { return label; }

std::ostream &Blockade::orderCout(std::ostream &output) const { return output << "-> Blockade order."; }

bool Blockade::validate() const
{
  std::cout << "-> Blockade order validation check" << std::endl;
  return true;
}

void Blockade::execute() const
{
  if (validate()) { std::cout << "Blockade execution." << std::endl; }
}

Order *Blockade::clone() const { return new Blockade(*this); }






// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Bomb
//
// -----------------------------------------------------------------------------------------------------------------


bomb::bomb() : Order()
{target = nullptr;}
bomb::bomb(Territory& target, Player& currentPlayer) : Order(currentPlayer)
{this->target = &target;}

const std::string Bomb::label = "Bomb";

/**
 * Destructor
 */
bomb::~bomb()
{target = nullptr;}

std::string Bomb::getLabel() const { return label; }

std::ostream &Bomb::orderCout(std::ostream &output) const { return output << "-> Bomb order."; }

bool Bomb::validate() const
{
  std::cout << "-> Bomb order validation check" << std::endl;
  return true;
}

void Bomb::execute() const
{
  if (validate()) { std::cout << "Bomb execution." << std::endl; }
}

Order *Bomb::clone() const { return new Bomb(*this); }






// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Deploy
//
// -----------------------------------------------------------------------------------------------------------------


deploy::deploy() : Order()
{
    target = nullptr;
    amount = nullptr;
}

const std::string Deploy::label = "Deploy";

deploy::deploy(Territory& target, Player& currentPlayer, int amount) : Order(currentPlayer)
{
    this->target = &target;
    int* copiedAmount = new int(amount); // Because our data member is an int pointer.
    this->amount = copiedAmount;
}

deploy::~deploy()
{
    target = nullptr;
    currentPlayer = nullptr;
    delete amount;
}

std::string Deploy::getLabel() const { return label; }

std::ostream &Deploy::orderCout(std::ostream &output) const { return output << "-> Deploy order."; }

bool Deploy::validate() const
{
  std::cout << "-> Deploy order validation check" << std::endl;
  return true;
}

void Deploy::execute() const
{
  if (validate()) { std::cout << "Deploy execution." << std::endl; }
}

Order *Deploy::clone() const { return new Deploy(*this); }






// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Negotiate
//
// -----------------------------------------------------------------------------------------------------------------







const std::string Negotiate::label = "Negotiate";

Negotiate::~Negotiate() = default;

std::string Negotiate::getLabel() const { return label; }

bool Negotiate::validate() const
{
  std::cout << "-> Negotiate order validation check" << std::endl;
  return true;
}

void Negotiate::execute() const
{
  if (validate()) { std::cout << "Negotiate execution." << std::endl; }
}


Order *Negotiate::clone() const { return new Negotiate(*this); }

std::ostream &Negotiate::orderCout(std::ostream &ostream) const {
  return ostream << "-> Negotiate order.";
}




// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                UserInputOrder - For Driver
//
// -----------------------------------------------------------------------------------------------------------------



Order* UserInputOrder::create(const std::string& orderType)
{
  if (orderType == "Deploy") { return new Deploy; }
  else if (orderType == "Advance") { return new Advance; }
  else if (orderType == "Bomb") { return new Bomb(); }
  else if (orderType == "Blockade") { return new Blockade(); }
  else if (orderType == "Airlift") { return new Airlift(); }
  else if (orderType == "Negotiate") { return new Negotiate(); }
  else { throw std::runtime_error("Unexpected OrderType: " + orderType ); }
}


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                OrdersFactory
//
// -----------------------------------------------------------------------------------------------------------------



Order* OrdersFactory::CreateOrder(CardType cardType) {
  switch(cardType){
    case CT_Bomb:
      return new Bomb();
    case CT_Reinforcement:
      // TODO: Assignment 2 -> remove deploy and add new logic
      return new Deploy();
    case CT_Blockade:
      return new Blockade();
    case CT_Airlift:
      return new Airlift();
    case CT_Diplomacy:
      return new Negotiate();
    default:
      throw std::runtime_error("ASSERT: Unhandled CardType Value");
  }
}