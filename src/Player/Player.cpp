#include "Player.h"

Player::Player(GameEngine* game, Hand* cards, std::string  name)
  : game(game), hand(cards), name(std::move(name)), reinforcementPool(0)
{
  orders = new OrdersList(game);
  game->addPlayer(this);
}

std::vector<Territory *> Player::toDefend() {
  vector<tuple<Territory*, int>> listOfTerritories;
  // check all neighbours for enemies
  // prioritize defending the territories that are connected to enemies
  for(auto& territory: territories){
    int enemiesTerritories = 0;
    // check for all territories the surrounding territories for enemies
    auto adjacentTerritories = territory->getAdjacentTerritories();
    for(auto& adjTerritory: *adjacentTerritories){
      // check the playerID
      if(adjTerritory->getPlayer() != this && adjTerritory->getPlayer() != nullptr && canAttack(adjTerritory->getPlayer())){
        enemiesTerritories++;
      }
    }
    listOfTerritories.emplace_back(territory, enemiesTerritories);
  }

  // let's sort this stuff
  std::sort(listOfTerritories.begin(), listOfTerritories.end(), [](auto const &t1, auto const &t2) {
    return get<1>(t1) > get<1>(t2); // compare the enemies
  });
  vector<Territory*> response;

  for(auto& t: listOfTerritories){
    response.push_back(std::get<0>(t));
  }

  return response;
}

std::vector<Territory *> Player::toAttack() {
  vector<Territory*> listOfTerritories;
  // check all neighbours for enemies
  // prioritize the territories with fewer enemies
  for(auto& territory: territories){
    // check for all territories the surrounding territories for enemies
    auto adjacentTerritories = territory->getAdjacentTerritories();
    for(auto& adjTerritory: *adjacentTerritories){
      // check the playerID
      if(adjTerritory->getPlayer() != this && adjTerritory->getPlayer() != nullptr && canAttack(adjTerritory->getPlayer())){
        listOfTerritories.push_back(adjTerritory);
      }
    }
  }

  // let's sort this stuff
  sort(listOfTerritories.begin(), listOfTerritories.end(), [ ]( const Territory* lhs, const Territory* rhs)
  {
    return lhs->getArmies() > lhs->getArmies();
  });

  return listOfTerritories;
}

// Type of order
void Player::issueOrder() {

  std::random_device dev3;
  std::mt19937 rng3(dev3());
  std::uniform_int_distribution<std::mt19937::result_type> intDistribution(0, 10);

  int i = (int) intDistribution(rng3);

  // if army units in reinforcement pool, then can only create deploy orders
  if(deployedArmiesThisTurn < reinforcementPool && i < 3){

    // get player toDefend vector
    auto defend = toDefend();

    // deploy a random amount
    std::random_device dev1;
    std::mt19937 rng1(dev1());
    std::uniform_int_distribution<std::mt19937::result_type> randomAmount(1, reinforcementPool - deployedArmiesThisTurn);

    // deploy to a random friendly territory
    int deploymentAmount = (int) randomAmount(rng1);

    std::random_device dev2;
    std::mt19937 rng2(dev2());
    std::uniform_int_distribution<std::mt19937::result_type> distRandomIndexTerritory(0, defend.size() - 1);
    int randomIndex = (int) distRandomIndexTerritory(rng2);

    Territory* randomTerritory = defend.at(randomIndex);
    orders->add(new Deploy(game, randomTerritory, this, deploymentAmount));
    deployedArmiesThisTurn += deploymentAmount;
    return;
  } else if(i == 4){
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
  } else {

    // they can also advance to enemy territory (attack)
    // get to attack vector
    auto attackTerritories = toAttack();

    // random attack territory
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> uniformIntDistribution(0, attackTerritories.size() - 1);

    // no attacks, let's get some neutral territories (neighbours)
    if(attackTerritories.empty()){
      if(territories.empty()){ return; }
      // grab a random territory of ours
      std::uniform_int_distribution<std::mt19937::result_type> uniformIntDistribution2(0, territories.size() - 1);
      int randomIndex = (int)uniformIntDistribution2(rng);
      auto t = territories.at(randomIndex);

      // get neighbours
      auto adj = t->getAdjacentTerritories();
      std::uniform_int_distribution<std::mt19937::result_type> uniformIntDistribution3(0, adj->size() - 1);
      int randomIndexAdj = (int)uniformIntDistribution3(rng);
      // get random neighbour
      auto target = adj->at(randomIndexAdj);

      return orders->add(new Advance(game, t, target, this, t->getArmies() / 2));
    }

    // getting a territory from the priority list
    auto attackTerritory = toAttack()[uniformIntDistribution(rng) % attackTerritories.size()];
    // trying to find a neighbourTerritory
    auto neighbour = findFirstNeighbourTerritory(attackTerritory);

    // we check if we have a valid neighbour
    // we also should check if there are enough armies to attack this territory
    if(neighbour && neighbour->getArmies() > 1){
      // if so then we actually attack (for now with half our troops) -> to keep it simple
      orders->add(new Advance(game, neighbour, attackTerritory, this, neighbour->getArmies() / 2));
    }

  }
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
Order* Player::decideOrder(CardType cardType) {
  switch (cardType) {
    case CT_Bomb:
      return decideCardOrderBomb();
    case CT_Reinforcement:
      decideCardReinforcement();
      return nullptr;
    case CT_Blockade:
      return decideCardOrderBlockade();
    case CT_Airlift:
      return decideCardOrderAirlift();
    case CT_Diplomacy:
      return decideCardOrderNegotiate();
  }
  throw std::runtime_error("Player::decideOrder::Assert CardType invalid");
}

Airlift* Player::decideCardOrderAirlift() {
  if(territories.size() < 2){
    // we can't really decide because there's not enough territories
    return nullptr;
  }

  bool validPlay = false;

  // check if airlift can be applied
  for(auto t : territories){
    if(t->getArmies() > 1){
      validPlay = true;
    }
  }

  if(!validPlay){ return nullptr;}

  auto priorityDefendTerritories = toDefend();
  // no territories to defend (cannot decide)
  if(priorityDefendTerritories.empty()){ return nullptr; }
  Territory* source = nullptr;
  Territory* target = nullptr;

  while(source == target || !source || !target){
    std::random_device dev2;
    std::mt19937 rng2(dev2());

    std::uniform_int_distribution<std::mt19937::result_type> distRandomIndexTerritory(0, territories.size() - 1);
    int randomIndex1 = (int) distRandomIndexTerritory(rng2);

    // source should only be a territory with a big enough army
    if(territories.at(randomIndex1)->getArmies() > 1){
      source = territories.at(randomIndex1);
    }

    std::uniform_int_distribution<std::mt19937::result_type> distRandomIndexTerritory1(0, priorityDefendTerritories.size() - 1);
    int randomIndex2 = (int) distRandomIndexTerritory1(rng2);
    target = priorityDefendTerritories.at(randomIndex2);
  }
  return new Airlift(game, source, target, this, (source->getArmies() / 2) + 1);
}

Bomb* Player::decideCardOrderBomb() {
  auto attack = toAttack();
  if(attack.empty()){
    // for now, we will just grab a random player's to defend
    // get enemies
    auto enemies = getEnemies();
    if(enemies.empty()){ return nullptr; }
    while(true){
      // attack random enemy
      std::random_device dev;
      std::mt19937 rng(dev());
      std::uniform_int_distribution<std::mt19937::result_type> distEnemy(0, enemies.size() - 1);
      int randomEnemy = (int) distEnemy(rng);

      auto enemy = enemies.at(randomEnemy);
      if(!enemy->toDefend().empty()){
        auto biggestArmy = enemy->toDefend().back();
        return new Bomb(game, biggestArmy, this);
      }
    }
  }
  // bomb the priority territory
  return new Bomb(game, attack[0], this);
}

Blockade* Player::decideCardOrderBlockade() {
  auto defend = toDefend();
  if(defend.empty()){
    return nullptr;
  }
  return new Blockade(game, defend.back(), this);
}

Negotiate* Player::decideCardOrderNegotiate() {
  // return nullptr if failed to decide on an order
  auto enemies = getEnemies();
  if(enemies.empty()){ return nullptr; }
  auto target = enemies[0];
  for(auto& enemy : enemies){
    if(enemy->territories.size() > target->territories.size()){
      target = enemy;
    }
  }
  return new Negotiate(game, this, target);
}

void Player::decideCardReinforcement() {
  reinforcementPool += 5;
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
