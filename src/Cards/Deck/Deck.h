#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

#include "Cards/Hand/Hand.h"
#include "Cards/Cards.h"
#include "GameEngine/GameEngine.h"

class Card;
class Hand;
class GameEngine;

class Deck
{
private:
  //hand pointer vector
  std::vector<Card *> deckCards;

  // Object Owner
  GameEngine* game;

public:
  //default constructor
  explicit Deck(GameEngine*);
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

