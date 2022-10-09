#include "Cards.h"


using namespace std;

//Card constructor with a type parameter
Card::Card(const CardType& type, GameEngine* game)
: cardType(type), game(game)
{
  if(game == nullptr){throw std::runtime_error("Card::Error | Cannot set Card Game Engine to null");}
}

//Copy constructor
Card::Card(const Card &initial)
  : cardType(initial.cardType), game(initial.game)
{
  if(game == nullptr){throw std::runtime_error("Card::Error | Cannot set Card Game Engine to null");}
}

void Card::setCardType(CardType& type)
{
    cardType = type;
}

CardType Card::getCardType()
{
    return cardType;
}

void Card::play() {
  // check to see whose turn it is
  Player* currentPlayer = game->getCurrentPlayerTurn();
  currentPlayer->issueOrder(cardType);
  Card* card = currentPlayer->getHand()->removeCard(cardType);

  if(card == nullptr){ throw std::runtime_error(&"Hand did not contain card type: " [cardType]); }
  Deck* gameDeck = game->getDeck();
  gameDeck->addCardToDeck(card);
}

std::string Card::CardTypeToString(CardType& c) {
  switch (c) {
    case CT_Bomb:
      return "Bomb";
    case CT_Reinforcement:
      return "CT_Reinforcement";
    case CT_Blockade:
      return "Blockade";
    case CT_Airlift:
      return "Airlift";
    case CT_Diplomacy:
      return "Diplomacy";
    default:
      throw std::runtime_error("ASSERT: Invalid Card Type");
  }
}

// Destructor
Card::~Card() = default;






//Copy construct
Hand::Hand(const Hand &initial)
{
  for (auto &&temp : initial.handCards) {
    handCards.push_back(new Card(*temp));
  }
};

//Destruct
Hand::~Hand()
{
  for (auto card : handCards) {
    delete card;
  }
  handCards.clear();
}

std::vector<Card *> *Hand::getCards() {
  return &this->handCards;
}

Card *Hand::getCardFromHand(int index) {
  if (index < 0 || index >= handCards.size()){
    throw std::invalid_argument("Index out of range.");
  }
  return handCards.at(index);
}

void Hand::addToHand(Card *card) {
  if(card == nullptr){
    throw std::invalid_argument("Card is a nullptr.");
  }
  handCards.push_back(card);
}

Card* Hand::removeCard(CardType type) {

  for(int i = 0; i < handCards.size(); i++){
    if(handCards.at(i)->getCardType() == type){
      Card* card = handCards.at(i);
      handCards.erase(handCards.begin() + i);
      return card;
    }
  }
  return nullptr;
}

Hand::Hand() {
  handCards = vector<Card*>();
}






//Default constructor
Deck::Deck(GameEngine* game)
    :game(game)
{}

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
  this->game = initial.game;
  for (auto &&temp : initial.deckCards) {
    deckCards.push_back(new Card(*temp));
  }
}

//draw card from the deck of hand
void Deck::draw(Hand& currentHand)
{
  if (deckCards.empty())
  {
    throw std::runtime_error("The deck is currently empty.");
  }
  Card* c = removeCardRandom();
  currentHand.addToHand(c);
}

//method shuffling the deck of hand
void Deck::shuffleDeck()
{
  std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::shuffle(std::begin(deckCards), std::end(deckCards), rng);
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
