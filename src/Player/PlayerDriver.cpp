#include "PlayerDriver.h"

void testPlayers(){

  // mocking argc and argv
  int argc = 1;
  char* argv[] = {(char*)"-console"};
  // setting up game engine
  auto gameEngine = new GameEngine(argc, argv);
  // creating player
  auto p = new Player(gameEngine, new Hand(), "Bob");

  // loading map to get access of territories
  gameEngine->loadMap("res/TestMap1_valid.map");
  auto map_territories = gameEngine->getMap()->getTerritories();

  // adding certain territories from map to player
  auto t1 = *map_territories->at(0);
  auto t2 = *map_territories->at(1);
  auto t3 = *map_territories->at(2);
  auto t4 = *map_territories->at(3);

  p->addTerritory(t1);
  p->addTerritory(t2);
  p->addTerritory(t3);
  p->addTerritory(t4);

  std::cout << "All 4: " << std::endl;

  for(auto t: *p->getTerritories()){
    std::cout << t->getName() << std::endl;
  }

  // removing a territory
  p->removeTerritory(t4);

  std::cout << "After Removing last one: " << std::endl;

  for(auto t: *p->getTerritories()){
    std::cout << t->getName() << std::endl;
  }


  std::cout << "\n " << std::endl;
  std::cout << "Defending Territories: " << std::endl;
  // printing defended territories
  auto defend = p->toDefend();
  for(auto d: defend){
    std::cout << d->getName() << std::endl;
  }

  std::cout << "\n " << std::endl;
  std::cout << "Attacking Territories: " << std::endl;

  // printing attack territories
  auto attack = p->toAttack();
  for(auto a: attack){
    std::cout << a->getName() << std::endl;
  }

  std::cout << "\n " << std::endl;
  std::cout << "Testing stream insertion overload " << std::endl;
  std::cout << *p << std::endl;

  std::cout << "\n " << std::endl;
  std::cout << "Testing player issueOrder Airlift" << std::endl;
  // issue an order
  p->issueOrder();
  auto orders = p->getOrdersListObject()->getList();
  std::cout << "Order that has been added to Player OrderList: " << std::endl;
  std::cout << *orders->at(0) << std::endl;
}