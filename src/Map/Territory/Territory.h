#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <utility>

class Continent;

class Territory
{
private:
    Continent* continent;
    std::string name;
    std::vector<Territory*> adjacentTerritories;
    int x = -1;
    int y = -1;

public:
    explicit Territory(std::string name);
    void addAdjacentTerritory(Territory* territory);

    std::string getName();
    std::vector<Territory *>* getAdjacentTerritories();

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);

    Continent* getContinent();
    void setContinent(Continent* c);

    Territory(const Territory &other);
    Territory& operator=(const Territory& other);

public:
    friend std::ostream& operator<<(std::ostream& stream, const Territory& other);
};
