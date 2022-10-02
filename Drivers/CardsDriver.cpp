#include "Cards.h"
#include "CardsDriver.h"
#include <iostream>
using namespace std;

void testCards() {
    //Dynamically creating deck obj
    Deck *deck = new Deck();
    //Createing a deck of all cards mixed
    deck->initializeDeck();
    
    //creating the hand obj
    Hand *hand = new Hand(); 

    // Draw deck of cards for players hand
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);
    deck->draw(hand);

    cout << "-> Cards in player's hand" <<endl;

    for (int i=0; i < hand->handCards.size(); i++) {
        cout << hand->handCards[i]->getCardType() <<endl;
    }


}
