#include "Map.h"

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Map
//
// ----------------------------------------------------------------------------------------------------------------

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




// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Territory
//
// ----------------------------------------------------------------------------------------------------------------


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
  this->player = other.player;

  this->armies = other.armies;

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
bool Territory::isAdjacent(Territory*& pTerritory) {
  for(auto t : this->adjacentTerritories){
    if(t == pTerritory){
      return true;
    }
  }
  return false;
}


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Continent
//
// ----------------------------------------------------------------------------------------------------------------



Continent::Continent(std::string name, int bonus)
{
  this->name = std::move(name);
  this->bonus = bonus;
}

void Continent::addTerritory(Territory* territory)
{
  this->territories.push_back(territory);
}

std::string Continent::getName()
{
  return this->name;
}

int Continent::getBonus() const
{
  return this->bonus;
}

std::vector<Territory*>* Continent::getTerritories()
{
  return &this->territories;
}

std::ostream &operator<<(std::ostream &stream, const Continent &other) {
  stream << "Continent Name: " << other.name << '\n'
         << "Continent Bonus: " << other.bonus << '\n';

  stream << "Continent Territories: " << '\n';
  for(auto t: other.territories){
    stream << (*t) << '\n';
  }
  return stream;
}

Continent &Continent::operator=(const Continent &other) {
  if(&other == this){
    return *this;
  }
  this->name = other.name;
  this->bonus = other.bonus;
  this->territories = other.territories;

  return *this;
}

Continent::Continent(const Continent &other) = default;



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                MapLoader
//
// ----------------------------------------------------------------------------------------------------------------


void MapLoader::load(const std::string& path, Map* out_map)
{
  std::ifstream input_file(path, std::ios::in);
  std::string line;

  // check if file is open
  if (!input_file.is_open())
  {
    throw std::runtime_error("Could not open file: " + path);
  }

  MapLoaderState state;

  std::string map_name = path.substr(path.find_last_of('/') + 1);
  out_map->setName(map_name);

  while (getline(input_file, line))
  {
    line = trim(line);
    if(line.empty()) { continue; }

    parseLine(line, out_map, state);
  }

  state.parseState = ReadingState_Idle;
  input_file.close();
}

void MapLoader::parseLine(std::string &line, Map* map, MapLoaderState& mapLoaderState)
{

  switch (mapLoaderState.parseState)
  {
    case ReadingState_Idle:
      if (line == "[Map]")
      {
        mapLoaderState.parseState = ReadingState_Map;
      }
      else
      {
        throw std::runtime_error("Invalid map file");
      }
      break;

    case ReadingState_Map:
      if (line == "[Continents]")
      {
        mapLoaderState.parseState = ReadingState_Continents;
      }
      else
      {
        std::string delimiter = "=";
        if (line.find(delimiter) != std::string::npos)
        {
          std::string key = line.substr(0, line.find(delimiter));
          std::string value = line.substr(line.find(delimiter) + 1, line.length());
          if (key == "author")
          {
            map->setAuthor(value);
          }
          else if (key == "image")
          {
            map->setImage(value);
          }
          else if (key == "wrap")
          {
            map->setWrap(value == "yes");
          }
          else if (key == "scroll")
          {
            map->setScroll(value == "horizontal");
          }
          else if (key == "warn")
          {
            map->setWarn(value == "yes");
          }
        }
      }
      break;

    case ReadingState_Continents:
      if (line == "[Territories]")
      {
        mapLoaderState.parseState = ReadingState_Territories;
      }
      else
      {
        // parse continents
        std::string delimiter = "=";
        if (line.find(delimiter) != std::string::npos)
        {
          std::string name = line.substr(0, line.find(delimiter));
          std::string value = line.substr(line.find(delimiter) + 1, line.length());
          Continent* continent;
          try {
            continent = new Continent(name, std::stoi(value));
          } catch (std::invalid_argument& e){
            throw std::runtime_error("Map Formatting Error: Invalid Continent Bonus.");
          } catch (std::out_of_range& e) {
            throw std::runtime_error("Map Formatting Error: Continent Bonus Coordinate Out Of Range.");
          }

          map->addContinent(continent);
          mapLoaderState.continents[name] = continent;
        }
      }
      break;
      // FORMAT: Territory name, x, y, continent, adjacent territories
    case ReadingState_Territories:

      // parse territories
      std::string delimiter = ",";
      // Territory
      Territory* territory = nullptr;

      if (line.find(delimiter) != std::string::npos)
      {
        std::string name = line.substr(0, line.find(delimiter));
        line = line.substr(line.find(delimiter) + 1, line.length());

        // check if territory exists in territoriesToCreate before creating a new one
        if (mapLoaderState.territoriesToCreate.find(name) != mapLoaderState.territoriesToCreate.end())
        {
          territory = mapLoaderState.territoriesToCreate[name];
          // remove from territoriesToCreate
          mapLoaderState.territoriesToCreate.erase(name);
        }
        else
        {
          territory = new Territory(name);
        }
      }

      // parse the rest of the line
      while (!line.empty())
      {
        auto delimiter_location = line.find(delimiter);
        std::string value = line.substr(0, delimiter_location);
        line = delimiter_location == std::string::npos ? "" : line.substr(delimiter_location + 1, line.length());

        // x
        if (territory->getX() == -1)
        {
          try{
            territory->setX(std::stoi(value));
          } catch (std::invalid_argument& e){
            throw std::runtime_error("Map Formatting Error: Invalid X Coordinate.");
          } catch (std::out_of_range& e) {
            throw std::runtime_error("Map Formatting Error: X Coordinate Out Of Range.");
          }
          continue;
        }
          // y
        else if (territory->getY() == -1)
        {
          try{
            territory->setY(std::stoi(value));
          } catch (std::invalid_argument& e){
            throw std::runtime_error("Map Formatting Error: Invalid Y Coordinate.");
          } catch (std::out_of_range& e) {
            throw std::runtime_error("Map Formatting Error: Y Coordinate Out Of Range.");
          }
          continue;
        }
          // continent
        else if (territory->getContinent() == nullptr)
        {
          // check if continents exists in hashmap
          if (mapLoaderState.continents.find(value) == mapLoaderState.continents.end())
          {
            throw std::runtime_error("Invalid continent: " + value);
          }
          else
          {
            territory->setContinent(mapLoaderState.continents[value]);
            mapLoaderState.continents[value]->addTerritory(territory);
          }
          continue;
        }
          // adjacent territories
        else
        {
          // check if territory exists in hashmap
          if (mapLoaderState.territories.find(value) != mapLoaderState.territories.end())
          {
            territory->addAdjacentTerritory(mapLoaderState.territories[value]);
          }
          else
          {
            Territory* adjacentTerritory;
            // check inside territories to create
            if(mapLoaderState.territoriesToCreate.find(value) != mapLoaderState.territoriesToCreate.end()){
              // use previously created
              adjacentTerritory = mapLoaderState.territoriesToCreate[value];
            } else {
              // create new territory
              adjacentTerritory = new Territory(value);
            }
            territory->addAdjacentTerritory(adjacentTerritory);
            // add to territoriesToCreate
            mapLoaderState.territoriesToCreate[value] = adjacentTerritory;
          }
        }
      }
      mapLoaderState.territories[territory->getName()] = territory;
      map->addTerritory(territory);
      break;
  }
}

// Utils
std::string MapLoader::ltrim(const std::string &s)
{
  size_t start = s.find_first_not_of(" \n\r\t\f\v");
  return (start == std::string::npos) ? "" : s.substr(start);
}

std::string MapLoader::rtrim(const std::string &s)
{
  size_t end = s.find_last_not_of(" \n\r\t\f\v");
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string MapLoader::trim(const std::string &s) {
  return rtrim(ltrim(s));
}