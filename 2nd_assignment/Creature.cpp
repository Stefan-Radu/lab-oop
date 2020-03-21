#include "Creature.hpp"

int mutate(int k) {
  return k + rand() % 3 + 1;
}

//==================================================  Creature  ==================================================

Creature::Creature(int h, bool i): health(h), ill(i) {}  
Creature::~Creature() {}

bool Creature::isAlive() const {
  return health > 0;
}

bool Creature::isIll() const {
  return ill;
}

void Creature::makeIll() {
  ill = true;
}

int Creature::getHealth() const {
  return health;
}

//==================================================  Prey  ==================================================

Prey::Prey(int mh, int ht):
  Creature(1, false), MAX_HEALTH(mh), HEALTH_TIC(mutate(ht)) {}
Prey::Prey(const Prey& prey):
  Creature(prey.health, prey.ill), MAX_HEALTH(prey.MAX_HEALTH), HEALTH_TIC(mutate(prey.HEALTH_TIC)) {}

void Prey::updateHealth() {
  if (ill) health = health -= HEALTH_TIC;
  else health = std::min(health + HEALTH_TIC, (int) MAX_HEALTH);
}

void Prey::updateHealth(int toAdd) {
  health = std::min(health + toAdd, (int) MAX_HEALTH);
}

bool Prey::canReproduce() const {
  return health >= MAX_HEALTH;
}

void Prey::resetHealth() {
  health = 1;
}

//==================================================  Predator  ==================================================

Predator::Predator(int mh, int ht):
  Creature(mh, false), MAX_HEALTH(mh), HEALTH_TIC(ht) {}
Predator::Predator(const Predator& predator):
  Creature(predator.health, predator.ill), MAX_HEALTH(predator.MAX_HEALTH), HEALTH_TIC(predator.HEALTH_TIC) {}

void Predator::updateHealth() {
  if (ill) health -= 3 * HEALTH_TIC;
  else health -= HEALTH_TIC;
}

void Predator::updateHealth(int toAdd) {
  health = std::min(health + toAdd, (int) MAX_HEALTH);
}
