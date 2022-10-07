#pragma once

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Map; class Hand; class Deck;

enum CardType {
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

public:
// play
void play();
//constructor
explicit Card(CardType& type);
//destruct
~Card();
void setCardType(CardType& type);
CardType* getCardType();
//cards copy constructor
Card(const Card &initial);

static std::string CardTypeToString(CardType& c);
};
