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
    deckCards.push_back(new Card(*temp));
  }
}

//draw card from the deck of cards
void Deck::draw(Hand& currentHand)
{
  if (deckCards.empty())
  {
    throw std::runtime_error("The deck is currently empty.");
  }
  Card* c = removeCardRandom();
  currentHand.addToHand(c);
}

//method shuffling the deck of cards
void Deck::shuffleDeck()
{
  mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
  shuffle(std::begin(deckCards), std::end(deckCards), rng);
}

void Deck::addCardToDeck(Card* card) {
  deckCards.push_back(card);
}

Card *Deck::removeCardRandom() {
  // randomly get a card from the deck
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> range_deck(0,deckCards.size() - 1);
  int index = (int)range_deck(rng);

  Card* c = deckCards.at(index);
  // remove the card ptr from the deck
  deckCards.erase(deckCards.begin() + index);
  return c;
}

std::vector<Card *> *Deck::getDeckCards() {
  return &this->deckCards;
};
