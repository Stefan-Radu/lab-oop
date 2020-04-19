#include "Vec2D.hpp"

Vec2D::Vec2D(): i(0), j(0) {}
Vec2D::Vec2D(int i, int j): i(i), j(j) {}
Vec2D::Vec2D(const Vec2D &v): i(v.i), j(v.j) {}

Vec2D& Vec2D::operator = (const Vec2D &other) {
  this->i = other.i;
  this->j = other.j;
  return *this;
}

Vec2D Vec2D::operator + (const Vec2D &other) const {
  return Vec2D(this->i + other.i, this->j + other.j);
}

void Vec2D::operator += (const Vec2D &other) {
  this->i += other.i;
  this->j += other.j;
}

Vec2D Vec2D::getRandomWay() {
  int chance = rand() % 4;
  return Vec2D(dirI[chance], dirJ[chance]);
}

std::ostream& operator << (std::ostream &os, const Vec2D &v) {
  os << v.i << ' ' << v.j;
  return os;
}
