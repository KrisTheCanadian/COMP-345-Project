#include "UserInputOrder.h"
#include "Deploy.h"
#include "Advance.h"
#include "Bomb.h"
#include "Blockade.h"
#include "Airlift.h"
#include "Negotiate.h"

// Here depnding on the player's cin we create an order.
// If player cins an invalid string a null pointer is returned and
// handled through OrdersList::addOrder()
Order *UserInputOrder::create(const std::string& orderType)
{
  if (orderType == "Deploy") { return new Deploy; }
  else if (orderType == "Advance") { return new Advance; }
  else if (orderType == "Bomb") { return new Bomb; }
  else if (orderType == "Blockade") { return new Blockade; }
  else if (orderType == "Airlift") { return new Airlift; }
  else if (orderType == "Negotiate") { return new Negotiate; }
  else { throw std::runtime_error("Unexpected OrderType: " + orderType ); }
}