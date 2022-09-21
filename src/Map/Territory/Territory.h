#pragma once

#include <string>
#include <vector>
#include <memory>

class Territory
{
private:
    std::string name;
    std::vector<std::shared_ptr<Territory>> adjacentTerritories;
};
