#pragma once

#include <vector>
#include <stdexcept>

#include "Cards/Cards.h"

//class Player;
class Card;

enum CardType : int;

class Hand
{
private:
  int playerID = -1;
  //hand pointer vector
  std::vector<Card *> handCards;
public:
  //default constructor
  Hand() = default;
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
  Card* removeCard(CardType);

  std::vector<Card *>& getHandCards() { return handCards; }
};