#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <vector>

#include "Hand.h"

class Card;

class Deck
{
private:
  //hand pointer vector
  std::vector<Card *> deckCards;

public:
  //default constructor
  Deck();
  //destruct
  ~Deck();
  //random card drawer to players hand from remaining deck hand method
  void draw(Hand& currentHand);
  //deck copy constructor
  Deck(const Deck &initial);
  //deck of hand shuffler method
  void shuffleDeck();
  // get deck hand
  std::vector<Card *> * getDeckCards();
  // add card to deck
  void addCardToDeck(Card* card);
private:
  // removes card from deck at random
  Card* removeCardRandom();
};

