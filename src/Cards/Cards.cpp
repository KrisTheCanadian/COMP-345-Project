#include "Cards.h"


using namespace std;

//Card constructor with a type parameter
Card::Card(CardType& type)
: cardType(type)
{}

//Copy constructor
Card::Card(const Card &initial)
{
    cardType = initial.cardType;
}

void Card::setCardType(CardType& type)
{
    cardType = type;
}

CardType* Card::getCardType()
{
    return &cardType;
}

void Card::play() {
  
}

std::string Card::CardTypeToString(CardType& c) {
  switch (c) {
    case CT_Bomb:
      return "Bomb";
    case CT_Reinforcement:
      return "CT_Reinforcement";
    case CT_Blockade:
      return "Blockade";
    case CT_Airlift:
      return "Airlift";
    case CT_Diplomacy:
      return "Diplomacy";
  }
}

// Destructor
Card::~Card() = default;
