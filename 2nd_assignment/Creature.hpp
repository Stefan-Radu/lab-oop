#pragma once

#include <iostream>

static int mutate(int k);

class Creature {
public:

  Creature();
  Creature(int);
  virtual ~Creature() = 0;

  virtual void updateHealth() = 0;

  bool isAlive() const; 
  int getHealth() const;

protected:
  int health;
};

class Prey: public Creature {
public:

  Prey(int mh = 10, int ht = 1);
  Prey(const Prey&);

  bool canReproduce() const;
  void updateHealth() override;
  void updateHealth(int);
  void resetHealth();

private:

  const int MAX_HEALTH;
  const int HEALTH_TIC;
};

class Predator: public Creature {
public:

  Predator(int mh = 10, int ht = 1);
  Predator(const Predator&);

  void updateHealth() override;
  void updateHealth(int);

private:

  const int MAX_HEALTH;
  const int HEALTH_TIC;
};
