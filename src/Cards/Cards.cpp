#include "Cards.h"


using namespace std;

//Card constructor with a type parameter
Card::Card(const CardType& type, GameEngine* game)
: cardType(type), game(game)
{
  if(game == nullptr){throw std::runtime_error("Card::Error | Cannot set Card Game Engine to null");}
}

//Copy constructor
Card::Card(const Card &initial)
  : cardType(initial.cardType), game(initial.game)
{
  if(game == nullptr){throw std::runtime_error("Card::Error | Cannot set Card Game Engine to null");}
}

void Card::setCardType(CardType& type)
{
    cardType = type;
}

CardType Card::getCardType()
{
    return cardType;
}

void Card::play() {
  // check to see whose turn it is
  Player* currentPlayer = game->getCurrentPlayerTurn();
  currentPlayer->issueOrder(cardType);
  Card* card = currentPlayer->getHand()->removeCard(cardType);

  if(card == nullptr){ throw std::runtime_error(&"Hand did not contain card type: " [cardType]); }
  Deck* gameDeck = game->getDeck();
  gameDeck->addCardToDeck(card);
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
