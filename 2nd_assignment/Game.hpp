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

  static const int CHANCE_MODULO = 100;

private:

  struct Cell {
    Cell();
    ~Cell();
    Prey *prey;
    Predator *predator;
  };

  bool endGame;
  int preyCnt, predatorCnt;

  sf::RenderWindow window;

  static const sf::Color RED;
  static const sf::Color GREEN;
  static const sf::Color PURPLE;
  static const sf::Color ORANGE;
  static const sf::Color CLEAR;

  const int PREY_PERCENTAGE, PREDATOR_PERCENTAGE;

  static const int ILLNESS_CHANCE = 7;
  static const int WIDTH = 720, HEIGHT = 480;
  static const int NEW_POS_TRIES_THRESHOLD = 4;

  static constexpr double END_GAME_THRESHOLD = 15.0;
  static constexpr double NO_CREATURES_THRESOLD = 1.0;

  Prey* const defaultPrey;
  Predator* const defaultPredator;

  Cell *world, *worldAux;
  sf::Vertex *pixels;

  void initWorld();
  void initPixels();
  void generateCreatures();
  void initEverything();

  void updatePreyState();
  void updatePredatorState();
  void updateState();

  void colorPixel(int&, int&, const sf::Color&);
  void display();

  Vec2D get2DPos(const int&) const; 
  int get1DPos(const Vec2D&) const; 
  int get1DPos(const int&, const int&) const; 

  Vec2D constrain(Vec2D);
};
