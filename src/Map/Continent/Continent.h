#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Territory.h"

class Continent
{
private:
  std::string name;
  int bonus;
  std::vector<std::shared_ptr<Territory>> territories;

public:
};
