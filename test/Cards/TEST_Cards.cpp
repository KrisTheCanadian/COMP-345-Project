#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GameEngine/GameEngine.h"

TEST(CardTestSuite, AddingCards)
{
  // arrange
  auto gameEngine = new GameEngine();
  auto player = new Player(gameEngine, new Hand());
  Deck* deck = gameEngine->getDeck();
  // act
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
  // assert
  auto cards = *deck->getDeckCards();
  EXPECT_EQ(cards.size(), 10);
}

TEST(CardTestSuite, DrawFromDeck)
{
  // arrange
  auto gameEngine = new GameEngine();
  auto player = new Player(gameEngine, new Hand());
  Deck* deck = gameEngine->getDeck();

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
  auto gameEngine = new GameEngine();
  auto player = new Player(gameEngine, new Hand());
  Deck* deck = gameEngine->getDeck();

  deck->addCardToDeck(new Card(CT_Bomb, gameEngine));
  deck->draw(*player->getHand());
  // act
  player->getHand()->getCards()->at(0)->play();
  // assert
  auto cards = *deck->getDeckCards();
  auto player_cards = player->getHand()->getCards();
  EXPECT_EQ(cards.size(), 1);
  EXPECT_TRUE(player_cards->empty());
  EXPECT_FALSE(player->getOrdersListObject()->getList()->empty());
  EXPECT_EQ(player->getOrdersListObject()->getList()->at(0)->getLabel(), "Bomb");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
