#include "Player.h"
#include "PlayerStrategies.h"

#include <utility>

Player::Player(GameEngine* game, Hand* cards, std::string name, const std::string& strategy)
  : game(game), hand(cards), name(std::move(name)), reinforcementPool(0)
{
  orders = new OrdersList(game);
  game->addPlayer(this);
  this->strategy = PlayerStrategy::createStrategy(this, strategy);
}

std::vector<Territory *> Player::toDefend() {
  return strategy->toDefend();
}

std::vector<Territory *> Player::toAttack() {
  return strategy->toAttack();
}

// Type of order
void Player::issueOrder() {

  strategy->issueOrder();
}

void Player::addTerritory(Territory& territory) {
  if(territory.getPlayer() == this){ return; }
  if(territory.getPlayer()){ territory.getPlayer()->removeTerritory(territory); }
  territory.setPlayer(this);
  territories.push_back(&territory);
}

void Player::removeTerritory(Territory& territory) {
  territory.setPlayer(nullptr);
  auto end = territories.end();
  for(auto it = territories.begin(); it != end; it++){
    if(territory.getName() == (*it)->getName()){
      territories.erase(it);
      return;
    }
  }
  throw std::runtime_error("Territory wasn't in the player's list.");
}

Player::~Player() {
  delete hand;
  delete orders;
};

Player &Player::operator=(const Player &other) {
  if(this == &other){
    return *this;
  }

  this->game = other.game;
  this->orders = other.orders;
  this->hand = other.hand;
  this->territories = other.territories;
  this->reinforcementPool = other.reinforcementPool;
  this->deployedArmiesThisTurn = other.deployedArmiesThisTurn;
  this->name = other.name;
  this->strategy = other.strategy;

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
void Player::addFriendly(Player* pPlayer) {
  friendlyPlayers.push_back(pPlayer);
}
void Player::clearFriendly() {
  friendlyPlayers.erase(friendlyPlayers.begin(), friendlyPlayers.end());
}

bool Player::canAttack(Player *pPlayer) {
  if(pPlayer == this){return false;}
  for(auto& player : friendlyPlayers){
    if(player == pPlayer){
      return false;
    }
  }
  return true;
}

Territory* Player::findFirstNeighbourTerritory(Territory* target) {
  for(auto& t: *target->getAdjacentTerritories()){
    if(t->getPlayer() == this){
      return t;
    }
  }
  return nullptr;
}

Order* Player::createOrderFromCard(Card* card) {
  return strategy->decideCard(card);
}

std::vector<Player *> Player::getEnemies() {
  vector<Player*> enemies;
  for(auto p: *game->getPlayers()){
    if(this->canAttack(p)){
      enemies.push_back(p);
    }
  }
  return enemies;
}

void Player::addDeployedArmies(int a) {
  deployedArmiesThisTurn += a;
}

int Player::getDeployedArmiesThisTurn() const {
  return deployedArmiesThisTurn;
}
void Player::clearDeploymentArmies() {
  deployedArmiesThisTurn = 0;
}
void Player::removeArmies(int n) {
  reinforcementPool -= n;
  if(reinforcementPool < 0){
    throw std::runtime_error("ASSERT: reinforcementPool overdrawn!");
  }
}
GameEngine *Player::getGameInstance() {
  return game;
}
void Player::setDeployedArmiesThisTurn(int a) {
  deployedArmiesThisTurn = a;
}

void Player::setStrategy(const string& strategyName) {
  strategy = PlayerStrategy::createStrategy(this, strategyName);
}
PlayerStrategy* Player::getStrategy() const {
  return strategy;
}
