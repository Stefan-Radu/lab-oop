#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Vec2D.hpp"
#include "Creature.hpp"

class Game {
public:

  Game(int, int, int, int);
  ~Game();

  void run();

private:

  struct Cell {
    Cell();
    ~Cell();
    Prey *prey;
    Predator *predator;
  };

  int preyCnt, predatorCnt;

  sf::RenderWindow window;

  const int WIDTH, HEIGHT;
  static const int CHANCE_MODULO = 1000;
  const int PREY_PERCENTAGE, PREDATOR_PERCENTAGE; // out of 100

  Cell *world, *worldAux;
  sf::Vertex *pixels;

  void initWorld();
  void generateCreatures();

  void updatePreyState();
  void updatePredatorState();
  void eatPrey();
  void updateState();

  void display();

  Vec2D get2DPos(const int&) const; 
  int get1DPos(const Vec2D&) const; 
  int get1DPos(const int&, const int&) const; 

  Vec2D constrain(Vec2D);
};
