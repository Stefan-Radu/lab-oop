#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Vec2D.hpp"
#include "Creature.hpp"

class Game {
public:

  // deleted copy constructor and operator=
  // to avoid additional instancese of the class

  Game(const Game&) = delete;
  Game& operator =(const Game&) = delete;

  // access to the only instance of the class
  static Game& getInstance();

  ~Game();

  // start simulations
  void run();

private:

  // private constructor to avoid instantiation
  Game();

  struct Cell {
    Cell();
    CreatureType type;
    Creature *creature;
    Cell& operator = (const Cell&);
    ~Cell();
  };

  bool endGame;

  sf::RenderWindow window;

  static const sf::Color RED;
  static const sf::Color GREEN;
  static const sf::Color PURPLE;
  static const sf::Color ORANGE;
  static const sf::Color CLEAR;

  const int WIDTH, HEIGHT;
  int PREY_PERCENTAGE, PREDATOR_PERCENTAGE;

  static const int CHANCE_MODULO = 100;
  static const int MAX_CREATURE_PERCENTAGE = 50;
  static const int MAX_CREATURE_HEALTH = 1000;
  static const int MAX_CREATURE_HEALTH_TIC = 100;
  static const int ILLNESS_CHANCE = 7;
  static const int NEXT_POS_TRIES_THRESHOLD = 4;

  double elapsedTime;
  static constexpr double END_GAME_THRESHOLD = 15000.0;
  static constexpr double NO_CREATURES_THRESOLD = 1500;

  Prey* defaultPrey;
  Predator* defaultPredator;

  static int gameCount;
  static Cell nullCell;

  Cell *world, *worldAux;
  sf::Vertex *pixels;

  int userInput(const char*) const;
  void logDetails() const;
  void resetGame();

  void initWorld();
  void initPixels();
  void generateCreatures();
  void initEverything();

  int getNextCellIndex(const int&) const;

  void addCreature(Cell&, CreatureType);
  void removeCreature(Cell&);
  bool notSurvive(const int&);
  void chanceMakeIll(const int&);
  void interact(const int&, const int&);
  void transferLife(const int&, const int&);

  void updateCell(const int&);
  void updateState();

  void colorPixel(int&, int&, const sf::Color&);
  void display();

  Vec2D get2DPos(const int&) const; 
  int get1DPos(const Vec2D&) const; 
  int get1DPos(const int&, const int&) const; 
  Vec2D wrap(Vec2D) const;
};
