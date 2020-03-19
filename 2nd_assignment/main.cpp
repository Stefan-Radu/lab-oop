#include <iostream>
#include <fstream>
#include "Game.hpp"
#include "Creature.hpp"

int main () {
  Game *g = new Game(720, 480, 50, 50);
  g -> run();
  delete g;
}
