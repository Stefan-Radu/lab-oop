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
      world[cell].prey = new Prey();
    }
    else if (chance < PREY_PERCENTAGE + PREDATOR_PERCENTAGE) {
      ++ predatorCnt;
      world[cell].predator = new Predator();
    }
  }
}

void Game::updatePreyState() {

  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell) {

    if (not world[cell].prey) continue;

    int curPos = cell;
    auto prey = world[cell].prey;
    prey -> updateHealth();

    if (not prey -> isAlive()) {
      delete prey;
      world[cell].predator = nullptr;
      -- predatorCnt;
      continue;
    }

    int newPos = get1DPos(constrain(get2DPos(curPos) + Vec2D::getRandomWay()));

    if (not worldAux[newPos].prey) {
      worldAux[newPos].prey = prey;
      if (prey -> canReproduce() and not worldAux[curPos].prey) {
        prey -> resetHealth();
        ++ preyCnt;
        worldAux[curPos].prey = new Prey();
      }
    }
    else if (not worldAux[curPos].prey) {
      worldAux[curPos].prey = prey;
    }
    else {
      // il pierd asa ca ii transfer viata
      world[curPos].prey -> updateHealth(prey -> getHealth());
      -- preyCnt;
      delete prey;
    }
    
    world[curPos].prey = nullptr;
  }
}

void Game::updatePredatorState() {

  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell) {

    if (not world[cell].predator) continue;


    int curPos = cell;
    auto predator = world[cell].predator;
    predator -> updateHealth();

    if (not predator -> isAlive()) {
      delete predator;
      world[cell].predator = nullptr;
      -- predatorCnt;
      continue;
    }

    int newPos = get1DPos(constrain(get2DPos(curPos) + Vec2D::getRandomWay()));
    
    if (not worldAux[newPos].predator) {

      worldAux[newPos].predator = predator;
      if (worldAux[newPos].prey) {

        predator -> updateHealth(worldAux[newPos].prey -> getHealth());
        -- preyCnt;
        delete worldAux[newPos].prey;
        worldAux[newPos].prey = nullptr;

        if (predator -> canReproduce() and not worldAux[curPos].predator) {
          worldAux[curPos].predator = new Predator(predator -> getExtraHealth());
          ++ predatorCnt;
        }
        else {
          predator -> getExtraHealth();
        }
      }
    }
    else if (not worldAux[curPos].predator) {
      worldAux[curPos].predator = predator;
      if (worldAux[curPos].prey) {
        predator -> updateHealth(worldAux[curPos].prey -> getHealth());
        -- preyCnt;
        delete worldAux[curPos].prey;
        worldAux[curPos].prey = nullptr;
      }
    }
    else {
      -- predatorCnt;
      delete predator;
    }

    // clear for next frame
    world[cell].predator = nullptr;
  }
}

void Game::updateState() {

  updatePreyState();
  updatePredatorState();

  std::swap(world, worldAux);
  /* std::cerr << preyCnt << ' ' << predatorCnt << '\n'; */
}

void Game::display() {

  for (int i = 0; i < HEIGHT; ++ i) {
    for (int j = 0; j < WIDTH; ++ j) {
      
      bool isPrey = world[get1DPos(i, j)].prey;
      bool isPredator = world[get1DPos(i, j)].predator;

      /* std::cerr << isPrey << ' ' << isPredator << '\n'; */

      if ((isPrey or isPredator) == false) {
        pixels[get1DPos(i, j)].color = sf::Color::Black;
        continue;
      }

      if (isPrey) {
        pixels[get1DPos(i, j)].color = sf::Color::Green;
      }
      else {
        pixels[get1DPos(i, j)].color = sf::Color::Red;
      }
    }
  }

  window.clear();
  window.draw(pixels, WIDTH * HEIGHT, sf::Points);
  window.display();
}

void Game::run() {

  while (window.isOpen() and preyCnt + predatorCnt > 0) {

    /* std::cerr << preyCnt << ' ' << predatorCnt << '\n'; */
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

Game::Cell::Cell() {
  prey = nullptr;
  predator = nullptr;
}

Game::Cell::~Cell() {
  delete prey;
  delete predator;
}
