#include "Creature.hpp"

//==================================================  Vec2D  ==================================================
Vec2D::Vec2D(): i(0), j(0) {}
Vec2D::Vec2D(int i, int j): i(i), j(j) {}
Vec2D::Vec2D(const Vec2D &v): i(v.i), j(v.j) {}

Vec2D& Vec2D::operator = (const Vec2D &other) {
  this -> i = other.i;
  this -> j = other.j;
  return *this;
}

Vec2D Vec2D::operator + (const Vec2D &other) const {
  return Vec2D(this -> i + other.i, this -> j + other.j);
}

void Vec2D::operator += (const Vec2D &other) {
  this -> i += other.i;
  this -> j += other.j;
}

Vec2D Vec2D::getRandomVec2D() {
  auto aux = Vec2D(rand() % 3 - 1, rand() % 3 - 1);
  return aux;
}

std::ostream& operator << (std::ostream &os, const Vec2D &v) {
  os << v.i << ' ' << v.j;
  return os;
}

//==================================================  Creature  ==================================================

Creature::Creature(int h, Vec2D pos): health(h), position(pos) {}  

bool Creature::isAlive() const {
  return health != 0;
}

int Creature::getHealth() const {
  return health;
}

Vec2D Creature::getPosition() const {
  return position;
}

void Creature::updatePosition(const int &limitH, const int &limitW) {
  position += Vec2D::getRandomVec2D();
  if (position.i < 0) position.i = limitH - 1;
  else if (position.i == limitH) position.i = 0;
  if (position.j < 0) position.j = limitW - 1;
  else if (position.j == limitW) position.j = 0;
}

//==================================================  Prey  ==================================================

Prey::Prey(): Creature(1, Vec2D()) {}
Prey::Prey(Vec2D pos): Creature(1, pos) {}
Prey::Prey(const Prey& prey): Creature(prey.health, prey.position) {}

Prey& Prey:: operator = (const Prey &other) {
  health = other.health;
  position = other.position;
  return *this;
}

void Prey::updateHealth() {
  health = std::min(health + HEALTH_TIC, (int) MAX_HEALTH);
}

bool Prey::canReproduce() const {
  return health == MAX_HEALTH;
}

void Prey::resetHealth() {
  health = 1;
}

//==================================================  Predator  ==================================================

Predator::Predator(): Creature(MAX_HEALTH, Vec2D()) {}
Predator::Predator(Vec2D pos): Creature(MAX_HEALTH, pos) {}
Predator::Predator(const Predator& predator): Creature(predator.health, predator.position) {}

Predator& Predator:: operator = (const Predator &other) {
  health = other.health;
  position = other.position;
  return *this;
}

void Predator::updateHealth() {
  health -= HEALTH_TIC;
}

void Predator::updateHealth(int toAdd) {
  health = std::max(health + toAdd, (int) MAX_HEALTH);
}

bool Predator::canReproduce() const {
  return health == MAX_HEALTH;
}
