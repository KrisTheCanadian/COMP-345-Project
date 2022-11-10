#include <iomanip> // To format output.
#include <cstdlib>
#include <cmath>
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
  Subject::notify(this);
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

int OrdersList::getOrdersListSize()
{
    return orders.size();
}
Order* OrdersList::getOrder(int index)
{
    if(index < orders.size() && index >= 0)
    {
        return orders[index];
    }
    return nullptr;
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


std::string OrdersList::castOrderType(Order * o){
  if(Advance *order = dynamic_cast<Advance*>(o)){
      return order->getLabel();
  }
  else if(Airlift *order = dynamic_cast<Airlift*>(o)){
      return order->getLabel();
  }
  else if(Blockade *order = dynamic_cast<Blockade*>(o)){
      return order->getLabel();
  }
  else if(Bomb *order = dynamic_cast<Bomb*>(o)){
      return order->getLabel();
  }
  else if(Deploy *order = dynamic_cast<Deploy*>(o)){
      return order->getLabel();
  }
  else if(Negotiate *order = dynamic_cast<Negotiate*>(o)){
      return order->getLabel();
  }
  throw std::runtime_error("OrderList::Error Order is null");
}

std::string OrdersList::stringToLog() {
  Order &o = *orders.back();
  std::string orderType = castOrderType(&o);

  std::stringstream ss;
  ss << "ORDER LIST: ";
  ss << "Order List Added ";
  ss << orderType;
  return ss.str();
}


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Advance
//
// -----------------------------------------------------------------------------------------------------------------
Advance::Advance(Territory& source, Territory& target, Player& currentPlayer, int amount) : Order(currentPlayer)
{
    this->source = &source;
    this->target = &target;
    this->amount = amount;
}
std::ostream &Advance::orderCout(std::ostream &output) const { return output << "-> Advance order."; }

std::string Advance::getLabel() const { return label; }

const std::string Advance::label = "Advance";

bool Advance::validate() const
{
  std::cout << "-> Advance order validation check" << std::endl;

    if (source->getOwnerId() != currentPlayer->getId())
    {
        cout << "The source territory is not your own!\n" << endl;
        return false;
    }

    else if (!(std::find(source->getAdjacentTerritories()->begin(), source->getAdjacentTerritories()->end(), target) != source->getAdjacentTerritories()->end()))
    {
        cout << "The target territory is not adjacent to the source territory!\n" << endl;
        return false;
    }
    else if (amount > source->getArmies())
    {
        cout << "You do not have this many armies in this territory!\n" << endl;
        return false;
    }
    else if (amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
    }
    cout << "Your order has been validated!\n" << endl;
  return true;
}

void Advance::execute() const
{
    if (validate())
    {
        std::cout << "Advance execution." << std::endl;
        if (source->getOwnerId() == target->getOwnerId()) // Transferring army to another territory
        {
            source->setArmies(source->getArmies() - amount);
            target->setArmies(target->getArmies() + amount);
        }
        else // If you try to transfer on enemy territory, considered as attack.
        {
            if (!currentPlayer->canAttack(target->getOwnerId()))
            {
                cout << "You cannot attack this player!\n" << endl;
                return;
            }
            attackSimulation(source, target, currentPlayer, amount);
        }
        cout << "Advance has finished executing!\n" << endl;
    }
}

Order *Advance::clone() const { return new Advance(*this); }

std::string Advance::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Airlift
//
// -----------------------------------------------------------------------------------------------------------------


Airlift::Airlift(Territory& source, Territory& target, Player& currentPlayer, int amount) : Order(currentPlayer)
{
    this->source = &source;
    this->target = &target;
    this->amount = amount;
}

const std::string Airlift::label = "Airlift";

std::string Airlift::getLabel() const { return label; }

std::ostream &Airlift::orderCout(std::ostream &output) const { return output << "-> Airlift order."; }

bool Airlift::validate() const
{
  std::cout << "-> Airlift order validation check" << std::endl;
    if (source->getOwnerId() != currentPlayer->getId())
    {
        cout << "The source territory is not your own!\n" << endl;
        return false;
    }
    else if (amount > source->getArmies())
    {
        cout << "You do not have this many armies in this territory!\n" << endl;
    }
    else if (amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
    }
    cout << "Your order has been validated!\n" << endl;
  return true;
}

void Airlift::execute() const
{
  if (validate()) {
      if (!currentPlayer->canAttack(target->getOwnerId()))
      {
          cout << "You cannot attack this player!\n" << endl;
          return;
      }
      std::cout << "Airlift execution." << std::endl;
      if (source->getOwnerId() == target->getOwnerId()) // Transferring army to another territory
      {
          source->setArmies(source->getArmies() - amount);
          target->setArmies(target->getArmies() + amount);
      }
      else // If you try to airlift on enemy territory, considered as attack.
      {
          attackSimulation(source, target, currentPlayer, amount);
      }
      cout << "Advance has finished executing!\n" << endl;
  }
}

Order *Airlift::clone() const { return new Airlift(*this); }

std::string Airlift::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}




// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Blockade
//
// -----------------------------------------------------------------------------------------------------------------


Blockade::Blockade(Territory& target, Player& currentPlayer) : Order(currentPlayer)
{
    this->target = &target;
}

const std::string Blockade::label = "Blockade";

std::string Blockade::getLabel() const { return label; }

std::ostream &Blockade::orderCout(std::ostream &output) const { return output << "-> Blockade order."; }

bool Blockade::validate() const
{
  std::cout << "-> Blockade order validation check" << std::endl;
    if(target->getOwnerId() != currentPlayer->getId())
    {
        cout << "This is not your territory! This order can only be played on your own territory!\n" << endl;
        return false;
    }
    cout << "Your order has been validated!\n" << endl;
  return true;
}

void Blockade::execute() const
{
  if (validate()) {
      std::cout << "Blockade execution." << std::endl;
      target->setArmies(target->getArmies() * 3);
      target->setOwnerId(-1); // Transfer to neutral
      cout << "Blockade has finished executing!\n" << endl;
  }
}

Order *Blockade::clone() const { return new Blockade(*this); }

std::string Blockade::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}






// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Bomb
//
// -----------------------------------------------------------------------------------------------------------------


Bomb::Bomb(Territory& target, Player& currentPlayer) : Order(currentPlayer)
{
    this->target = &target;
}

const std::string Bomb::label = "Bomb";

std::string Bomb::getLabel() const { return label; }

std::ostream &Bomb::orderCout(std::ostream &output) const { return output << "-> Bomb order."; }

bool Bomb::validate() const
{
  std::cout << "-> Bomb order validation check" << std::endl;
    if(target->getOwnerId() == currentPlayer->getId())
    {
        cout << "This territory is your own!\n" << endl;
        return false;
    }
    cout << "Your order has been validated!\n" << endl;
  return true;
}

void Bomb::execute() const
{

  if (validate()) {
      if (!currentPlayer->canAttack(target->getOwnerId()))
      {
          cout << "You cannot attack this player!\n" << endl;
          return;
      }
      std::cout << "Bomb execution." << std::endl;
      target->setArmies(ceil(target->getArmies() / 2));
      cout << "Bomb has finished executing!\n" << endl;
  }
}

Order *Bomb::clone() const { return new Bomb(*this); }

std::string Bomb::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}






// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Deploy
//
// -----------------------------------------------------------------------------------------------------------------

Deploy::Deploy(Territory& target, Player& currentPlayer, int amount) : Order(currentPlayer)
{
    this->target = &target;
    this->amount = amount;
}

const std::string Deploy::label = "Deploy";

std::string Deploy::getLabel() const { return label; }

std::ostream &Deploy::orderCout(std::ostream &output) const { return output << "-> Deploy order."; }

bool Deploy::validate() const
{
  std::cout << "-> Deploy order validation check" << std::endl;

    if (target->getOwnerId() != currentPlayer->getId())
    {
        cout << "You do not own this territory!\n" << endl;
        return false;
    }
    else if (amount > currentPlayer->getReinforcementPool())
    {
        cout << "You do not have this many armies in the reinforcement pool!\n" << endl;
        return false;
    }
    else if (amount < 1)
    {
        cout << "Please enter a value that is at least 1 for this order\n" << endl;
    }
    cout << "Your order has been validated!\n" << endl;
  return true;
}

void Deploy::execute() const
{
  if (validate()) {
      std::cout << "Deploy execution." << std::endl;
      target->setArmies(amount + target->getArmies());
      cout << "Deploy has finished executing!\n" << endl;
  }
}

Order *Deploy::clone() const { return new Deploy(*this); }

std::string Deploy::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
}




// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Negotiate
//
// -----------------------------------------------------------------------------------------------------------------


Negotiate::Negotiate(Player& targetPlayer, Player& currentPlayer) : Order(currentPlayer)
{
    this->targetPlayer = &targetPlayer;
}

const std::string Negotiate::label = "Negotiate";

std::string Negotiate::getLabel() const { return label; }

bool Negotiate::validate() const
{
  std::cout << "-> Negotiate order validation check" << std::endl;
    if(targetPlayer->getId() == currentPlayer->getId())
    {
        cout << "You cannot negotiate with yourself.\n" << endl;
        return false;
    }
    cout << "Your order has been validated.\n" << endl;
  return true;
}

void Negotiate::execute() const
{
  if (validate()) {
      std::cout << "Negotiate execution." << std::endl;
      currentPlayer->addFriendly(targetPlayer->getId());
      targetPlayer->addFriendly(currentPlayer->getId());
  }
    cout << "Negotiate has finished executing." << endl;
}


Order *Negotiate::clone() const { return new Negotiate(*this); }

std::ostream &Negotiate::orderCout(std::ostream &ostream) const {
  return ostream << "-> Negotiate order.";
}

std::string Negotiate::stringToLog() {
  std::stringstream ss;
  ss << "ORDER: ";
  ss << "Order Executed ";
  ss << *this;
  return ss.str();
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

void attackSimulation(Territory* source, Territory* target, Player* currentPlayer, int amount)
{
    source->setArmies(source->getArmies() - amount); // Attackers leave home territory

    srand(time(NULL));
    int successAttack = 0;
    int successDefend = 0;

    for (int i = 1; i <= amount; i++) // Attacking Phase
    {
        int roll = rand() % 100 + 1;
        if (roll <= 60)
        {
            successAttack++;
        }
    }

    for (int i = 1; i <= target->getArmies(); i++) // Defending Phase
    {
        int roll = rand() % 100 + 1;

        if (roll <= 70)
        {
            successDefend++;
        }
    }

    int remainingAttackArmies = amount - successDefend;
    int remainingDefendArmies = target->getArmies() - successAttack;

    if (remainingAttackArmies < 0) // Possible if for example 1 attacker vs 70 defenders
    {
        remainingAttackArmies = 0;
    }

    if (remainingDefendArmies < 0) // Possible if for example 1 defender vs 70 attackers
    {
        remainingDefendArmies = 0;
    }

    if (remainingAttackArmies > 0 && remainingDefendArmies == 0) // Win
    {
        cout << "Territory conquered! You have won this battle!\n" << endl;
        target->setOwnerId(currentPlayer->getId()); // Current player now occupies territory
        currentPlayer->getTerritories()->push_back(target);// territory added to player list
        target->setArmies(remainingAttackArmies); // Attackers advance to conquered territory
    }

    else // Lose. A draw is considered a loss. If any, attackers retreat. If any, defenders retreat.
    {
        cout << "Territory has not been conquered. You have lost this battle!\n" << endl;
        source->setArmies(source->getArmies() + remainingAttackArmies); // Attackers retreat
        target->setArmies(remainingDefendArmies);
    }

    if (source->getArmies() == 0)
    {
        cout << "The attacker has lost his territory in the process!\n" << endl;
        source->setOwnerId(-1);
    }

    if (target->getArmies() == 0)
    {
        cout << "The defender has lost his territory in the process!\n" << endl;
        target->setOwnerId(-1);
    }
}