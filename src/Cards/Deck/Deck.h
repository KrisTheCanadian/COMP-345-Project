#pragma once

#include <iostream>
#include "Cards.h"
#include "Hand.h"

class Deck
{
public:
  //default constructor
  Deck();
  //destruct
  ~Deck();
  //random card drawer to players hand from remaining deck cards method
  void draw(Hand& currentHand);
  //deck copy constructor
  Deck(const Deck &initial);
  //cards pointer vector
  vector<Cards *> deckCards;
};

