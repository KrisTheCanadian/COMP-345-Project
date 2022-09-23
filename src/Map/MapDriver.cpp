#include <iostream>

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
  loader.load(path);
  return 0;
}