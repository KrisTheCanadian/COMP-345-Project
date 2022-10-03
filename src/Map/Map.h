#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <unordered_map>

#include "Territory.h"
#include "Continent.h"

class Map
{

private:
    std::string name;
    std::string image;
    std::string author;

    bool wrap;
    bool scroll;
    bool warn;

    std::vector<std::shared_ptr<Territory>> territories;
    std::vector<std::shared_ptr<Continent>> continents;

private:
    bool isMapStronglyConnected();
    bool isTerritories1to1Continents();
    void DFS(const std::shared_ptr<Territory>& territory, std::vector<std::shared_ptr<Territory>> &visited);
    bool isTerritoryStronglyConnected(const std::shared_ptr<Territory>& territory);

public:
    bool validate();

    // --------------------------------------------------
    // map adders
    // --------------------------------------------------
    void addContinent(const std::shared_ptr<Continent> &continent);
    void addTerritory(const std::shared_ptr<Territory> &territory);

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
    std::vector<std::shared_ptr<Territory>> getTerritories();
    std::vector<std::shared_ptr<Continent>> getContinents();
};
