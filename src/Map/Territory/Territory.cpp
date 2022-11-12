#include "Territory.h"


Territory::Territory(std::string name)
  : name(std::move(name)), continent(nullptr), player(nullptr)
{}

void Territory::addAdjacentTerritory(Territory* territory)
{
  this->adjacentTerritories.push_back(territory);
}

std::string Territory::getName()
{
  return this->name;
}

std::vector<Territory *>* Territory::getAdjacentTerritories()
{
  return &this->adjacentTerritories;
}

int Territory::getX() const
{
  return this->x;
}

int Territory::getY() const
{
  return this->y;
}

void Territory::setX(int _x)
{
  this->x = _x;
}

void Territory::setY(int _y)
{
  this->y = _y;
}

Continent* Territory::getContinent()
{
  return this->continent;
}

void Territory::setContinent(Continent* c)
{
  this->continent = c;
}

// avoid deep copy (due to other territories being only pointers)
Territory::Territory(const Territory &other)= default;

Territory& Territory::operator=(const Territory &other) {
  if(this == &other){
    return *this;
  }

  this->name = other.name;
  this->continent = other.continent;

  this->armies = other.armies;
  this->player = other.player;

  this->x = other.x;
  this->y = other.y;

  this->adjacentTerritories = other.adjacentTerritories;
  return *this;
}

std::ostream &operator<<(std::ostream &stream, const Territory &other) {
  stream << "Territory Name: " << other.name << '\n'
  << "Territory Coordinates: " << '(' << other.x << ", " << other.y << ')' << '\n';
  return stream ;
}

int Territory::getArmies() const {
  return this->armies;
}

void Territory::setArmies(int army_units) {
  this->armies = army_units;
}

int Territory::removeArmyUnits(int removed) {
  if(removed < 0){ throw std::runtime_error("Cannot remove a negative amount of army units."); }
  int total = this->armies - removed;
  if(total < 0){ throw std::runtime_error("Cannot remove more armies than the territory currently has."); }
  this->armies = total;
  return total;
}

int Territory::addArmyUnits(int added) {
  if(added < 0){ throw std::runtime_error("Cannot add a negative amount of army units."); }
  int total = this->armies + added;
  this->armies = total;
  return total;
}

Player *Territory::getPlayer() {
  return this->player;
}

void Territory::setPlayer(Player* p) {
  this->player = p;
}