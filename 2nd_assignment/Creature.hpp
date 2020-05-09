#pragma once

#include <iostream>

int mutate(int k);

enum class CreatureType { PREDATOR, PREY, NOTHING };

class Creature {
public:

  Creature(int, bool, int, int);
  virtual ~Creature();

  static int getCount();

  void updateHealth(int);
  void makeIll();
  int getHealth() const;
  bool isDead() const; 
  bool isIll() const;
  bool canReproduce() const;

  virtual void updateHealth() = 0;
  virtual void resetHealth() = 0;

protected:

  int health;
  bool ill;
  const int MAX_HEALTH;
  const int HEALTH_TIC;

  friend std::ostream& operator << (std::ostream&, Creature&);

private:
  static int howMany;
};

class Prey: public Creature {
public:

  Prey(int, int);
  Prey(const Prey&);

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
