#pragma once

#include <iostream>

struct Vec2D {

  Vec2D();
  Vec2D(int, int);
  Vec2D(const Vec2D&);

  int x, y;

  void operator = (const Vec2D&);
  static Vec2D generateRAndomVec2D();
};

std::ostream& operator << (std::ostream&, Vec2D&);

class Creature {
public:

  Creature(int, Vec2D);

  virtual void updateHealth() = 0;
  bool isAlive() const; 

  void updatePosition();

protected:
  int health;
  Vec2D position;
};

class Prey: public Creature {
public:

  Prey();
  Prey(Vec2D);

  void updateHealth();

private:

  static const int MAX_HEALTH = 100;
  static const int HEALTH_TIC = 1;
};

class Predator: public Creature {
public:

  Predator();
  Predator(Vec2D);

  void updateHealth();

private:

  static const int MAX_HEALTH = 100;
  static const int HEALTH_TIC = 1;
};

