#pragma once

#include "Cards/Cards.h"
#include <iostream>
#include <vector>

class Player;
class Order;
class Territory;

// abstract class
class PlayerStrategy {
public:
  Player* player = nullptr;
public:
  virtual void issueOrder() = 0;
  virtual Order* decideCard(Card*) = 0;
  virtual std::vector<Territory *> toDefend() = 0;
  virtual std::vector<Territory *> toAttack() = 0;
  static PlayerStrategy* createStrategy(Player* player, const std::string& strategy);
};

class Human : public PlayerStrategy {
public:
  explicit Human(Player* player);
  void issueOrder() override;
  std::vector<Territory *> toDefend() override;
  std::vector<Territory *> toAttack() override;
  Order* decideCard(Card*) override;

private:
  void playCard();

  void deploy();
  void advance();

  Order* playReinforcementCard();
  Order* playBombCard();
  Order* playBlockadeCard();
  Order* playDiplomacyCard();
  Order* playAirliftCard();
};

class Aggressive : public PlayerStrategy {
public:
  explicit Aggressive(Player* player);
  void issueOrder() override;
  Order* decideCard(Card* card) override;
  std::vector<Territory *> toDefend() override;
  std::vector<Territory *> toAttack() override;
private:
  void playCard();

  void deploy();
  void advance();

  Order* playBombCard();
  Order* playReinforcementCard();
  Order* playBlockadeCard();
  Order* playDiplomacyCard();
  Order* playAirliftCard();
};

class Benevolent : public PlayerStrategy {
public:
  explicit Benevolent(Player* player);
  void issueOrder() override;
  Order* decideCard(Card* card) override;
  std::vector<Territory *> toDefend() override;
  std::vector<Territory *> toAttack() override;
};

class Neutral : public PlayerStrategy {
public:
  explicit Neutral(Player* player);
  void issueOrder() override;
  Order* decideCard(Card* card) override;
  std::vector<Territory *> toDefend() override;
  std::vector<Territory *> toAttack() override;
};

class Cheater : public PlayerStrategy {
public:
  explicit Cheater(Player* player);
  void issueOrder() override;
  Order* decideCard(Card* card) override;
  std::vector<Territory *> toDefend() override;
  std::vector<Territory *> toAttack() override;
};