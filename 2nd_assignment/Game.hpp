#pragma once

#include <vector>
#include "Creature.hpp"
#include <SFML/Graphics.hpp>

class Game {
public:

  Game(int, int, int, int);
  ~Game();

  void run();

private:

  struct Cell {
    std::vector < Prey > prey;
    std::vector < Predator > predators;
  };

  sf::RenderWindow window;

  const int WIDTH, HEIGHT;
  static const int MAX_PREY_PER_CELL = 3;
  static const int MULTIPLYER = 4;
  const int PREY_PERCENTAGE, PREDATOR_PERCENTAGE; // out of 100

  Cell *world, *worldAux;

  void initWorld();
  void generateCreatures();
  void updateState();
  void display();
};
