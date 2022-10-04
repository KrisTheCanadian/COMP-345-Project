#include "Hand.h"

//Default constructor
Hand::Hand()= default;

//Copy construct
Hand::Hand(const Hand &initial)
{
  for (auto &&temp : initial.handCards) {
    handCards.push_back(new Cards(*temp));
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