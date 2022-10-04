#include "Cards.h"

using namespace std;

//Default constructor
Cards::Cards()
{
    cardType = "";
}

//Card constructor with a type parameter
Cards::Cards(string& type) {
    cardType = type;
}

//Copy constructor
Cards::Cards(const Cards &initial)
{
    cardType = initial.cardType;
}

void Cards::setCardType(string& type)
{
    cardType = type;
}

string* Cards::getCardType()
{
    return &cardType;
}

//Destructor
Cards::~Cards() = default;
