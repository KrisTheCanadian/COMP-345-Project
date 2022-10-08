#include "Player.h"

Player::Player(GameEngine* game, Hand* cards)
  : game(game), hand(cards), orders(OrdersList(game))
{}

// default copy constructor
Player::Player(const Player &p) = default;

std::vector<Territory *> Player::toDefend() {
  unsigned length = territories.size();
  if(length > 0){
    auto first = territories.begin();
    auto last = territories.begin() + length/2;
    return {first, last};
  }
  return {};
}

std::vector<Territory *> Player::toAttack() {
  unsigned length = territories.size();
  if(length > 0){
    auto first = territories.begin() + length/2;
    auto last = territories.end();
    return {first, last};
  }
  return {};
}

// Type of order
void Player::issueOrder(CardType cardType){
  // order
  Order* order = nullptr;

  switch(cardType){
    case CT_Bomb:
      order = new Bomb();
      break;
    case CT_Reinforcement:
      // TODO: Assignment 2
      order = nullptr;
      break;
    case CT_Blockade:
      order = new Blockade();
      break;
    case CT_Airlift:
      order = new Airlift();
      break;
    case CT_Diplomacy:
      order = new Negotiate();
      break;
  }
  if(order == nullptr){ return; }
  orders.add(order);
}

void Player::addTerritory(Territory& territory) {
  territories.push_back(&territory);
}

void Player::removeTerritory(Territory& territory) {
  auto end = territories.end();
  for(auto it = territories.begin(); it != end; it++){
    if(territory.getName() == (*it)->getName()){
      territories.erase(it);
    }
  }
}

Player::~Player() {
  for(auto c : *hand->getCards()){
    delete c;
  }
};

Player &Player::operator=(const Player &other) {
  if(this == &other){
    return *this;
  }

  this->game = other.game;
  this->orders = other.orders;
  this->hand = other.hand;
  this->territories = other.territories;
  return *this;
}

std::ostream &operator<<(std::ostream &out, const Player &player) {
  out << "-------------------" << "\n";
  for(auto t : player.territories){
    out << *t << "\n";
  }
  out << "-------------------" << "\n";
  return out;
}

// ----------------------------------------------------------------
// Getters
// ----------------------------------------------------------------

std::vector<Territory *>* Player::getTerritories() {
  return &territories;
}

Hand *Player::getHand() {
  return hand;
}

OrdersList *Player::getOrdersList() {
  return &orders;
}
