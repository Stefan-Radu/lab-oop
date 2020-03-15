#include "Creature.hpp"

Vec2D::Vec2D(): x(0), y(0) {}
Vec2D::Vec2D(int x, int y): x(x), y(y) {}

void Vec2D::operator = (const Vec2D &other) {
  this -> x = other.x;
  this -> y = other.y;
}

std::ostream& operator << (std::ostream &os, Vec2D &v) {
  os << v.x << ' ' << v.y;
  return os;
}
