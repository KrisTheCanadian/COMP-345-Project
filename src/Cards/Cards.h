#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "Map/Map.h"
#include "Deck/Deck.h"
#include "Player/Player.h"
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
  void setCardType(CardType& type);
  CardType getCardType();

  // --------------------------------
  // Static Method to Map CardType Enum to String
  // --------------------------------
  static std::string CardTypeToString(CardType& c);
};
