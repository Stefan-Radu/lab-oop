#include "Game.hpp"
#include <chrono>
#include <thread>

//==================================================  Initialization  ==================================================

const sf::Color Game::GREEN(180, 255, 14, 50);
const sf::Color Game::RED(217, 31, 39, 50);
const sf::Color Game::PURPLE(201, 0, 184, 50);
const sf::Color Game::ORANGE(201, 154, 0, 50);
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
      world[cell].type = CreatureType::PREY;
      world[cell].creature = new Prey(*defaultPrey);
    }
    else if (chance < PREY_PERCENTAGE + PREDATOR_PERCENTAGE) {
      ++ predatorCnt;
      world[cell].type = CreatureType::PREDATOR;
      world[cell].creature = new Predator(*defaultPredator);
    }
  }
}

//==================================================  Game Logic  ==================================================

void Game::updatePreyState() {

  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell) {

    if (world[cell].type != CreatureType::PREY) continue;

    Prey *prey = static_cast < Prey* > (world[cell].creature);

    prey->updateHealth();

    if (not prey->isAlive()) {
      delete prey;
      -- preyCnt;
      world[cell].type = CreatureType::NOTHING;
      world[cell].creature = nullptr;
      continue;
    }

    if (endGame and rand() % CHANCE_MODULO < ILLNESS_CHANCE) prey->makeIll();

    int newPos = get1DPos(wrap(get2DPos(cell) + Vec2D::getRandomWay()));

    for (int i = 0; i < NEW_POS_TRIES_THRESHOLD and worldAux[newPos].type == CreatureType::PREY; ++ i) {
      newPos = get1DPos(wrap(get2DPos(cell) + Vec2D::getRandomWay()));
    }

    if (worldAux[newPos].type != CreatureType::PREY) {
      if (worldAux[cell].type == CreatureType::NOTHING and prey->canReproduce()) {
        prey->resetHealth();
        ++ preyCnt;
        worldAux[cell].type = CreatureType::PREY;
        worldAux[cell].creature = new Prey(*defaultPrey);
      }
      worldAux[newPos].type = CreatureType::PREY;
      worldAux[newPos].creature = prey;
    }
    else {
      // life transfer
      -- preyCnt;
      worldAux[newPos].creature->updateHealth(prey->getHealth());
      delete prey;
    }

    // clear for next frame
    world[cell].type = CreatureType::NOTHING;
    world[cell].creature = nullptr;
  }
}

void Game::updatePredatorState() {

  for (int cell = 0; cell < WIDTH * HEIGHT; ++ cell) {

    if (world[cell].type != CreatureType::PREDATOR) continue;

    Predator *predator = static_cast < Predator* > (world[cell].creature);
    predator->updateHealth();

    if (not predator->isAlive()) {
      delete predator;
      -- predatorCnt;
      world[cell].type = CreatureType::NOTHING;
      world[cell].creature = nullptr;
      continue;
    }

    int newPos = get1DPos(wrap(get2DPos(cell) + Vec2D::getRandomWay()));
    for (int i = 0; i < NEW_POS_TRIES_THRESHOLD and worldAux[newPos].type == CreatureType::PREDATOR; ++ i) {
      newPos = get1DPos(wrap(get2DPos(cell) + Vec2D::getRandomWay()));
    }

    if (worldAux[newPos].type != CreatureType::PREDATOR) {

      if (worldAux[newPos].type == CreatureType::PREY) {

        -- preyCnt;
        predator->Creature::updateHealth(worldAux[newPos].creature->getHealth());

        delete worldAux[newPos].creature;

        if (worldAux[cell].type == CreatureType::NOTHING) {
          ++ predatorCnt;
          worldAux[cell].type = CreatureType::PREDATOR;
          worldAux[cell].creature = new Predator(*defaultPredator);
        }
      } 

      worldAux[newPos].type = CreatureType::PREDATOR;
      worldAux[newPos].creature = predator;
    }
    else {
      // life transfer
      -- predatorCnt;
      worldAux[newPos].creature->updateHealth(predator->getHealth());
      delete predator;
    }

    // clear for next frame
    
    world[cell].type = CreatureType::NOTHING;
    world[cell].creature = nullptr;
  }
}

//==================================================  Functionality  ==================================================

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
      
      const Cell &cell = world[get1DPos(i, j)];

      if (cell.type == CreatureType::NOTHING) {
        colorPixel(i, j, CLEAR);
      }
      else if (cell.type == CreatureType::PREY) {
        if(cell.creature->isIll()) colorPixel(i, j, ORANGE);
        else colorPixel(i, j, GREEN);
      }
      else {
        if (cell.creature->isIll()) colorPixel(i, j, PURPLE);
        else colorPixel(i, j, RED);
      }
    }
  }

  window.draw(pixels, WIDTH * HEIGHT << 2, sf::Points);
  window.display();
}

void Game::run() {

  window.clear();
  window.display();
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

  auto startTime = std::chrono::high_resolution_clock::now();

  while (window.isOpen()) {

    if (not endGame) {

      auto currentTime = std::chrono::high_resolution_clock::now();
      auto diff = std::chrono::duration_cast < std::chrono::seconds > (currentTime - startTime);

      if (diff.count() > END_GAME_THRESHOLD){
        defaultPrey->makeIll();
        defaultPredator->makeIll();
        endGame = true;
      }
    }

    if (predatorCnt + preyCnt == 0) {
      -- preyCnt;
      startTime = std::chrono::high_resolution_clock::now();
    }

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    updateState();
    display();

    if (preyCnt == -1) {
      auto currentTime = std::chrono::high_resolution_clock::now();
      auto diff = std::chrono::duration_cast < std::chrono::seconds > (currentTime - startTime);
      if (diff.count() > NO_CREATURES_THRESOLD) {
        window.close();
      }
    }
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

Vec2D Game::wrap(Vec2D pos) {
  if (pos.i < 0) pos.i = HEIGHT - 1;
  else if (pos.i >= HEIGHT) pos.i = 0;
  if (pos.j < 0) pos.j = WIDTH - 1;
  else if (pos.j >= WIDTH) pos.j = 0;
  return pos;
}

Game::Cell::Cell() {
  type = CreatureType::NOTHING;
  creature = nullptr;
}

Game::~Game() {
  delete defaultPrey;
  delete defaultPredator;
  delete[] world;
  delete[] worldAux;
  delete[] pixels;
}

Game::Cell::~Cell() {
  delete creature;
}
