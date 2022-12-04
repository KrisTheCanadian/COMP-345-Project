#include "PlayerStrategies.h"
#include "Player.h"
#include "Cards/Cards.h"
#include "Orders/Orders.h"

PlayerStrategy* PlayerStrategy::createStrategy(Player *player, const std::string& strategy) {

  std::string strategy_name;
  for(auto& c : strategy){strategy_name += (char)std::tolower(c);}

  if(strategy_name == "human") {
    return new Human(player);
  } else if(strategy_name == "aggressive") {
    return new Aggressive(player);
  } else if(strategy_name == "benevolent") {
    return new Benevolent(player);
  } else if(strategy_name == "neutral") {
    return new Neutral(player);
  } else if (strategy_name == "cheater") {
    return new Cheater(player);
  } else if (strategy_name == "random") {
    if (rand() % 2 == 0) {
      return new Aggressive(player);
    } else {
      return new Benevolent(player);
    }
  } else {
    throw std::runtime_error("Invalid strategy name");
  }
}

Human::Human(Player *player) {
  this->player = player;
}

void Human::issueOrder() {
  cout << "Human player " << player->getName() << " is issuing an order." << endl;
  int reinforcementPoolLeft = max(player->getReinforcementPool() - player->getDeployedArmiesThisTurn(), 0);
  int cardsLeft = (int)player->getHand()->getCards()->size();
  cout << "You have " << reinforcementPoolLeft << " left for deployment." << endl;
  cout << "You have " << cardsLeft << " cards in your hand." << endl;

  int choice = 0;
  cout << "What are your orders " << player->getName() << "?" << endl;
  if(reinforcementPoolLeft > 0) {
    cout << "1. Deploy" << endl;
  }
  cout << "2. Advance" << endl;
  if(cardsLeft > 0) {
    cout << "3. Play cards" << endl;
  }
  cout << "4. Exit" << endl;
  cout << "5. Finished issuing orders for the entire turn" << endl;
  cout << "--> ";
  cin >> choice;
  cout << endl;

  switch(choice) {
    case 1:
      if(reinforcementPoolLeft > 0) {
        if(!deploy()){ issueOrder(); }
      } else {
        cout << "You have no armies left to deploy." << endl;
        issueOrder();
      }
      break;
    case 2:
      if(!advance()){ issueOrder(); }
      break;
    case 3:
      if(cardsLeft > 0) {
        if(!playCard()){ issueOrder(); }
      } else {
        cout << "You have no cards to play." << endl;
        issueOrder();
      }
      break;
    case 4:
      cout << "Exiting..." << endl;
      break;
    case 5:
      if(reinforcementPoolLeft > 0) {
        cout << "You have " << reinforcementPoolLeft << " armies left to deploy." << endl;
        cout << "You must deploy all armies before you can end your turn." << endl;
        issueOrder();
      } else {
        isTurnDone = true;
      }
      break;
    default:
      cout << "Invalid choice." << endl;
      issueOrder();
      break;
  }

}

std::vector<Territory *> Human::toDefend() {
  return *player->getTerritories();
}

std::vector<Territory *> Human::toAttack() {
  // get all adjacent territories that are not owned by the player
  std::vector<Territory *> territoriesToAttack;
  for(Territory* territory : *player->getTerritories()) {
    for(Territory* adjacentTerritory : *territory->getAdjacentTerritories()) {
      if(adjacentTerritory->getPlayer() != player && player->canAttack(adjacentTerritory->getPlayer())) {
        territoriesToAttack.push_back(adjacentTerritory);
      }
    }
  }

  // remove duplicates
  sort( territoriesToAttack.begin(), territoriesToAttack.end() );
  territoriesToAttack.erase( unique( territoriesToAttack.begin(), territoriesToAttack.end() ), territoriesToAttack.end() );

  return territoriesToAttack;
}
bool Human::deploy() {
  int reinforcementPoolLeft = max(player->getReinforcementPool() - player->getDeployedArmiesThisTurn(), 0);
  cout << "You have " << reinforcementPoolLeft << " armies left to deploy." << endl;
  cout << "Which territory do you want to deploy to?" << endl;

  int i = 1;
  auto territoriesToDefend = player->toDefend();

  for(Territory* territory : territoriesToDefend) {
    if(deployedTroops.find(territory) != deployedTroops.end()) {
      cout << i << ". " << territory->getName() << " (" << territory->getArmies() << " + " << deployedTroops[territory] << " armies)" << endl;
    } else {
      cout << i << ". " << territory->getName() << " (" << territory->getArmies() << " armies)" << endl;
    }
    i++;
  }

  cout << "--> ";
  int choice;
  cin >> choice;
  cout << endl;

  if(choice < 1 || choice > territoriesToDefend.size()) {
    cout << "Invalid choice." << endl;
    return false;
  }

  Territory* territory = territoriesToDefend.at(choice - 1);

  cout << "How many armies do you want to deploy to " << territory->getName() << "?" << endl;
  cout << "--> ";
  int armies;
  cin >> armies;
  cout << endl;

  if(armies < 1 || armies > reinforcementPoolLeft) {
    cout << "Invalid choice." << endl;
    return false;
  }


  deployedTroops[territory] += armies;
  player->addDeployedArmies(armies);
  player->getOrdersListObject()->add(new Deploy(player->getGameInstance(), territory, player, armies));

  cout << "You have " << player->getReinforcementPool() - player->getDeployedArmiesThisTurn() << " armies left to deploy." << endl;
  cout << endl;
  return true;
}

bool Human::playCard() {
  int cardsLeft = (int)player->getHand()->getCards()->size();
  cout << "You have " << cardsLeft << " cards in your hand." << endl;
  cout << "Which card do you want to play?" << endl;

  int i = 1;
  for(Card* card : *player->getHand()->getCards()) {
    cout << i << ". " << card->getCardTypeString() << endl;
    i++;
  }

  cout << "--> ";
  int choice;
  cin >> choice;
  cout << endl;

  if(choice < 1 || choice > cardsLeft) {
    cout << "Invalid choice." << endl;
    return false;
  }

  Card* card = player->getHand()->getCards()->at(choice - 1);
  card->play();


  cout << "You have " << player->getHand()->getCards()->size() << " cards left in your hand." << endl;
  cout << endl;
  return true;
}

bool Human::advance() {
  int reinforcementPoolLeft = max(player->getReinforcementPool() - player->getDeployedArmiesThisTurn(), 0);
  cout << "You have " << reinforcementPoolLeft << " armies left to deploy." << endl;
  cout << "Which territory do you want to advance from?" << endl;

  int i = 1;
  auto territoriesToDefend = player->toDefend();

  for(Territory* territory : territoriesToDefend) {
    if(deployedTroops.find(territory) != deployedTroops.end()) {
      cout << i << ". " << territory->getName() << " (" << territory->getArmies() << " + " << deployedTroops[territory] << " armies)" << endl;
    } else {
      cout << i << ". " << territory->getName() << " (" << territory->getArmies() << " armies)" << endl;
    }
    i++;
  }

  cout << "--> ";
  int choice;
  cin >> choice;
  cout << endl;

  if(choice < 1 || choice > territoriesToDefend.size()) {
    cout << "Invalid choice." << endl;
    return false;
  }

  Territory* territory = territoriesToDefend.at(choice - 1);

  cout << "Which territory do you want to advance to?" << endl;

  i = 1;
  auto territoriesToAttack = player->toAttack();

  for(auto& t : territoriesToAttack) {
    if(territory->isAdjacent(t)) {
      if(deployedTroops.find(t) != deployedTroops.end()) {
        cout << i++ << ". " << t->getName() << " (" << t->getArmies() << " armies) & (Attacking with " << deployedTroops[t] << " Armies)" << " Owner: " << (t->getPlayer() == nullptr ? "Neutral": t->getPlayer()->getName()) << endl;
      } else {
        cout << i++ << ". " << t->getName() << " (" << t->getArmies() << " armies)" << " Owner: " << (t->getPlayer() == nullptr ? "Neutral": t->getPlayer()->getName()) << endl;
      }
    }
  }

  if(i == 1) {
    cout << "No adjacent territories to attack." << endl;
    return false;
  }

  cout << "--> ";
  cin >> choice;
  cout << endl;

  if(choice < 1 || choice > territoriesToAttack.size()) {
    cout << "Invalid choice." << endl;
    return false;
  }

  Territory* targetTerritory = territoriesToAttack.at(choice - 1);

  cout << "How many armies do you want to advance to " << targetTerritory->getName() << "?" << endl;
  cout << "--> ";
  int armies;
  cin >> armies;
  cout << endl;

  if(armies < 1 || armies > territory->getArmies() + deployedTroops[territory]) {
    cout << "Invalid choice." << endl;
    return false;
  }

  deployedTroops[targetTerritory] += armies;
  deployedTroops[territory] -= armies;

  player->getOrdersListObject()->add(new Advance(player->getGameInstance(), territory, targetTerritory, player, armies));
  cout << endl;
  return true;
}
Order* Human::playReinforcementCard() {
  player->addReinforcement(5);
  cout << "You have gained 5 reinforcements." << endl;
  cout << "You now have " << player->getReinforcementPool() << " reinforcements." << endl;
  return nullptr;
}

Order* Human::playBombCard() {
  cout << "Which territory do you want to bomb?" << endl;

  int i = 1;
  auto territoriesToAttack = player->toAttack();

  for(auto& t : territoriesToAttack) {
    cout << i << ". " << t->getName() << " (" << t->getArmies() << " armies)" << " Owner: " << (t->getPlayer() == nullptr ? "Neutral": t->getPlayer()->getName()) << endl;
    i++;
  }

  cout << "--> ";
  int choice;
  cin >> choice;
  cout << endl;

  if(choice < 1 || choice > territoriesToAttack.size()) {
    cout << "Invalid choice." << endl;
    return playBombCard();
  }

  Territory* targetTerritory = territoriesToAttack.at(choice - 1);

  cout << "You have issued a bomb order on " << targetTerritory->getName() << "." << endl;

  return new Bomb(player->getGameInstance(), targetTerritory, player);
}

Order* Human::playBlockadeCard() {
  cout << "Which territory do you want to blockade?" << endl;

  int i = 1;
  auto territoriesToDefend = player->toDefend();

  for(Territory* territory : territoriesToDefend) {
    cout << i << ". " << territory->getName() << " (" << territory->getArmies() << " armies)" << endl;
    i++;
  }

  cout << "--> ";
  int choice;
  cin >> choice;
  cout << endl;

  if(choice < 1 || choice > territoriesToDefend.size()) {
    cout << "Invalid choice." << endl;
    return playBlockadeCard();
  }

  Territory* territory = territoriesToDefend.at(choice - 1);

  cout << "You have issued a blockade order on " << territory->getName() << "." << endl;

  return new Blockade(player->getGameInstance(), territory, player);
}

Order* Human::playDiplomacyCard() {
  cout << "Which player do you want to make a peace treaty with?" << endl;

  int i = 1;
  for(Player* p : *player->getGameInstance()->getPlayers()) {
    if(p != player && player->canAttack(p)) {
      cout << i << ". " << p->getName() << endl;
      i++;
    }
  }

  if(i == 1) {
    cout << "You can't make a peace treaty with anyone." << endl;
    return nullptr;
  }

  cout << "--> ";
  int choice;
  cin >> choice;
  cout << endl;

  if(choice < 1 || choice > player->getGameInstance()->getPlayers()->size() - 1) {
    cout << "Invalid choice." << endl;
    return playDiplomacyCard();
  }

  Player* targetPlayer = player->getGameInstance()->getPlayers()->at(choice - 1);
  cout << "You made a peace treaty with " << targetPlayer->getName() << "." << endl;
  return new Negotiate(player->getGameInstance(), player, targetPlayer);
}

Order* Human::playAirliftCard() {
  cout << "Which territory do you want to airlift from?" << endl;

  int i = 1;
  auto territoriesToDefend = player->toDefend();

  for(Territory* territory : territoriesToDefend) {
    if(territory->getArmies() > 1) {
      cout << i << ". " << territory->getName() << " (" << territory->getArmies() << " armies)" << endl;
      i++;
    }
  }

  if(i == 1) {
    cout << "You don't have any territories with more than 1 army." << endl;
    return nullptr;
  }

  cout << "--> ";
  int choice;
  cin >> choice;
  cout << endl;

  if(choice < 1 || choice > territoriesToDefend.size()) {
    cout << "Invalid choice." << endl;
    return playAirliftCard();
  }

  Territory* territory = territoriesToDefend.at(choice - 1);

  cout << "Which territory do you want to airlift to?" << endl;

  i = 1;
  auto territoriesToAttack = player->toAttack();

  for(auto& t : territoriesToAttack) {
    cout << i << ". " << t->getName() << " (" << t->getArmies() << " armies)" << " Owner: " << (t->getPlayer() == nullptr ? "Neutral": t->getPlayer()->getName()) << endl;
    i++;
  }

  cout << "--> ";
  cin >> choice;
  cout << endl;

  if(choice < 1 || choice > territoriesToAttack.size()) {
    cout << "Invalid choice." << endl;
    return playAirliftCard();
  }

  Territory* targetTerritory = territoriesToAttack.at(choice - 1);

  cout << "How many armies do you want to airlift to " << targetTerritory->getName() << "?" << endl;
  cout << "--> ";
  int armies;
  cin >> armies;
  cout << endl;

  if(armies < 1 || armies > territory->getArmies()) {
    cout << "Invalid choice." << endl;
    return playAirliftCard();
  }

  cout << "You have issued an airlift order from territory" << territory->getName() << " to territory " << targetTerritory->getName() << "." << endl;
  return new Airlift(player->getGameInstance(), territory, targetTerritory, player, armies);
}

Order* Human::decideCard(Card* card) {
  switch(card->getCardType()) {
    case CardType::CT_Reinforcement:
      return playReinforcementCard();
    case CardType::CT_Bomb:
      return playBombCard();
    case CardType::CT_Blockade:
      return playBlockadeCard();
    case CardType::CT_Diplomacy:
      return playDiplomacyCard();
    case CT_Airlift:
      return playAirliftCard();
  }

  throw std::runtime_error("ASSERT::Human::decideCard Invalid card type.");
}
void Human::reset() {
  this->deployedTroops.clear();
  this->isTurnDone = false;
}


void Aggressive::issueOrder() {
  // deploy armies first
  int leftoverArmies = max(player->getReinforcementPool() - player->getDeployedArmiesThisTurn(), 0);

  int randomChanceOfPlayingCard = rand() % 100;
  if(randomChanceOfPlayingCard > 50 && !player->getHand()->getHandCards()->empty()){
    playCard();
    return;
  }

  // randomly choose to deploy or advance
  if(leftoverArmies > 0 && rand() % 2 == 0) {
    deploy();
  } else {
    advance();
  }
}

std::vector<Territory *> Aggressive::toDefend() {
  vector<tuple<Territory*, int>> listOfTerritories;
  // check all neighbours for enemies
  // prioritize defending the territories that are connected to enemies
  for(auto& territory: *player->getTerritories()){
    int enemiesTerritories = 0;
    // check for all territories the surrounding territories for enemies
    auto adjacentTerritories = territory->getAdjacentTerritories();
    for(auto& adjTerritory: *adjacentTerritories){
      // check the playerID
      if(adjTerritory->getPlayer() != player && adjTerritory->getPlayer() != nullptr && player->canAttack(adjTerritory->getPlayer())){
        enemiesTerritories++;
      }
    }
    listOfTerritories.emplace_back(territory, enemiesTerritories);
  }

  // puts the territories with the most armies first
  std::sort(listOfTerritories.begin(), listOfTerritories.end(), [](auto const &t1, auto const &t2) {
    return get<1>(t1) < get<1>(t2);
  });
  vector<Territory*> response;

  for(auto& t: listOfTerritories){
    response.push_back(std::get<0>(t));
  }

  return response;
}

std::vector<Territory *> Aggressive::toAttack() {
  // get all territories that are not owned by the player
  vector<Territory*> listOfTerritories;
  // check all neighbours for enemies
  // prioritize the territories with fewer enemies
  for(auto& t: *player->getTerritories()) {
    // check for all territories the surrounding territories for enemies
    auto adjacentTerritories = t->getAdjacentTerritories();
    for(auto& adjTerritory: *adjacentTerritories){
      if(adjTerritory->getPlayer() != player && player->canAttack(adjTerritory->getPlayer())){
        listOfTerritories.push_back(adjTerritory);
      }
    }
  }

  // target the territory with the least armies
  sort(listOfTerritories.begin(), listOfTerritories.end(), [ ](const Territory* lhs, const Territory* rhs)
  {
    return lhs->getArmies() > lhs->getArmies();
  });

  return listOfTerritories;
}

Aggressive::Aggressive(Player *player) {
  this->player = player;
}

Order* Aggressive::decideCard(Card* card) {
  switch(card->getCardType()){
    case CT_Bomb:
      return playBombCard();
    case CT_Reinforcement:
      return playReinforcementCard();
    case CT_Blockade:
      return playBlockadeCard();
    case CT_Airlift:
      return playAirliftCard();
    case CT_Diplomacy:
      return playDiplomacyCard();
  }

  throw std::runtime_error("ASSERT::Aggressive::decideCard Invalid card type.");
}

void Aggressive::deploy() {
  cout << "Aggressive player " << player->getName() << " is deploying." << endl;

  auto territoriesToDefend = player->toDefend();

  if(territoriesToDefend.empty()) {
    cout << "You don't have any territories to defend." << endl;
    return;
  }

  Territory* strongestTerritory = territoriesToDefend.at(0);

  cout << "Deploying " << player->getReinforcementPool() << " armies to " << strongestTerritory->getName() << "." << endl;
  player->setDeployedArmiesThisTurn(player->getReinforcementPool());
  player->getOrdersListObject()->add(new Deploy(player->getGameInstance(), strongestTerritory, player, player->getReinforcementPool()));
}

void Aggressive::advance() {
  cout << "Aggressive player " << player->getName() << " is advancing." << endl;

  auto territoriesToAttack = player->toAttack();

  if(territoriesToAttack.empty()) {
    cout << "You don't have any territories to attack." << endl;
    return;
  }

  for(auto& t: territoriesToAttack) {
    // find the strongest territory that can attack the target
    auto territoriesToDefend = player->toDefend();
    // use the strongest territory to attack
    for(auto& t2: territoriesToDefend) {
      if(std::find(t->getAdjacentTerritories()->begin(), t->getAdjacentTerritories()->end(), t2) != t->getAdjacentTerritories()->end()) {
        // check if the territory has enough armies to attack
        if(t2->getArmies() < 3) { continue; }
        // found a territory that can attack the target
        // attack the target
        cout << "Attacking " << t->getName() << " from " << t2->getName() << "." << endl;
        player->getOrdersListObject()->add(new Advance(player->getGameInstance(), t2, t, player, t2->getArmies() - 1));
        return;
      }
    }
  }

  cout << "You don't have any territories to attack." << endl;
}
void Aggressive::playCard() {
  if(player->getHand()->getHandCards()->empty()){ return; }
  // aggressive players will play aggressive cards first

  // play the bomb cards first
  for(auto& card: *player->getHand()->getHandCards()){
      if(card->getCardType() == CardType::CT_Bomb){
        card->play();
        return;
      }
  }

  // play random card
  int randomCard = rand() % player->getHand()->getHandCards()->size();
  player->getHand()->getHandCards()->at(randomCard)->play();
}

Order* Aggressive::playBombCard() {
  cout << "Aggressive player " << player->getName() << " is playing a bomb card." << endl;

  auto territoriesToAttack = player->toAttack();

  if(territoriesToAttack.empty()) {
    cout << "You don't have any territories to attack." << endl;
    return nullptr;
  }

  // find the strongest territory that can attack the target
  auto territoriesToAttackFrom = player->toAttack();

  // get the last territory
  Territory* territoryToAttack = territoriesToAttackFrom.at(territoriesToAttackFrom.size() - 1);

  cout << "Issued Bombing " << territoryToAttack->getName() << "." << endl;
  return new Bomb(player->getGameInstance(), territoryToAttack, player);
}

Order* Aggressive::playBlockadeCard() {
  if(player->getTerritories()->size() == 1) {
    cout << "It's not a good idea to blockade your last territory." << endl;
    return nullptr;
  }

  // never play blockade card on the strongest territory
  auto territoriesToDefend = player->toDefend();
  // pick the territory that has the most amount of enemies around it
  Territory* territoryToBlockade = territoriesToDefend.at(1);
  int territoryWithMostEnemies = 0;

  for(auto& t : territoriesToDefend) {
    int enemies = 0;
    for(auto& adjTerritory: *t->getAdjacentTerritories()) {
      if(adjTerritory->getPlayer() != player) {
        enemies++;
      }
    }
    if(enemies > territoryWithMostEnemies) {
      territoryWithMostEnemies = enemies;
      territoryToBlockade = t;
    }
  }

  cout << "Issued Blockading " << territoryToBlockade->getName() << "." << endl;
  return new Blockade(player->getGameInstance(), territoryToBlockade, player);
}
Order* Aggressive::playReinforcementCard() {
  player->addReinforcement(5);
  cout << "Issued Reinforcement." << endl;
  cout << "You now have " << player->getReinforcementPool() << " armies to deploy." << endl;
  return nullptr;
}
Order* Aggressive::playDiplomacyCard() {
  // make friends with the player with the most territories
  auto players = player->getGameInstance()->getPlayers();
  Player* playerToMakeFriendsWith = players->at(0);
  for(auto& p: *players) {
    if(p->getTerritories()->size() > playerToMakeFriendsWith->getTerritories()->size() && player->canAttack(p)) {
      playerToMakeFriendsWith = p;
    }
  }
  return new Negotiate(player->getGameInstance(), player, playerToMakeFriendsWith);
}
Order* Aggressive::playAirliftCard() {
  if(player->toDefend().size() < 2) {
    cout << "You don't have enough territories to airlift." << endl;
    return nullptr;
  }

  // airlift all armies except one from the strongest territory to territory with the most enemies
  auto territoriesToDefend = player->toDefend();
  auto territoryToAirliftFrom = territoriesToDefend.at(0);
  // pick the territory that has the most amount of enemies around it
  Territory* territoryToAirliftTo = territoriesToDefend.at(1);
  int territoryWithMostEnemies = 0;
  for(auto& t : territoriesToDefend) {
    if(t == territoryToAirliftFrom) { continue; }
    int enemies = 0;
    for(auto& adjTerritory: *t->getAdjacentTerritories()) {
      if(adjTerritory->getPlayer() != player) {
        enemies++;
      }
    }
    if(enemies > territoryWithMostEnemies) {
      territoryWithMostEnemies = enemies;
      territoryToAirliftTo = t;
    }
  }

  cout << "Issued Airlifting " << territoryToAirliftFrom->getName() << " to " << territoryToAirliftTo->getName() << "." << endl;
  return new Airlift(player->getGameInstance(), territoryToAirliftFrom, territoryToAirliftTo, player, territoryToAirliftFrom->getArmies() - 1);
}

Benevolent::Benevolent(Player *player) {
  this->player = player;
}

void Benevolent::issueOrder() {
  int armiesLeftToDeploy = max(player->getReinforcementPool() - player->getDeployedArmiesThisTurn(), 0);

  if(armiesLeftToDeploy > 0){
    cout << "You have " << armiesLeftToDeploy << " armies left to deploy." << endl;
    auto territoriesToDefend = player->toDefend();

    if(territoriesToDefend.empty()) {
      cout << "You don't have any territories to defend." << endl;
      return;
    }

    // deploy armies to the weakest territory
    auto randomWeakTerritory = territoriesToDefend.at(0);
    if(territoriesToDefend.size() > 1){
      randomWeakTerritory = territoriesToDefend.at((rand() % (territoriesToDefend.size() - 1)));
    }

    cout << "Deploying " << armiesLeftToDeploy << " armies to " << randomWeakTerritory->getName() << "." << endl;
    int randomAmountOfArmiesToDeploy = rand() % armiesLeftToDeploy + 1;

    player->addDeployedArmies(randomAmountOfArmiesToDeploy);
    player->getOrdersListObject()->add(new Deploy(player->getGameInstance(), randomWeakTerritory, player, randomAmountOfArmiesToDeploy));
  }
}

std::vector<Territory *> Benevolent::toDefend() {
  vector<tuple<Territory*, int>> listOfTerritories;
  // check all neighbours for enemies
  // prioritize defending the territories that are connected to enemies
  for(auto& territory: *player->getTerritories()){
    int enemiesTerritories = 0;
    // check for all territories the surrounding territories for enemies
    auto adjacentTerritories = territory->getAdjacentTerritories();
    for(auto& adjTerritory: *adjacentTerritories){
      // check the playerID
      if(adjTerritory->getPlayer() != player && adjTerritory->getPlayer() != nullptr && player->canAttack(adjTerritory->getPlayer())){
        enemiesTerritories++;
      }
    }
    listOfTerritories.emplace_back(territory, enemiesTerritories);
  }

  std::sort(listOfTerritories.begin(), listOfTerritories.end(), [](auto const &t1, auto const &t2) {
    return get<1>(t1) > get<1>(t2);
  });
  vector<Territory*> response;

  for(auto& t: listOfTerritories){
    response.push_back(std::get<0>(t));
  }

  return response;
}

std::vector<Territory *> Benevolent::toAttack() {
  // does not attack
  return {};
}
Order* Benevolent::decideCard(Card* card) {
  switch(card->getCardType()) {
    case CardType::CT_Bomb:
      // will not play bombs
      return nullptr;
    case CardType::CT_Blockade:
      return playBlockadeCard();
    case CardType::CT_Reinforcement:
      return playReinforcementCard();
    case CardType::CT_Diplomacy:
      return playDiplomacyCard();
    case CardType::CT_Airlift:
      return playAirliftCard();
    default:
      throw std::runtime_error("ASSERT::Benevolent::decideCard Invalid card type");
  }
}

Order* Benevolent::playReinforcementCard() {
  player->addReinforcement(5);
  cout << "Issued Reinforcement of 5 armies." << endl;
  return nullptr;
}

Order* Benevolent::playBlockadeCard() {
  if(player->toDefend().size() < 2) {
    cout << "You shouldn't blockade your only territory." << endl;
    return nullptr;
  }
  // blockade the weakest territory
  auto territoriesToDefend = player->toDefend();
  auto territoryToBlockade = territoriesToDefend.at(0);
  cout << "Issued Blockade of " << territoryToBlockade->getName() << "." << endl;
  return new Blockade(player->getGameInstance(), territoryToBlockade, player);
}

Order* Benevolent::playDiplomacyCard() {
  // pick the player with the most territories
  auto players = player->getGameInstance()->getPlayers();
  int mostTerritories = 0;
  Player* playerToDiplomacy = nullptr;
  for(auto& p: *players) {
    if(p == player) { continue; }
    if(p->getTerritories()->size() > mostTerritories) {
      mostTerritories = (int)p->getTerritories()->size();
      playerToDiplomacy = p;
    }
  }

  if(playerToDiplomacy == nullptr) {
    cout << "You don't have any players to diplomacy." << endl;
    return nullptr;
  }

  cout << "Issued Diplomacy with " << playerToDiplomacy->getName() << "." << endl;
  return new Negotiate(player->getGameInstance(), player, playerToDiplomacy);
}

Order* Benevolent::playAirliftCard() {
  if(player->toDefend().size() < 2) {
    cout << "You shouldn't airlift your only territory." << endl;
    return nullptr;
  }
  // airlift the strongest territory to the weakest territory
  auto territoriesToDefend = player->toDefend();
  auto territoryToAirliftTo = territoriesToDefend.at(0);
  auto territoryToAirliftFrom = territoriesToDefend.at(territoriesToDefend.size() - 1);
  cout << "Issued Airlift from " << territoryToAirliftFrom->getName() << " to " << territoryToAirliftTo->getName() << "." << endl;
  return new Airlift(player->getGameInstance(), territoryToAirliftTo, territoryToAirliftFrom, player, (territoryToAirliftFrom->getArmies() / 2)  + 1);
}


void Neutral::issueOrder() {
  // does not issue orders
  // skip turn
  if(numberOfTerritoriesLastTurn == -1 || numberOfTerritoriesLastTurn == player->getTerritories()->size()) {
    numberOfTerritoriesLastTurn = (int)player->getTerritories()->size();
    player->setDeployedArmiesThisTurn(player->getReinforcementPool());
    return;
  }
  cout << "Neutral Player " + player->getName() + " has been attacked last turn and is now switching to an Aggressive strategy!" << endl;
  player->setStrategy("Aggressive");
}

std::vector<Territory *> Neutral::toDefend() {
  return {};
}

std::vector<Territory *> Neutral::toAttack() {
  return {};
}

Neutral::Neutral(Player *player) {
  this->player = player;
}

Order* Neutral::decideCard(Card* card) {
  return nullptr;
}


void Cheater::issueOrder() {
  cout << "Cheater Player " + player->getName() + " is issuing orders!" << endl;
  // conquer all adjacent territories
  auto territories = player->getTerritories();

  for(auto& adj : *territories){
    cout << "Cheater Player " + player->getName() + " is conquering " + adj->getName() << endl;
    player->addTerritory(*adj);
  }

  player->setDeployedArmiesThisTurn(player->getReinforcementPool());
  // deploy all armies on all territories
  for(auto& territory: *player->getTerritories()) {
    territory->setArmies(territory->getArmies() + player->getReinforcementPool());
  }

  player->setDeployedArmiesThisTurn(player->getReinforcementPool());
}

std::vector<Territory *> Cheater::toDefend() {
  return {};
}

std::vector<Territory *> Cheater::toAttack() {
  return {};
}

Cheater::Cheater(Player *player) {
  this->player = player;
}
Order* Cheater::decideCard(Card* card) {
  return nullptr;
}
