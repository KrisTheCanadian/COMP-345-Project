#include "CardsDriver.h"

using namespace std;

void testCards() {
    Deck deck = Deck();

    //Creating a deck of all cards mixed
    
    //creating the hand obj
    Hand hand = Hand();

    // Draw deck of cards for players hand
    deck.draw(hand);
    deck.draw(hand);
    deck.draw(hand);
    deck.draw(hand);

    cout << "-> Cards in player's hand" << endl;

    for (auto & handCard : hand.handCards) {
        cout << handCard->getCardType() << endl;
    }


}
