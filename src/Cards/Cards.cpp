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

CardType Card::getCardType()
{
    return cardType;
}

void Card::play(Deck* deck, Player* player) {
  player->issueOrder(cardType);
  Card* card = player->getHand()->removeCard(cardType);
  if(card == nullptr){ throw std::runtime_error(&"Hand did not contain card type: " [cardType]); }
  deck->addCardToDeck(card);
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
    default:
      throw std::runtime_error("ASSERT: Invalid Card Type");
  }
}

// Destructor
Card::~Card() = default;
