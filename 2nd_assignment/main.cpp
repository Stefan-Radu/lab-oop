#include <iostream>
#include <fstream>
#include "Game.hpp"

int main () {
  Game *g = new Game();
  g->run();
  delete g;
}
