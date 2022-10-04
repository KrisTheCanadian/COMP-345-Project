#pragma once

#include "Cards.h"

#include <vector>

class Cards;

class Hand
{
public:
  //default constructor
  Hand();
  //destruct
  ~Hand();
  //hand copy constructor
  Hand(const Hand &initial);
  //cards pointer vector
  std::vector<Cards *> handCards{};
  void setPlayerID(int playerId);
  int getPlayerID() const;
private:
  int playerID{};
};