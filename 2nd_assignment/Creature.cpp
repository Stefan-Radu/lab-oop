#include "Creature.hpp"

int mutate(int k) {
  return std::max(k + rand() % 3 - 1, 1);
}

//==================================================  Creature  ==================================================

Creature::Creature(int h, bool i, int mh, int ht):
  health(h), ill(i), MAX_HEALTH(mh), HEALTH_TIC(mutate(ht)) {}  

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

void Creature::updateHealth(int toAdd) {
  health += toAdd;
  if (health > MAX_HEALTH) health = MAX_HEALTH;
}

//==================================================  Prey  ==================================================

Prey::Prey(int mh, int ht):
  Creature(1, false, mh, ht) {}

Prey::Prey(const Prey& prey):
  Creature(prey.health, prey.ill, prey.MAX_HEALTH, prey.HEALTH_TIC) {}

void Prey::updateHealth() {
  health += (-2 * (int)ill + 1) * HEALTH_TIC;
  if (health > MAX_HEALTH) health = MAX_HEALTH;
}

bool Prey::canReproduce() const {
  return health >= MAX_HEALTH;
}

void Prey::resetHealth() {
  health = 1;
}

//==================================================  Predator  ==================================================

Predator::Predator(int mh, int ht):
  Creature(mh, false, mh, ht) {}

Predator::Predator(const Predator& predator):
  Creature(predator.health, predator.ill, predator.MAX_HEALTH, predator.HEALTH_TIC) {}

void Predator::updateHealth() {
  health -= HEALTH_TIC << (int)ill;
}
