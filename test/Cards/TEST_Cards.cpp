#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameEngine/GameEngine.h"

TEST(CardTestSuite, AddingCards)
{
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv, true);
  new Player(&gameEngine, new Hand(), "Rick", "Aggressive");
  Deck* deck = gameEngine.getDeck();
  // act
  deck->addCardToDeck(new Card(CT_Bomb, &gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, &gameEngine));
  deck->addCardToDeck(new Card(CT_Airlift, &gameEngine));
  deck->addCardToDeck(new Card(CT_Blockade, &gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, &gameEngine));

  deck->addCardToDeck(new Card(CT_Bomb, &gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, &gameEngine));
  deck->addCardToDeck(new Card(CT_Bomb, &gameEngine));
  deck->addCardToDeck(new Card(CT_Blockade, &gameEngine));
  deck->addCardToDeck(new Card(CT_Airlift, &gameEngine));
  // assert
  auto cards = *deck->getDeckCards();
  EXPECT_EQ(cards.size(), 10);
}

TEST(CardTestSuite, DrawFromDeck)
{
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv, true);
  auto player = new Player(&gameEngine, new Hand(), "Bob", "Aggressive");
  Deck* deck = gameEngine.getDeck();

  deck->addCardToDeck(new Card(CT_Bomb, &gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, &gameEngine));
  deck->addCardToDeck(new Card(CT_Airlift, &gameEngine));
  deck->addCardToDeck(new Card(CT_Blockade, &gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, &gameEngine));

  deck->addCardToDeck(new Card(CT_Bomb, &gameEngine));
  deck->addCardToDeck(new Card(CT_Diplomacy, &gameEngine));
  deck->addCardToDeck(new Card(CT_Bomb, &gameEngine));
  deck->addCardToDeck(new Card(CT_Blockade, &gameEngine));
  deck->addCardToDeck(new Card(CT_Airlift, &gameEngine));
  // act
  deck->draw(*player->getHand());
  deck->draw(*player->getHand());
  // assert
  auto cards = *deck->getDeckCards();
  auto player_cards = player->getHand()->getCards();
  EXPECT_EQ(cards.size(), 8);
  EXPECT_EQ(player_cards->size(), 2);
}

TEST(CardTestSuite, PlayCard)
{
  // arrange
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};

  GameEngine gameEngine = GameEngine(argc, argv, true);
  gameEngine.loadMap("../res/TestMap1_valid.map");
  auto player = new Player(&gameEngine, new Hand(), "Bob", "Aggressive");
  auto player2 = new Player(&gameEngine, new Hand(), "Rick", "Aggressive");

  auto territories = gameEngine.getMap()->getTerritories();
  player->addTerritory(*territories->at(0));
  player2->addTerritory(*territories->at(1));
  Deck* deck = gameEngine.getDeck();

  deck->addCardToDeck(new Card(CT_Bomb, &gameEngine));
  deck->draw(*player->getHand());
  gameEngine.setCurrentPlayer(player);

  // act
  player->getHand()->getHandCards()->at(0)->play();

  // assert
  EXPECT_EQ(gameEngine.getDeck()->getDeckCards()->size(), 1);
  EXPECT_TRUE(player->getHand()->getHandCards()->empty());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
