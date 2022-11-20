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
  cout << "--> ";
  cin >> choice;
  cout << endl;

  switch(choice) {
    case 1:
      if(reinforcementPoolLeft > 0) {
        deploy();
      } else {
        cout << "You have no armies left to deploy." << endl;
        issueOrder();
      }
      break;
    case 2:
      advance();
      break;
    case 3:
      if(cardsLeft > 0) {
        playCard();
      } else {
        cout << "You have no cards to play." << endl;
        issueOrder();
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

  return territoriesToAttack;
}
void Human::deploy() {
  int reinforcementPoolLeft = max(player->getReinforcementPool() - player->getDeployedArmiesThisTurn(), 0);
  cout << "You have " << reinforcementPoolLeft << " armies left to deploy." << endl;
  cout << "Which territory do you want to deploy to?" << endl;

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
    deploy();
    return;
  }

  Territory* territory = territoriesToDefend.at(choice - 1);

  cout << "How many armies do you want to deploy to " << territory->getName() << "?" << endl;
  cout << "--> ";
  int armies;
  cin >> armies;
  cout << endl;

  if(armies < 1 || armies > reinforcementPoolLeft) {
    cout << "Invalid choice." << endl;
    deploy();
    return;
  }

  player->getOrdersListObject()->add(new Deploy(player->getGameInstance(), territory, player, armies));

  cout << "You have " << player->getReinforcementPool() - player->getDeployedArmiesThisTurn() << " armies left to deploy." << endl;
  cout << endl;
  issueOrder();
}

void Human::playCard() {
  int cardsLeft = (int)player->getHand()->getCards()->size();
  cout << "You have " << cardsLeft << " cards in your hand." << endl;
  cout << "Which card do you want to play?" << endl;

  int i = 1;
  for(Card* card : *player->getHand()->getCards()) {
    cout << i << ". " << card->getCardType() << endl;
    i++;
  }

  cout << "--> ";
  int choice;
  cin >> choice;
  cout << endl;

  if(choice < 1 || choice > cardsLeft) {
    cout << "Invalid choice." << endl;
    playCard();
    return;
  }

  Card* card = player->getHand()->getCards()->at(choice - 1);
  card->play();


  cout << "You have " << player->getHand()->getCards()->size() << " cards left in your hand." << endl;
  cout << endl;
  issueOrder();
}

void Human::advance() {
  int reinforcementPoolLeft = max(player->getReinforcementPool() - player->getDeployedArmiesThisTurn(), 0);
  cout << "You have " << reinforcementPoolLeft << " armies left to deploy." << endl;
  cout << "Which territory do you want to advance from?" << endl;

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
    advance();
    return;
  }

  Territory* territory = territoriesToDefend.at(choice - 1);

  cout << "Which territory do you want to advance to?" << endl;

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
    advance();
    return;
  }

  Territory* targetTerritory = territoriesToAttack.at(choice - 1);

  cout << "How many armies do you want to advance to " << targetTerritory->getName() << "?" << endl;
  cout << "--> ";
  int armies;
  cin >> armies;
  cout << endl;

  if(armies < 1 || armies > territory->getArmies()) {
    cout << "Invalid choice." << endl;
    advance();
    return;
  }

  player->getOrdersListObject()->add(new Advance(player->getGameInstance(), territory, targetTerritory, player, armies));

  cout << "You have " << player->getReinforcementPool() - player->getDeployedArmiesThisTurn() << " armies left to deploy." << endl;
  cout << endl;
  issueOrder();
}
Order* Human::playReinforcementCard(Card* card) {
  player->addReinforcement(5);
  return nullptr;
}

Order* Human::playBombCard(Card* card) {
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
    return playBombCard(card);
  }

  Territory* targetTerritory = territoriesToAttack.at(choice - 1);

  return new Bomb(player->getGameInstance(), targetTerritory, player);
}

Order* Human::playBlockadeCard(Card* card) {
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
    return playBlockadeCard(card);
  }

  Territory* territory = territoriesToDefend.at(choice - 1);

  return new Blockade(player->getGameInstance(), territory, player);
}

Order* Human::playDiplomacyCard(Card* card) {
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
    return playDiplomacyCard(card);
  }

  Player* targetPlayer = player->getGameInstance()->getPlayers()->at(choice - 1);

  return new Negotiate(player->getGameInstance(), player, targetPlayer);
}

Order* Human::playAirliftCard(Card* card) {
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
    return playAirliftCard(card);
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
    return playAirliftCard(card);
  }

  Territory* targetTerritory = territoriesToAttack.at(choice - 1);

  cout << "How many armies do you want to airlift to " << targetTerritory->getName() << "?" << endl;
  cout << "--> ";
  int armies;
  cin >> armies;
  cout << endl;

  if(armies < 1 || armies > territory->getArmies()) {
    cout << "Invalid choice." << endl;
    return playAirliftCard(card);
  }

  return new Airlift(player->getGameInstance(), territory, targetTerritory, player, armies);
}

Order* Human::decideCard(Card* card) {
  switch(card->getCardType()) {
    case CardType::CT_Reinforcement:
      return playReinforcementCard(card);
    case CardType::CT_Bomb:
      return playBombCard(card);
    case CardType::CT_Blockade:
      return playBlockadeCard(card);
    case CardType::CT_Diplomacy:
      return playDiplomacyCard(card);
    case CT_Airlift:
      return playAirliftCard(card);
  }

  throw std::runtime_error("ASSERT::Human::decideCard Invalid card type.");
}


void Aggressive::issueOrder() {
}

std::vector<Territory *> Aggressive::toDefend() {
  return {};
}

std::vector<Territory *> Aggressive::toAttack() {
  return {};
}

Aggressive::Aggressive(Player *player) {
  this->player = player;
}
Order* Aggressive::decideCard(Card* card) {
  return nullptr;
}


Benevolent::Benevolent(Player *player) {
  this->player = player;
}

void Benevolent::issueOrder() {
}

std::vector<Territory *> Benevolent::toDefend() {
  return {};
}

std::vector<Territory *> Benevolent::toAttack() {
  return {};
}
Order* Benevolent::decideCard(Card* card) {
  return nullptr;
}


void Neutral::issueOrder() {
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
