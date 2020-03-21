#pragma once

#include <iostream>

class Creature {
public:

  Creature(int);
  virtual ~Creature() = 0;

  virtual void updateHealth() = 0;
  virtual void updateHealth(int) = 0;

  bool isAlive() const; 
  int getHealth() const;
  virtual bool canReproduce() const = 0;

protected:
  int health;
};

class Prey: public Creature {
public:

  Prey();
  Prey(const Prey&);
  Prey& operator = (const Prey&);

  bool canReproduce() const override;
  void updateHealth() override;
  void updateHealth(int) override;
  void resetHealth();

private:

  static const int MAX_HEALTH = 50;
  static const int HEALTH_TIC = 7;
};

class Predator: public Creature {
public:

  Predator();
  Predator(int);
  Predator(const Predator&);
  Predator& operator = (const Predator&);

  bool canReproduce() const override;
  void updateHealth() override;
  void updateHealth(int) override;
  int getExtraHealth();

private:

  static const int MAX_HEALTH = 30;
  static const int HEALTH_TIC = 3;
};
