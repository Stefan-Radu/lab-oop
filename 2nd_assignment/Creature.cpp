#include "Creature.hpp"

//==================================================  Vec2D  ==================================================
Vec2D::Vec2D(): x(0), y(0) {}
Vec2D::Vec2D(int x, int y): x(x), y(y) {}
Vec2D::Vec2D(const Vec2D &v): x(v.x), y(v.y) {}

void Vec2D::operator = (const Vec2D &other) {
  this -> x = other.x;
  this -> y = other.y;
}

Vec2D Vec2D::generateRAndomVec2D() {
  return Vec2D(rand() % 3 - 1, rand() % 3 - 1);
}

std::ostream& operator << (std::ostream &os, Vec2D &v) {
  os << v.x << ' ' << v.y;
  return os;
}

//==================================================  Creature  ==================================================

Creature::Creature(int h, Vec2D pos): health(h), position(pos) {}  

bool Creature::isAlive() const {
  return health != 0;
}

//==================================================  Prey  ==================================================

Prey::Prey(): Creature(1, Vec2D()) {}
Prey::Prey(Vec2D pos): Creature(1, pos) {}

void Prey::updateHealth() {
  health += HEALTH_TIC;
}

//==================================================  Predator  ==================================================

Predator::Predator(): Creature(MAX_HEALTH, Vec2D()) {}
Predator::Predator(Vec2D pos): Creature(MAX_HEALTH, pos) {}

void Predator::updateHealth() {
  health -= HEALTH_TIC;
}
