#include "Map.h"

bool Map::validate()
{
  return isMapStronglyConnected() && isTerritories1to1Continents();
}

void Map::DFS(Territory* territory, std::vector<Territory*> &visited)
{
  visited.push_back(territory);
  for (auto adjacent : *territory->getAdjacentTerritories())
  {
    if (std::find(visited.begin(), visited.end(), adjacent) == visited.end())
    {
      DFS(adjacent, visited);
    }
  }
}

bool Map::isTerritoryStronglyConnected(Territory* territory)
{
  std::vector<Territory *> visited{};
  DFS(territory, visited);
  return visited.size() == territories.size();
}

bool Map::isMapStronglyConnected()
{
  return std::all_of(territories.begin(), territories.end(), [this](
      Territory* t)
      {
          auto val = isTerritoryStronglyConnected(t);
          return val;
      });
}

bool Map::isTerritories1to1Continents()
{
  return std::all_of(continents.begin(), continents.end(), [](Continent *c){return !c->getTerritories()->empty();});
}

void Map::addContinent(Continent *continent)
{
  this->continents.push_back(continent);
}

void Map::addTerritory(Territory *territory)
{
  this->territories.push_back(territory);
}

// --------------------------------------------------
// Getters
// --------------------------------------------------
std::string Map::getName()
{
  return this->name;
}

std::string Map::getImage()
{
  return this->image;
}

std::string Map::getAuthor()
{
  return this->author;
}

bool Map::getWrap() const
{
  return this->wrap;
}

bool Map::getScroll() const
{
  return this->scroll;
}

bool Map::getWarn() const
{
  return this->warn;
}

std::vector<Territory*>* Map::getTerritories()
{
  return &this->territories;
}

std::vector<Continent*>* Map::getContinents()
{
  return &this->continents;
}

// --------------------------------------------------
// setters
// --------------------------------------------------

void Map::setName(std::string _name)
{
  this->name = std::move(_name);
}

void Map::setImage(std::string _image)
{
  this->image = std::move(_image);
}

void Map::setAuthor(std::string _author)
{
  this->author = std::move(_author);
}

void Map::setWrap(bool _wrap)
{
  this->wrap = _wrap;
}

void Map::setScroll(bool _scroll)
{
  this->scroll = _scroll;
}

void Map::setWarn(bool _warn)
{
  this->warn = _warn;
}

// --------------------------------------------------
// Destructors + Constructors + Operator Overloads
// --------------------------------------------------

Map::~Map() {
  for(auto t : territories){
    delete t;
  }

  for(auto c : continents){
    delete c;
  }
}


std::ostream &operator<<(std::ostream &stream, const Map &other) {
  stream << "Map Name: " << other.name << '\n'
  << "Map Author: " << other.author << '\n'
  << "Map Image: " << other.image << '\n'
  << "Map Wrap: " << (other.wrap ? "True":"False") << '\n'
  << "Map Scroll: " << (other.scroll ? "Horizontal":"Vertical") << '\n'
  << "Map Warn: " << (other.warn ? "True":"False") << '\n';

  stream << "Map Continents: " << '\n';
  for(auto c : other.continents){
    stream << *c << '\n';
  }

  stream << "Map Territories: " << '\n';
  for(auto t : other.territories){
    stream << *t << '\n';
  }

  return stream;
}

Map::Map(const Map &other)
: name(other.name), author(other.author), warn(other.warn), scroll(other.scroll), image(other.image), wrap(other.wrap), game(other.game)
{
  // deep copy
  for(auto t : territories){
    this->addTerritory(new Territory(*t));
  }
  // deep copy
  for(auto c : continents){
    this->addContinent(new Continent(*c));
  }

}

Map &Map::operator=(const Map &other) {
  if(this == &other){
    return *this;
  }

  this->name = other.name;
  this->image = other.image;
  this->author = other.author;

  this->wrap = other.wrap;
  this->scroll = other.scroll;
  this->warn = other.warn;

  this->continents = other.continents;
  this->territories = other.territories;

  this->game = other.game;

  return *this;
}

Map::Map(GameEngine* game)
  :game(game)
{
  if(game == nullptr){throw std::runtime_error("Map::Error | Cannot set map Game Engine to null");}
}
