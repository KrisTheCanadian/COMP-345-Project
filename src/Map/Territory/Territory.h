#pragma once

#include <string>
#include <vector>
#include <memory>

class Territory
{
private:
    std::string name;
    std::vector<std::shared_ptr<Territory>> adjacentTerritories;

public:
    Territory(std::string name);
    void addAdjacentTerritory(std::shared_ptr<Territory> territory);
    std::string getName();
    std::vector<std::shared_ptr<Territory>> getAdjacentTerritories();
};
