#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

#include "Map/Map.h"
#include "Player/Player.h"

class GameEngine;
class Map;
class Player;

using namespace std;

// --------------------------------
// enum for type of card (public)
// --------------------------------
enum CardType: int {
  CT_Bomb = 0,
  CT_Reinforcement,
  CT_Blockade,
  CT_Airlift,
  CT_Diplomacy
};

class Card
{
private:
  //type of each card
  CardType cardType;

  // Object Owner
  GameEngine* game;

public:
  // --------------------------------
  // Play Card
  // --------------------------------
  void play();

  // --------------------------------
  // Constructors
  // --------------------------------
  explicit Card(const CardType& type, GameEngine* game);
  Card(const Card &initial);

  // --------------------------------
  // Destructor
  // --------------------------------
  ~Card();

  // --------------------------------
  // Setters + Getters
  // --------------------------------
  void setCardType(const CardType& type);
  CardType getCardType() const;
  std::string getCardTypeString();

  // --------------------------------
  // Static Method to Map CardType Enum to String
  // --------------------------------
  static std::string CardTypeToString(CardType& c);
};



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

  std::vector<Card *>* getHandCards() { return &handCards; }
};





class Deck
{
private:
  //deck pointer vector
  std::vector<Card *> deckCards;
  // Object Owner
  GameEngine* game;

public:
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
  void create_deck();
private:
  // removes card from deck at random
  Card* removeCardRandom();
};

