#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "Map/Map.h"
#include "Deck/Deck.h"
#include "Player/Player.h"
using namespace std;

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
  // play
  void play();
  //constructor
  explicit Card(const CardType& type, GameEngine* game);
  //destruct
  ~Card();
  void setCardType(CardType& type);
  CardType getCardType();
  //hand copy constructor
  Card(const Card &initial);

static std::string CardTypeToString(CardType& c);
};
