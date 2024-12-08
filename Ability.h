#ifndef ABILITY_H
#define ABILITY_H

#include <string>

class Ability
{
 public:
  Ability();
  Ability(std::string newName, std::string newType, int newDamage, int newHealing, int newBonus, int newManaCost, int newStaminaCost);

  // Getters
  std::string getName();
  std::string getType();
  int getDamage();
  int getHealing();
  int getManaCost();
  int getStaminaCost();

  // use ability
  int rollAbility();
  
 private:
  std::string name;
  std::string type; // damage, healing, utility
  int damage; // if destructive
  int healing; // if restorative
  int bonus; //guaranteed damage/health
  int manaCost; // if magical
  int staminaCost; // if non magical
  std::string description;
};

#endif
