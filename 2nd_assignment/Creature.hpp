#pragma once

#include <iostream>

struct Vec2D {

  Vec2D();
  Vec2D(int, int);
  Vec2D(const Vec2D&);
  Vec2D& operator = (const Vec2D&);

  int x, y;

  static Vec2D generateRandomVec2D(); // for moving a creature 1 step up / down/ left / right
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
  Prey(const Prey&);
  Prey& operator = (const Prey&);

  void updateHealth() override;

private:

  static const int MAX_HEALTH = 100;
  static const int HEALTH_TIC = 1;
};

class Predator: public Creature {
public:

  Predator();
  Predator(Vec2D);
  Predator(const Predator&);
  Predator& operator = (const Predator&);

  void updateHealth() override;

private:

  static const int MAX_HEALTH = 100;
  static const int HEALTH_TIC = 1;
};
