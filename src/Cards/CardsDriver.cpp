#include "CardsDriver.h"

using namespace std;

void testCards() {
  auto gameEngine = new GameEngine();
  Deck* deck = gameEngine->getDeck();

  //Creating a deck of all hand mixed

  //creating the hand obj
  Hand hand = Hand();

  // Draw deck of hand for players hand
  deck->draw(hand);
  deck->draw(hand);
  deck->draw(hand);
  deck->draw(hand);

  cout << "-> Card in player's hand" << endl;

  for (auto & handCard : hand.getHandCards()) {
      cout << handCard->getCardType() << endl;
  }


}
