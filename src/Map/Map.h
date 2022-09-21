#pragma once

#include <string>
#include <vector>
#include <memory>

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
    void validate();

public:
    // --------------------------------------------------
    // map adders
    // --------------------------------------------------
    void addContinent(std::shared_ptr<Continent> continent);
    void addTerritory(std::shared_ptr<Territory> territory);

    // --------------------------------------------------
    // setters
    // --------------------------------------------------
    void setName(std::string name);
    void setImage(std::string image);
    void setAuthor(std::string author);
    void setWrap(bool wrap);
    void setScroll(bool scroll);
    void setWarn(bool warn);
    void setTerritories(std::vector<std::shared_ptr<Territory>> territories);
    void setContinents(std::vector<std::shared_ptr<Continent>> continents);

    // --------------------------------------------------
    // getters
    // --------------------------------------------------
    std::string getName();
    std::string getImage();
    std::string getAuthor();
    bool getWrap();
    bool getScroll();
    bool getWarn();
    std::vector<std::shared_ptr<Territory>> getTerritories();
    std::vector<std::shared_ptr<Continent>> getContinents();
};
