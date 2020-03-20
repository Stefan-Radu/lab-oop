#include "Game.hpp"
#include <thread>
#include <chrono>

Game::Game(int w, int h, int preyPerc, int predatorPerc):
  WIDTH(w), HEIGHT(h), PREY_PERCENTAGE(preyPerc), PREDATOR_PERCENTAGE(predatorPerc) {

  srand(time(0));

  initWorld();
  generateCreatures();

  window.create(sf::VideoMode(WIDTH * MULTIPLYER, HEIGHT * MULTIPLYER), "Predator & Prey");
}

void Game::initWorld() {
  world = new Cell[WIDTH * HEIGHT];
  worldAux = new Cell[WIDTH * HEIGHT];
}

void Game::generateCreatures() {
  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell ) {
    int chance = rand() % 100;
    if (chance < PREY_PERCENTAGE) {
      world[cell].prey.emplace_back();
    }
    else if (chance < PREY_PERCENTAGE + PREDATOR_PERCENTAGE) {
      world[cell].predators.emplace_back();
    }
  }
}

void Game::updatePreyState() {

  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell) {

    Vec2D curPos = get2DPos(cell);
    for (auto &prey : world[cell].prey) {
      prey.updateHealth();
      int newPos = get1DPos(curPos + Vec2D::getRandomWay());
      if (prey.canReproduce()) {
        prey.resetHealth();
        worldAux[newPos].prey.emplace_back();
      }
      worldAux[newPos].prey.emplace_back(prey);
    }

    // clear for next frame
    world[cell].prey.clear();
  }
}

void Game::updatePredatorState() {

  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell) {

    Vec2D curPos = get2DPos(cell);
    for (auto &predator : world[cell].predators) {
      predator.updateHealth();
      int newPos = get1DPos(curPos + Vec2D::getRandomWay());
      
      // try to eat prey
      if (not worldAux[newPos].prey.empty()) {
        auto prey = worldAux[newPos].prey.back();
        worldAux[newPos].prey.pop_back();
        predator.updateHealth(prey.getHealth());
        if (predator.canReproduce()) {
          worldAux[newPos].predators.emplace_back();
        }
      }
      worldAux[newPos].predators.emplace_back(predator);
    }
  }
}

void Game::updateState() {

  updatePreyState();
  updatePredatorState();

  std::swap(world, worldAux);
}

void Game::display() {

  window.clear(sf::Color::Black);
  for (int i = 0; i < HEIGHT; ++ i) {
    for (int j = 0; j < WIDTH; ++ j) {
      
      int preyCnt = (int) preyMap[i][j].size();
      int predatorCnt = (int) predatorMap[i][j].size();

      if (preyCnt + predatorCnt == 0) continue;

      sf::RectangleShape point(sf::Vector2f(MULTIPLYER, MULTIPLYER));
      point.setPosition(j * MULTIPLYER, i * MULTIPLYER);
      if (preyCnt > predatorCnt) {
        point.setFillColor(sf::Color::Green);
      }
      else {
        point.setFillColor(sf::Color::Red);
      }

      window.draw(point);
    }
  }

  window.display();
}

void Game::run() {

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    updateState();
    display();
  }
}

Vec2D Game::get2DPos(const int &cell) const {
  return Vec2D(cell / WIDTH, cell % WIDTH);
}

int Game::get1DPos(const Vec2D &pos) const {
  return pos.i * WIDTH + pos.j;
};

Game::~Game() {
  delete [] world;
  delete [] worldAux;
}
