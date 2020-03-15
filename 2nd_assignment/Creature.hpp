#pragma once

#include <iostream>

struct Vec2D {
  Vec2D();
  Vec2D(int, int);
  int x, y;
  void operator = (const Vec2D&);
};

std::ostream& operator << (std::ostream&, Vec2D&);

class Creature {
public:

  Creature();

private:




};


