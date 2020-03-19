#include "Game.hpp"

Game::Game(int w, int h, int preyPerc, int predatorPerc):
  WIDTH(w), HEIGHT(h), PREY_PERCENTAGE(preyPerc), PREDATOR_PERCENTAGE(predatorPerc) {

  initWorld();
  generateCreatures();
}

void Game::initWorld() {
  world.resize(HEIGHT);
  for (auto &line : world) {
    line.resize(WIDTH);
    for (auto &cell : line) {
      cell.resize(2);
      cell[0] = cell[1] = 0;
    }
  }
}

void Game::generateCreatures() {

  srand(time(0));

  prey.resize(WIDTH * HEIGHT / 2, Prey());
  predators.resize(WIDTH * HEIGHT / 2);

  for (int y = 0; y < HEIGHT; ++ y) {
    for (int x = 0; x < WIDTH; ++ x) {

      int chance = rand() % 1000;
      if (chance < PREY_PERCENTAGE) {
        prey[1] = Prey(Vec2D(x, y));
        prey.push_back(Prey(Vec2D(x, y)));
      }
      else if (chance < PREY_PERCENTAGE + PREDATOR_PERCENTAGE) {
        Predator aux(Vec2D(x, y));
        predators.push_back(aux);
        predators.push_back(aux);
      }
    }
  }
}

