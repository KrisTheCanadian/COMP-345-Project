#include <iostream>
#include <memory>

#include "MapLoader.h"

void testLoadMaps(int argc, char *const *argv);

int main(int argc, char *argv[])
{
  testLoadMaps(argc, argv);

  return 0;
}

void testLoadMaps(int argc, char *const *argv) {
  // get cli arguments
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <map file>" << std::endl;
    return;
  }

  std::string path = argv[1];
  // load map
  MapLoader loader;
  std::shared_ptr<Map> map;

  try {
    map = loader.load(path);
  } catch (const std::runtime_error& error){
    std::cout << "Map Format is Invalid" << std::endl;
  }

  std::cout << "Map is valid: " << (map->validate() ? "True" : "False") << std::endl;
}
