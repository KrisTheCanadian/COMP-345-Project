#pragma once

#include <vector>

class Territory;

class Player {
private:
  std::vector<Territory*> territories;
public:
  std::vector<Territory*> toDefend();
  std::vector<Territory*> toAttack();
};