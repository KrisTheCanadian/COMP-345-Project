#pragma once

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <utility>

class Continent;

class Territory
{
private:
    std::shared_ptr<Continent> continent;
    std::string name;
    std::vector<std::shared_ptr<Territory>> adjacentTerritories;
    int x = -1;
    int y = -1;

public:
    explicit Territory(std::string name);
    void addAdjacentTerritory(const std::shared_ptr<Territory>& territory);

    std::string getName();
    std::vector<std::shared_ptr<Territory>> getAdjacentTerritories();

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);

    std::shared_ptr<Continent> getContinent();
    void setContinent(std::shared_ptr<Continent> c);
};
