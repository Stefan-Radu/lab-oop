#pragma once

#include <iostream>

int mutate(int k);

enum class CreatureType { PREDATOR, PREY, NOTHING };

class Creature {
public:

  Creature(int, bool, int, int);
  virtual ~Creature() = 0;

  void updateHealth(int);
  virtual void updateHealth() = 0;

  bool isDead() const; 
  bool isIll() const;
  void makeIll();
  virtual void resetHealth() = 0;
  int getHealth() const;

protected:
  int health;
  bool ill;
  const int MAX_HEALTH;
  const int HEALTH_TIC;
};

class Prey: public Creature {
public:

  Prey(int, int);
  Prey(const Prey&);

  bool canReproduce() const;
  void updateHealth() override;
  void resetHealth() override;
};

class Predator: public Creature {
public:

  Predator(int, int);
  Predator(const Predator&);

  void updateHealth() override;
  void resetHealth() override;
};
