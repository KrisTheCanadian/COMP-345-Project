#pragma once

#include "Cards.h"

#include <vector>

class Card;

class Hand
{
private:
  int playerID = -1;
  //cards pointer vector
  std::vector<Card *> handCards;
public:
  //default constructor
  Hand();
  //destruct
  ~Hand();
  //hand copy constructor
  Hand(const Hand &initial);
  void setPlayerID(int playerId);
  int getPlayerID() const;
  // getter handCards
  std::vector<Card *>* getCards();
  // get card from handCards
  Card* getCardFromHand(int index);
  // add to handCards
  void addToHand(Card* card);
  // remove & delete from handCards (once the card is used, it should be deleted)
  void deleteCard(int index);
};