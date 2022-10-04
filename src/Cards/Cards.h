#pragma once

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Map; class Hand; class Deck;

class Cards
{
private:
//type of each card
string cardType;

public:
//default constructor
Cards();
//constructor
explicit Cards(string& type);
//destruct
~Cards();
void setCardType(string& type);
string* getCardType();
//cards copy constructor
Cards(const Cards &initial);
};
