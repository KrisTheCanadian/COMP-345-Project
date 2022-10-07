#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <unordered_map>

#include "Continent.h"
#include "Territory.h"

class Map
{

private:
  std::string name;
  std::string image;
  std::string author;

  bool wrap{};
  bool scroll{};
  bool warn{};

  std::vector<Territory*> territories;
  std::vector<Continent*> continents;

private:
  bool isMapStronglyConnected();
  bool isTerritories1to1Continents();
  void DFS(Territory* territory, std::vector<Territory*>& visited);
  bool isTerritoryStronglyConnected(Territory* territory);

public:
  // --------------------------------------------------
  // Destructors + Constructors + Operator Overloads
  // --------------------------------------------------
  Map();
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
