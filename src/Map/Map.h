#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <fstream>


#include "GameEngine/GameEngine.h"
#include "Player/Player.h"


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Territory
//
// ----------------------------------------------------------------------------------------------------------------

class Continent;
class GameEngine;
class Player;

class Territory
{
private:
  Continent* continent;
  std::string name;
  std::vector<Territory*> adjacentTerritories;

  int armies = 0;
  Player* player;

  int x = -1;
  int y = -1;

public:
  // ----------------------------------------
  // Constructors
  // ----------------------------------------
  explicit Territory(std::string name);
  Territory(const Territory &other);

  std::string getName();
  std::vector<Territory *>* getAdjacentTerritories();
  // ----------------------------------------
  // getters and setters
  // ----------------------------------------
  int getArmies() const;
  void setArmies(int);

  Player* getPlayer();
  void setPlayer(Player*);

  int getX() const;
  int getY() const;

  void setX(int x);
  void setY(int y);

  // ----------------------------------------
  // adders and removers
  // ----------------------------------------

  Continent* getContinent();
  void setContinent(Continent* c);

  int removeArmyUnits(int);
  int addArmyUnits(int);

  void addAdjacentTerritory(Territory* territory);

  // ----------------------------------------
  // Operator Overloads
  // ----------------------------------------
  Territory& operator=(const Territory& other);

public:
  // ----------------------------------------
  // ostream overload
  // ----------------------------------------
  friend std::ostream& operator<<(std::ostream& stream, const Territory& other);

};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Map
//
// ----------------------------------------------------------------------------------------------------------------

class Map
{
public:
  std::vector<Continent*> continents;

private:
  std::string name;
  std::string image;
  std::string author;

  bool wrap{};
  bool scroll{};
  bool warn{};

  std::vector<Territory*> territories;


  // Object Owner
  GameEngine* game;

private:
  bool isMapStronglyConnected();
  bool isTerritories1to1Continents();
  void DFS(Territory* territory, std::vector<Territory*>& visited);
  bool isTerritoryStronglyConnected(Territory* territory);

public:
  // --------------------------------------------------
  // Destructors + Constructors + Operator Overloads
  // --------------------------------------------------
  explicit Map(GameEngine* game);
  ~Map();
  bool validate();

  Map(const Map &other);
  Map& operator=(const Map& other);

  // --------------------------------------------------
  // map adders
  // --------------------------------------------------
  void addContinent(Continent* continent);
  void addTerritory(Territory* territory);

  // --------------------------------------------------
  // setters
  // --------------------------------------------------
  void setName(std::string _name);
  void setImage(std::string _image);
  void setAuthor(std::string author);
  void setWrap(bool wrap);
  void setScroll(bool scroll);
  void setWarn(bool warn);

  // --------------------------------------------------
  // getters
  // --------------------------------------------------
  std::string getName();
  std::string getImage();
  std::string getAuthor();
  bool getWrap() const;
  bool getScroll() const;
  bool getWarn() const;
  std::vector<Territory *> * getTerritories();
  std::vector<Continent *> * getContinents();

public:
  friend std::ostream& operator<<(std::ostream& stream, const Map& other);
};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Continent
//
// ----------------------------------------------------------------------------------------------------------------


class Continent
{
public:
    std::vector<Territory*> territories;

private:
  std::string name;
  int bonus;

public:
  // ----------------------------------------
  // Constructors
  // ----------------------------------------
  Continent(std::string name, int bonus);
  Continent(const Continent& other);


  // ----------------------------------------
  // Adders
  // ----------------------------------------
  void addTerritory(Territory* territory);

  // ----------------------------------------
  // Getters
  // ----------------------------------------
  std::string getName();
  int getBonus() const;
  std::vector<Territory *> * getTerritories();

  // ----------------------------------------
  // Operator Overloads
  // ----------------------------------------
  Continent& operator=(const Continent& other);
public:
  // ----------------------------------------
  // Ostream Overload
  // ----------------------------------------
  friend std::ostream& operator<<(std::ostream& stream, const Continent& other);
};



// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Map Loader
//
// ----------------------------------------------------------------------------------------------------------------



class Map;

// Static Class
class MapLoader
{
private:

  // ----------------------------------------
  // State Enum
  // ----------------------------------------
  enum ReadingState
  {
    ReadingState_Idle,
    ReadingState_Map,
    ReadingState_Continents,
    ReadingState_Territories
  };

  // ----------------------------------------
  // Map Loader Data / State
  // ----------------------------------------
  struct MapLoaderState
  {
    std::unordered_map<std::string, Territory*> territories;
    // territories to add to the map
    std::unordered_map<std::string, Territory*> territoriesToCreate;
    // continent name -> Continent
    std::unordered_map<std::string, Continent*> continents;
    ReadingState parseState = ReadingState_Idle;
  };

  // ----------------------------------------
  // Map Loader Parse Line
  // ----------------------------------------
  static void parseLine(std::string &line, Map* map, MapLoaderState& mapLoaderState);

  // ----------------------------------------
  // Map Loader Line Trim Utilities
  // ----------------------------------------
  static std::string ltrim(const std::string &s);
  static std::string rtrim(const std::string &s);

public:
    static std::string trim(const std::string &s);
  // ----------------------------------------
  // Map Loader Load File
  // ----------------------------------------
  static void load(const std::string& path, Map* out_map);

  // ----------------------------------------
  // Map loader is a static class and should not have any constructor or assignment operator overloaded.
  // ----------------------------------------
  MapLoader() = delete;
  MapLoader(const MapLoader &other) = delete;
  MapLoader& operator=(const MapLoader& other) = delete;

public:
  // ----------------------------------------
  // Map loader cannot be instantiated and therefore cannot be printed out.
  // ----------------------------------------
  friend std::ostream& operator<<(std::ostream& stream, const MapLoader& other) = delete;
};
