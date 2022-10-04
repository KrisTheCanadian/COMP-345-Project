#pragma once

#include "Cards.h"

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
  vector<Cards *> handCards;
  void setPlayerID(int playerId);
  int getPlayerID() const;
private:
  int playerID{};
};