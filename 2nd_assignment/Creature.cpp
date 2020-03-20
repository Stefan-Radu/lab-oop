#include "Creature.hpp"

//==================================================  Creature  ==================================================

Creature::Creature(int h): health(h) {}  

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

bool Prey::canReproduce() const {
  return health >= MAX_HEALTH;
}

void Prey::resetHealth() {
  health = 1;
}

//==================================================  Predator  ==================================================

Predator::Predator(): Creature(MAX_HEALTH) {}
Predator::Predator(const Predator& predator): Creature(predator.health) {}

Predator& Predator:: operator = (const Predator &other) {
  health = other.health;
  return *this;
}

void Predator::updateHealth() {
  health = std::max(0, health - (int) HEALTH_TIC);
}

void Predator::updateHealth(int toAdd) {
  health = std::max(health + toAdd, (int) MAX_HEALTH);
}

bool Predator::canReproduce() const {
  return health >= MAX_HEALTH;
}
