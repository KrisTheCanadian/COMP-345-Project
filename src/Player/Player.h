#pragma once

#include <memory>

#include "Territory.h"

class Player {
private:
  std::vector<std::shared_ptr<Territory>> territories;
public:
  std::vector<std::shared_ptr<Territory>> toDefend();
  std::vector<std::shared_ptr<Territory>> toAttack();
};