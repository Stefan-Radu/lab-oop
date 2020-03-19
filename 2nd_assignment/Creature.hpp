#pragma once

#include <iostream>

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

class Creature {
public:

  Creature(int, Vec2D);

  virtual void updateHealth() = 0;

  bool isAlive() const; 
  int getHealth() const;
  virtual bool canReproduce() const = 0;

  Vec2D getPosition() const;
  void updatePosition(const int&, const int&);

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

  bool canReproduce() const override;
  void updateHealth() override;
  void resetHealth();

private:

  static const int MAX_HEALTH = 2;
  static const int HEALTH_TIC = 1;
};

class Predator: public Creature {
public:

  Predator();
  Predator(Vec2D);
  Predator(const Predator&);
  Predator& operator = (const Predator&);

  bool canReproduce() const override;
  void updateHealth() override;
  void updateHealth(int);

private:

  static const int MAX_HEALTH = 2;
  static const int HEALTH_TIC = 1;
};
