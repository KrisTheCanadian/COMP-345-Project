#include "OrdersFactory.h"

Order* OrdersFactory::CreateOrder(CardType cardType) {
  switch(cardType){
    case CT_Bomb:
      return new Bomb();
    case CT_Reinforcement:
      // TODO: Assignment 2
      return nullptr;
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
