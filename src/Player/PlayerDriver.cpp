#include "PlayerDriver.h"

void testPlayers(){
  Player p = Player(new Deck(), new Hand());
  Territory t1 = Territory("Territory 1");
  Territory t2 = Territory("Territory 2");
  Territory t3 = Territory("Territory 3");
  Territory t4 = Territory("Territory 4");

  p.addTerritory(t1);
  p.addTerritory(t2);
  p.addTerritory(t3);
  p.addTerritory(t4);

  std::cout << "All 4: " << std::endl;

  for(auto t: *p.getTerritories()){
    std::cout << t->getName() << std::endl;
  }

  p.removeTerritory(t4);

  std::cout << "After Removing last one: " << std::endl;

  for(auto t: *p.getTerritories()){
    std::cout << t->getName() << std::endl;
  }

  std::cout << "\n " << std::endl;
  std::cout << "Defending Territories: " << std::endl;

  auto defend = p.toDefend();
  for(auto d: defend){
    std::cout << d->getName() << std::endl;
  }

  std::cout << "\n " << std::endl;
  std::cout << "Attacking Territories: " << std::endl;

  auto attack = p.toAttack();
  for(auto a: attack){
    std::cout << a->getName() << std::endl;
  }

  std::cout << "\n " << std::endl;
  std::cout << "Testing stream insertion overload " << std::endl;
  std::cout << p << std::endl;
}