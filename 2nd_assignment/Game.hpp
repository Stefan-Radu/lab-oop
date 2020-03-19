#pragma once

#include <vector>
#include "Creature.hpp"

class Game {
public:

  Game(int, int, int, int);

private:

  const int WIDTH, HEIGHT;
  const int PREY_PERCENTAGE, PREDATOR_PERCENTAGE; // out of 1000

  std::vector < Prey > prey;
  std::vector < Predator > predators;
  std::vector < std::vector < std::vector < int > > > world; 

  void initWorld();
  void generateCreatures();
};
