#include "Player.h"

#include <utility>

int Player::nextId = 0;

Player::Player(GameEngine* game, Hand* cards, std::string  name)
  : game(game), hand(cards), id(nextId++), name(std::move(name)), reinforcementPool(0)
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
void Player::issueOrder() {

  // for now, only 1 attack and only 1 defend
  static bool attacked = false;
  static bool defended = false;

  // they can do advance order to own territory (defend)
  if(!defended){
    orders->add(new Advance());
    defended = true;
  }

  // they can also advance to enemy territory (attack)
  if(!attacked){
    orders->add(new Advance());
    attacked = true;
  }

  // randomly create

  // if army units in reinforcement pool, then can only create deploy orders
  if(reinforcementPool > 0){
    orders->add(new Deploy());
    // deploy a random amount
    std::random_device dev1;
    std::mt19937 rng1(dev1());
    std::uniform_int_distribution<std::mt19937::result_type> randomAmount(1, reinforcementPool);

    // deploy to a random friendly territory
    int deploymentAmount = (int) randomAmount(rng1);

    std::random_device dev2;
    std::mt19937 rng2(dev2());
    std::uniform_int_distribution<std::mt19937::result_type> distRandomIndexTerritory(0, territories.size() - 1);
    int randomIndex = (int) distRandomIndexTerritory(rng2);

    Territory* randomTerritory = territories.at(randomIndex);
    randomTerritory->setArmies(deploymentAmount);
    reinforcementPool -= deploymentAmount;
    return;
  }

  // then they can create any cards they have
  auto cards = hand->getHandCards();
  if(!cards->empty()){

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> uniformIntDistribution(0, cards->size() - 1);
    int randomIndex = (int) uniformIntDistribution(rng);

    auto randomCard = cards->at(randomIndex);
    // play this card
    randomCard->play();
    return;
  }

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

OrdersList* Player::getOrdersListObject() {
  return orders;
}

int Player::getId() const {
  return id;
}

string Player::getPhase()
{
    return phase;
}

void Player::setPhase(string ph)
{
    phase = std::move(ph);
}

int Player::getReinforcementPool() const
{
    return reinforcementPool;
}

void Player::setReinforcementPool(int i)
{
    reinforcementPool = i;
}

int Player::getContinentBonus()
{
  int continentBonusTotal = 0;
  for(auto & continent : game->getMap()->continents)
  {
      int numOfTerritoriesInContinentMap = (int) continent->territories.size();
      int playerTerritoryIsInContinentCount = 0;

      for(auto & territory : territories)
      {
          if(territory->getContinent()->getName() == continent->getName())
          {
              playerTerritoryIsInContinentCount++;
          }
      }

      if(playerTerritoryIsInContinentCount == numOfTerritoriesInContinentMap)
      {
        continentBonusTotal += continent->getBonus();
      }
  }
    return continentBonusTotal;
}

std::string Player::getName() const {
  return name;
}

void Player::addReinforcement(int reinforcement) {
  reinforcementPool += reinforcement;
}

