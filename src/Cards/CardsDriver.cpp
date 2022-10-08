#include "CardsDriver.h"
#include "Cards/Cards.h"

using namespace std;

void testCards() {
  auto gameEngine = new GameEngine();
  auto player = new Player(gameEngine, new Hand());
  Deck* deck = gameEngine->getDeck();

  // initialize deck (10 cards)
  deck->addCardToDeck(new Card(CT_Bomb, gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, gameEngine));
  deck->addCardToDeck(new Card(CT_Airlift, gameEngine));
  deck->addCardToDeck(new Card(CT_Blockade, gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, gameEngine));

  deck->addCardToDeck(new Card(CT_Bomb, gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, gameEngine));
  deck->addCardToDeck(new Card(CT_Bomb, gameEngine));
  deck->addCardToDeck(new Card(CT_Blockade, gameEngine));
  deck->addCardToDeck(new Card(CT_Airlift, gameEngine));


  //Creating a deck of all hand mixed
  deck->shuffleDeck();

  //getting the hand obj
  Hand player_hand = *player->getHand();

  // Draw deck of hand for players hand
  deck->draw(player_hand);
  deck->draw(player_hand);
  deck->draw(player_hand);
  deck->draw(player_hand);

  cout << "-> Card in player's hand" << endl;

  for (auto handCard : player_hand.getHandCards()) {
      cout << handCard->getCardType() << endl;
  }

  cout << "-> Player Plays a card" << endl;
  // play most left hand size card
  player_hand.getHandCards().at(0)->play();

}
