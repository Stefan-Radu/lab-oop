#pragma once

#include <ostream>

struct Vec2D {

  Vec2D();
  Vec2D(int, int);
  Vec2D(const Vec2D&);

  Vec2D& operator = (const Vec2D&);
  Vec2D operator + (const Vec2D&) const;
  void operator += (const Vec2D&);

  int i, j;

  static Vec2D getRandomVec2D(); // for moving a creature 1 step up / down/ left / right
};

std::ostream& operator << (std::ostream&, const Vec2D&);
