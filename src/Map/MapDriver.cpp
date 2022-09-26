#include <iostream>
#include <memory>

#include "MapLoader.h"

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <map file>" << std::endl;
    return 1;
  }
  // get cli arguments
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
  return 0;
}