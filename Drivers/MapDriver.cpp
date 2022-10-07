#include <iostream>
#include <memory>

#include "MapLoader.h"

void testLoadMaps() {

  std::vector<std::string> map_files {
    "res/TestMap1_valid.map",
    "res/TestMap2_invalid.map",
    "res/TestMap3_invalid.map",
    "res/TestMap4_valid.map",
    "res/TestMap5_invalid_format.map"
  };

  for(auto& p : map_files){
    // load map
    MapLoader loader;
    Map* map;

    try {
      map = loader.load(p);
      std::cout << "Map is valid: " << (map->validate() ? "True" : "False") << std::endl;
    } catch (const std::runtime_error& error) {
      std::cout << "Map Format is Invalid: " << error.what() << std::endl;
    }

  }
}
