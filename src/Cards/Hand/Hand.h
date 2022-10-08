#pragma once

#include <vector>
#include <stdexcept>

#include "Cards/Cards.h"

class Order;
class Card;
enum CardType: int;

class Hand
{
private:
  //hand pointer vector

public:
  std::vector<Card *> handCards;
  //default constructor
  Hand();
  //destruct
  ~Hand();
  //hand copy constructor
  Hand(const Hand &initial);
  // getter handCards
  std::vector<Card *>* getCards();
  // get card from handCards
  Card* getCardFromHand(int index);
  // add to handCards
  void addToHand(Card* card);
  // remove & delete from handCards (once the card is used, it should be deleted)
  Card* removeCard(CardType);

  std::vector<Card *>& getHandCards() { return handCards; }
};