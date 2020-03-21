#include "Creature.hpp"

//==================================================  Creature  ==================================================

Creature::Creature(int h): health(h) {}  
Creature::~Creature() {}

bool Creature::isAlive() const {
  return health > 0;
}

int Creature::getHealth() const {
  return health;
}

//==================================================  Prey  ==================================================

Prey::Prey(): Creature(1) {}
Prey::Prey(const Prey& prey): Creature(prey.health) {}

Prey& Prey:: operator = (const Prey &other) {
  health = other.health;
  return *this;
}

void Prey::updateHealth() {
  health = std::min(health + HEALTH_TIC, (int) MAX_HEALTH);
}

void Prey::updateHealth(int toAdd) {
  health += toAdd;
}

bool Prey::canReproduce() const {
  return health >= MAX_HEALTH;
}

void Prey::resetHealth() {
  health = 1;
}

//==================================================  Predator  ==================================================

Predator::Predator(): Creature(MAX_HEALTH) {}
Predator::Predator(int h): Creature(std::min(h, (int) MAX_HEALTH)) {}
Predator::Predator(const Predator& predator): Creature(predator.health) {}

Predator& Predator:: operator = (const Predator &other) {
  health = other.health;
  return *this;
}

void Predator::updateHealth() {
  health -= HEALTH_TIC;
}

void Predator::updateHealth(int toAdd) {
  health += toAdd;
}

int Predator::getExtraHealth() {
  if (health >= MAX_HEALTH) {
    int ret = health - MAX_HEALTH + 1;
    health = MAX_HEALTH;
    return ret;
  }
  return 0;
}

bool Predator::canReproduce() const {
  return health >= MAX_HEALTH;
}
