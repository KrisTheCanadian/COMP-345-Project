#include "CardsDriver.h"
#include "Cards/Cards.h"

using namespace std;

void testCards(int argc, char** argv) {
  auto gameEngine = new GameEngine(argc, argv);
  auto player = new Player(gameEngine, new Hand(), "name");
  Deck* deck = gameEngine->getDeck();

  cout << "-> Adding 10 cards to deck..." << endl;
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


  cout << "-> shuffling deck..." << endl;
  //Creating a deck of all hand mixed
  deck->shuffleDeck();

  //getting the hand obj
  auto player_hand = player->getHand();

  cout << "-> player draws 4 cards" << endl;
  // Draw deck of hand for players hand
  deck->draw(*player_hand);
  deck->draw(*player_hand);
  deck->draw(*player_hand);
  deck->draw(*player_hand);

  cout << "-> Card in player's hand" << endl;

  for (auto handCard : *player_hand->getHandCards()) {
      cout << handCard->getCardType() << endl;
  }

  cout << "-> Number of Cards in Deck: " << deck->getDeckCards()->size() << endl;
  cout << "-> Number of Cards in Player's hand: " << player_hand->getHandCards()->size() << endl;

  cout << "-> Player Plays a card" << endl;
  gameEngine->setCurrentPlayer(player);
  // play most left hand size card
  Card* card_to_play = player_hand->getHandCards()->at(0);
  card_to_play->play();

  cout << "-> Number of Cards in Deck: " << deck->getDeckCards()->size() << endl;
  cout << "-> Number of Cards in Player's hand: " << player_hand->getHandCards()->size() << endl;

}
