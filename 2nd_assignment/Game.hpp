#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Vec2D.hpp"
#include "Creature.hpp"

class Game {
public:

  Game();
  Game(int, int);
  Game(int, int, int, int, int, int);

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

  static const int WIDTH = 800, HEIGHT = 600;
  static const int CHANCE_MODULO = 1000;
  const int PREY_PERCENTAGE, PREDATOR_PERCENTAGE; // out of 1000

  const Prey* const defaultPrey;
  const Predator* const defaultPredator;

  Cell *world, *worldAux;
  sf::Vertex *pixels;

  void initWorld();
  void initPixels();
  void generateCreatures();
  void initEverything();

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
