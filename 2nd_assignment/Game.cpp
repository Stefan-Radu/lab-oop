#include <thread>
#include <chrono>
#include "Game.hpp"

Game::Game(int w, int h, int preyPerc, int predatorPerc):
  WIDTH(w), HEIGHT(h), PREY_PERCENTAGE(preyPerc), PREDATOR_PERCENTAGE(predatorPerc) {

  srand(time(0));

  preyCnt = predatorCnt = 0;

  initWorld();
  generateCreatures();

  pixels = new sf::Vertex[WIDTH * HEIGHT];
  for (int i = 0; i < HEIGHT; ++ i) {
    for (int j = 0; j < WIDTH; ++ j) {
      pixels[get1DPos(i, j)].position = sf::Vector2f(j, i);
    }
  }

  window.create(sf::VideoMode(WIDTH, HEIGHT), "Predator & Prey");

  window.setFramerateLimit(60);
}

void Game::initWorld() {
  world = new Cell[WIDTH * HEIGHT];
  worldAux = new Cell[WIDTH * HEIGHT];
}

void Game::generateCreatures() {
  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell ) {
    int chance = rand() % CHANCE_MODULO;
    if (chance < PREY_PERCENTAGE) {
      ++ preyCnt;
      world[cell].prey.emplace_back();
    }
    else if (chance < PREY_PERCENTAGE + PREDATOR_PERCENTAGE) {
      ++ predatorCnt;
      world[cell].predators.emplace_back();
    }
  }
}

void Game::updatePreyState() {

  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell) {

    Vec2D curPos = get2DPos(cell);
    for (auto &prey : world[cell].prey) {
      prey.updateHealth();
      int newPos = get1DPos(constrain(curPos + Vec2D::getRandomWay()));
      if (prey.canReproduce() and worldAux[newPos].prey.size() < THRESHOLD) {
        prey.resetHealth();
        ++ preyCnt;
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

      if (not predator.isAlive()) {
        -- predatorCnt;
        continue;
      }

      int newPos = get1DPos(constrain(curPos + Vec2D::getRandomWay()));
      
      // try to eat prey
      if (not worldAux[newPos].prey.empty()) {
        auto prey = worldAux[newPos].prey.back();
        worldAux[newPos].prey.pop_back();
        predator.updateHealth(prey.getHealth());
        if (predator.canReproduce()) {
          worldAux[newPos].predators.emplace_back();
        }
        -- preyCnt;
        ++ predatorCnt;
      }
      worldAux[newPos].predators.emplace_back(predator);
    }


    // clear for next frame
    world[cell].predators.clear();
  }
}

void Game::updateState() {

  updatePreyState();
  updatePredatorState();

  /* Cell *sw = world; */
  /* world = worldAux; */
  /* worldAux = sw; */
  std::swap(world, worldAux);

  /* std::cerr << preyCnt << ' ' << predatorCnt << '\n'; */
}

void Game::display() {

  /* window.clear(sf::Color::Black); */
  for (int i = 0; i < HEIGHT; ++ i) {
    for (int j = 0; j < WIDTH; ++ j) {
      
      int preyCnt = (int) world[get1DPos(i, j)].prey.size();
      int predatorCnt = (int) world[get1DPos(i, j)].predators.size();

      /* std::cerr << preyCnt << ' '<< predatorCnt << '\n'; */

      if (preyCnt + predatorCnt == 0) {
        pixels[get1DPos(i, j)].color = sf::Color::Black;
        continue;
      }

      /* sf::RectangleShape point(sf::Vector2f(MULTIPLYER, MULTIPLYER)); */
      /* point.setPosition(j * MULTIPLYER, i * MULTIPLYER); */
      if (preyCnt > predatorCnt) {
        pixels[get1DPos(i, j)].color = sf::Color::Green;
        /* point.setFillColor(sf::Color::Green); */
      }
      else {
        pixels[get1DPos(i, j)].color = sf::Color::Red;
        /* point.setFillColor(sf::Color::Red); */
      }


      /* window.draw(point); */
    }
  }

  window.clear();
  window.draw(pixels, WIDTH * HEIGHT, sf::Points);
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
}

int Game::get1DPos(const int &i, const int &j) const {
  return i * WIDTH + j;
}

Vec2D Game::constrain(Vec2D pos) {
  if (pos.i < 0) pos.i = HEIGHT - 1;
  else if (pos.i >= HEIGHT) pos.i = 0;
  if (pos.j < 0) pos.j = WIDTH - 1;
  else if (pos.j >= WIDTH) pos.j = 0;
  return pos;
}

Game::~Game() {
  delete [] world;
  delete [] worldAux;
}

Cell() {
  prey = nullptr;
  predator = nullptr;
}

~Cell() {
  delete prey;
  delete predator;
}
