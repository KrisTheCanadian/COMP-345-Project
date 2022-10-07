#include "Player.h"

Player::Player() = default;

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
void Player::issueOrder(std::string type){

    // given a type of order, create the appropriate order.

  orders->add(&order);
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

std::vector<Territory *> Player::getTerritories() {
  return territories;
}

Player::~Player() = default;

Player &Player::operator=(const Player &other) {
    this->orders = other.orders;
    this->cards = other.cards;
    this->territories = other.territories;
}

std::ostream &operator<<(std::ostream &out, const Player &player) {
  out << "-------------------" << "\n";
  for(Territory * t : player.territories){
    out << t->getName() << "\n";
  }
  out << "-------------------" << "\n";
  return out;
}
