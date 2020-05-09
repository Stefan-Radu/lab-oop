#include "Creature.hpp"

int mutate(int k) {
  return std::max(k + rand() % 3 - 1, 1);
}

//==================================================  Creature  ==================================================

int Creature::howMany = 0;

Creature::Creature(int health, bool ill, int maxHealth, int healthTick):
  health(health), ill(ill), MAX_HEALTH(maxHealth), HEALTH_TIC(mutate(healthTick)) {
  ++ howMany;
}  

int Creature::getCount() {
  return Creature::howMany - 2;
}

bool Creature::isDead() const {
  return health <= 0;
}

bool Creature::isIll() const {
  return ill;
}

bool Creature::canReproduce() const {
  return health >= MAX_HEALTH;
}

void Creature::makeIll() {
  ill = true;
}

int Creature::getHealth() const {
  return health;
}

void Creature::updateHealth(int toAdd) {
  health += toAdd;
  if (health > MAX_HEALTH) {
    health = MAX_HEALTH;
  }
}

Creature::~Creature() {
  -- howMany;
}

std::ostream& operator << (std::ostream &os, Creature &c) {
  os << "Maximum health: " << c.MAX_HEALTH <<  '\n';
  os << "Health tic: " << c.HEALTH_TIC <<  '\n';
  return os;
}

//==================================================  Prey  ==================================================

Prey::Prey(int maxHealth, int healthTick):
  Creature(1, false, maxHealth, healthTick) {}

Prey::Prey(const Prey& prey):
  Creature(prey.health, prey.ill, prey.MAX_HEALTH, prey.HEALTH_TIC) {}

void Prey::updateHealth() {
  health += (-2 * (int)ill + 1) * HEALTH_TIC;
  if (health > MAX_HEALTH) {
    health = MAX_HEALTH;
  }
}

void Prey::resetHealth() {
  health = 1;
}

//==================================================  Predator  ==================================================

Predator::Predator(int maxHealth, int healthTick):
  Creature(maxHealth, false, maxHealth, healthTick) {}

Predator::Predator(const Predator& predator):
  Creature(predator.health, predator.ill, predator.MAX_HEALTH, predator.HEALTH_TIC) {}

void Predator::updateHealth() {
  health -= HEALTH_TIC;
}

void Predator::resetHealth() {
  health = MAX_HEALTH;
}
