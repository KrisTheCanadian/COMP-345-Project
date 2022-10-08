#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "Player/Player.h"
#include "GameEngine/GameEngine.h"

using namespace std;

class Map;
class Deck;
class Player;
class GameEngine;

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
  explicit Card(CardType& type, GameEngine* game);
  //destruct
  ~Card();
  void setCardType(CardType& type);
  CardType getCardType();
  //hand copy constructor
  Card(const Card &initial);

static std::string CardTypeToString(CardType& c);
};
