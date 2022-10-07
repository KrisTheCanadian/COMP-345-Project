#include <stdexcept>
#include "Hand.h"

//Default constructor
Hand::Hand()= default;

//Copy construct
Hand::Hand(const Hand &initial)
{
  for (auto &&temp : initial.handCards) {
    handCards.push_back(new Card(*temp));
  }
};


//Destruct
Hand::~Hand()
{
  for (auto card : handCards) {
    delete card;
  }
  handCards.clear();
}

void Hand::setPlayerID(int playerId) {
  playerID = playerId;
}

int Hand::getPlayerID() const {
  return playerID;
}

std::vector<Card *> *Hand::getCards() {
  return &this->handCards;
}

Card *Hand::getCardFromHand(int index) {
  if (index < 0 || index >= handCards.size()){
    throw std::invalid_argument("Index out of range.");
  }
  return handCards.at(index);
}

void Hand::addToHand(Card *card) {
  if(card == nullptr){
    throw std::invalid_argument("Card is a nullptr.");
  }
  handCards.push_back(card);
}

void Hand::deleteCard(int index) {
  if (index < 0 || index >= handCards.size()){
    throw std::invalid_argument("Index out of range.");
  }

  // delete heap allocated card
  delete handCards.at(index);
  handCards.erase(handCards.begin() + index);
}
