#include "Deck.h"

//Default constructor
Deck::Deck() = default;

//Destructor
Deck::~Deck()
{
  for (auto card : deckCards)  {
    delete card;
  }
  deckCards.clear();
}

//copy constructor
Deck::Deck(const Deck &initial)
{
  for (auto &&temp : initial.deckCards) {
    deckCards.push_back(new Cards(*temp));
  }
}

//draw card from the deck of cards
void Deck::draw(Hand& currentHand)
{
  if (deckCards.empty())
  {
    throw std::runtime_error("The deck is currently empty.");
  }
  else
  {
    //add last deck card to user's hand
    currentHand.handCards.push_back(deckCards.back());
    //removes card from the deck of cards after it has been drawn for hand
    deckCards.pop_back();
  }
}

////initialize the deck of cards
//void Deck::initializeDeck()
//{
//  vector<string> cardTypes = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"};
//
//  for (auto & cardType : cardTypes)
//  {
//    auto *card = new Cards();
//    card->setCardType(cardType);
//    for(const auto& c : cardTypes){
//      deckCards.push_back(c);
//    }
//  }
//  //shuffle the cards
//  shuffleDeck();
//}

//method shuffling the deck of cards
void Deck::shuffleDeck()
{
  mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
  shuffle(std::begin(deckCards), std::end(deckCards), rng);
};