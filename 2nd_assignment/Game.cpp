#include "Game.hpp"
#include <chrono>

//========================================= Initialization =====================

const sf::Color Game::GREEN(180, 255, 14, 255);
const sf::Color Game::RED(217, 31, 39, 255);
const sf::Color Game::PURPLE(201, 0, 184, 255);
const sf::Color Game::ORANGE(201, 154, 0, 255);
const sf::Color Game::CLEAR(0, 0, 0, 15);

Game::Game():
  PREY_PERCENTAGE(10), PREDATOR_PERCENTAGE(10),
  defaultPrey(new Prey()), defaultPredator(new Predator()) {
  initEverything();
}

Game::Game(int preyPerc, int predatorPerc):
  PREY_PERCENTAGE(preyPerc), PREDATOR_PERCENTAGE(predatorPerc),
  defaultPrey(new Prey()), defaultPredator(new Predator()) {
  initEverything();
}

Game::Game(int preyPerc, int predatorPerc, int mh1, int ht1, int mh2, int ht2):
  PREY_PERCENTAGE(preyPerc), PREDATOR_PERCENTAGE(predatorPerc),
  defaultPrey(new Prey(mh1, ht1)), defaultPredator(new Predator(mh2, ht2)) {
  initEverything();
}

void Game::initEverything() {

  srand(time(0));

  endGame = false;
  preyCnt = predatorCnt = 0;

  initWorld();
  initPixels();
  generateCreatures();

  window.create(sf::VideoMode(WIDTH << 1, HEIGHT << 1), "Predator & Prey");
  window.setFramerateLimit(30);
  window.setVerticalSyncEnabled(true);
}

void Game::initWorld() {
  world = new Cell[WIDTH * HEIGHT];
  worldAux = new Cell[WIDTH * HEIGHT];
}

void Game::initPixels() {
  pixels = new sf::Vertex[WIDTH * HEIGHT << 2];
  for (int i = 0; i < (HEIGHT << 1); ++ i) {
    for (int j = 0; j < (WIDTH << 1); ++ j) {
      pixels[i * (WIDTH << 1) + j].position = sf::Vector2f(j, i);
    }
  }
}

void Game::generateCreatures() {
  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell ) {
    int chance = rand() % CHANCE_MODULO;
    if (chance < PREY_PERCENTAGE) {
      ++ preyCnt;
      world[cell].prey = new Prey(*defaultPrey);
    }
    else if (chance < PREY_PERCENTAGE + PREDATOR_PERCENTAGE) {
      ++ predatorCnt;
      world[cell].predator = new Predator(*defaultPredator);
    }
  }
}

//========================================= Game logic =====================

void Game::updatePreyState() {

  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell) {

    if (not world[cell].prey) continue;

    Prey *&prey = world[cell].prey;

    prey -> updateHealth();

    if (not prey -> isAlive()) {
      delete prey;
      -- preyCnt;
      prey = nullptr;
      continue;
    }

    if (endGame and rand() % CHANCE_MODULO < ILLNESS_CHANCE) prey -> makeIll();

    int newPos = get1DPos(constrain(get2DPos(cell) + Vec2D::getRandomWay()));

    for (int i = 0; i < NEW_POS_TRIES_THRESHOLD and worldAux[newPos].prey; ++ i) {
      newPos = get1DPos(constrain(get2DPos(cell) + Vec2D::getRandomWay()));
    }

    if (not worldAux[newPos].prey) {
      worldAux[newPos].prey = prey;
      if (not worldAux[cell].prey and prey -> canReproduce()) {
        prey -> resetHealth();
        ++ preyCnt;
        worldAux[cell].prey = new Prey(*defaultPrey);
      }
    }
    else if (not worldAux[cell].prey) {
      worldAux[cell].prey = prey;
    }
    else {
      // il pierd asa ca ii transfer viata
      worldAux[cell].prey -> updateHealth(prey -> getHealth());
      -- preyCnt;
      delete prey;
    }
    
    prey = nullptr;
  }
}

void Game::updatePredatorState() {

  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell) {

    if (not world[cell].predator) continue;

    Predator *&predator = world[cell].predator;
    predator -> updateHealth();

    if (not predator -> isAlive()) {
      delete predator;
      -- predatorCnt;
      predator = nullptr;
      continue;
    }

    int newPos = get1DPos(constrain(get2DPos(cell) + Vec2D::getRandomWay()));
    for (int i = 0; i < NEW_POS_TRIES_THRESHOLD and worldAux[newPos].predator; ++ i) {
      newPos = get1DPos(constrain(get2DPos(cell) + Vec2D::getRandomWay()));
    }

    if (not worldAux[newPos].predator) {

      worldAux[newPos].predator = predator;
      if (worldAux[newPos].prey) {

        -- preyCnt;
        predator -> updateHealth(worldAux[newPos].prey -> getHealth());

        delete worldAux[newPos].prey;
        worldAux[newPos].prey = nullptr;

        if (not worldAux[cell].predator) {
          ++ predatorCnt;
          worldAux[cell].predator = new Predator(*defaultPredator);
        }
      }
    }
    else if (not worldAux[cell].predator) {
      worldAux[cell].predator = predator;
      if (worldAux[cell].prey) {
        -- preyCnt;
        predator -> updateHealth(worldAux[cell].prey -> getHealth());
        delete worldAux[cell].prey;
        worldAux[cell].prey = nullptr;
      }
    }
    else {
      // il pierd, deci fac transfer de viata
      -- predatorCnt;
      worldAux[cell].predator -> updateHealth(predator -> getHealth());
      delete predator;
    }
    // clear for next frame
    predator = nullptr;
  }
}

void Game::updateState() {

  updatePreyState();
  updatePredatorState();

  std::swap(world, worldAux);
}

void Game::colorPixel(int &i, int &j, const sf::Color &color) {
  pixels[(i << 1) * (WIDTH << 1) + (j << 1)].color = color;
  pixels[(i << 1) * (WIDTH << 1) + (j << 1 | 1)].color = color;
  pixels[(i << 1 | 1) * (WIDTH << 1) + (j << 1)].color = color;
  pixels[(i << 1 | 1) * (WIDTH << 1) + (j << 1 | 1)].color = color;
}

void Game::display() {

  for (int i = 0; i < HEIGHT; ++ i) {
    for (int j = 0; j < WIDTH; ++ j) {
      
      const auto prey = world[get1DPos(i, j)].prey;
      const auto predator = world[get1DPos(i, j)].predator;

      if ((prey or predator) == false) {
        colorPixel(i, j, CLEAR);
        continue;
      }

      if (prey) {
        if(prey -> isIll()) colorPixel(i, j, ORANGE);
        else colorPixel(i, j, GREEN);
      }
      else {
        if (predator -> isIll()) colorPixel(i, j, PURPLE);
        else colorPixel(i, j, RED);
      }
    }
  }

  window.draw(pixels, WIDTH * HEIGHT << 2, sf::Points);
  window.display();
}

void Game::run() {

  auto startTime = std::chrono::high_resolution_clock::now();

  while (window.isOpen()) {

    if (not endGame) {

      auto currentTime = std::chrono::high_resolution_clock::now();
      auto diff = std::chrono::duration_cast < std::chrono::seconds > (currentTime - startTime);

      if (diff.count() > END_GAME_THRESHOLD){
        defaultPrey -> makeIll();
        defaultPredator -> makeIll();
        endGame = true;
      }
    }

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    updateState();
    display();

    if (predatorCnt + preyCnt == 0) window.close();
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

// ====================================== Cleanup / init ====

Game::~Game() {
  delete defaultPrey;
  delete defaultPredator;
  delete[] world;
  delete[] worldAux;
  delete[] pixels;
}

Game::Cell::Cell() {
  prey = nullptr;
  predator = nullptr;
}

Game::Cell::~Cell() {
  delete prey;
  delete predator;
}
