#include "Player.h"

int Player::nextId = 0;

Player::Player(GameEngine* game, Hand* cards): game(game), hand(cards), id(nextId++)
{
  orders = new OrdersList();
  game->addPlayer(this);
}

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
  auto order = OrdersFactory::CreateOrder(cardType);
  orders->add(order);
}

void Player::addTerritory(Territory& territory) {
  territory.setPlayer(this);
  territory.setOwnerId(this->id);
  territory.setPlayer(this);
  territories.push_back(&territory);
}

void Player::removeTerritory(Territory& territory) {
  territory.setPlayer(nullptr);
  territory.setOwnerId(-1);
  auto end = territories.end();
  for(auto it = territories.begin(); it != end; it++){
    if(territory.getName() == (*it)->getName()){
      territory.setOwnerId(-1);
      territories.erase(it);
    }
  }
}

Player::~Player() {
  delete hand;
  delete orders;
};

Player &Player::operator=(const Player &other) {
  if(this == &other){
    return *this;
  }
  this->id = other.id;
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

OrdersList *Player::getOrdersListObject() {
  return orders;
}

int Player::getId() const {
  return id;
}
