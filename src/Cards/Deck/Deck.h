#pragma once

#include <iostream>
#include <random>
#include <chrono>

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
  //deck of cards initializer method
//  void initializeDeck();
  //deck of cards shuffler method
  void shuffleDeck();
};

