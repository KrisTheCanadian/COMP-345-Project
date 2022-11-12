#include <iostream>
#include <memory>

#include "Map/Map.h"

void testLoadMaps() {

  // available map files
  std::vector<std::string> map_files {
    "res/TestMap1_valid.map",
    "res/TestMap2_invalid.map",
    "res/TestMap3_invalid.map",
    "res/TestMap4_valid.map",
    "res/TestMap5_invalid_format.map"
  };
  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};
  // let's load all the maps and check to see if they are valid.
  for(const std::string& p : map_files){
    GameEngine gameEngine = GameEngine(argc, argv);
    auto map = gameEngine.getMap();
    // we make sure to catch our own std::runtime errors for invalid maps
    try {
      MapLoader::load(p, map);
      std::cout << "Map is valid: " << (map->validate() ? "True" : "False") << std::endl;
    } catch (const std::runtime_error& error) {
      std::cout << "Map Format is Invalid: " << error.what() << std::endl;
    }
  }
}
