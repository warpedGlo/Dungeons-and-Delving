#include "Ability.h"

Ability::Ability()
{
  name = "Unknown Ability";
  type = "Unknown Type";
  damage = 0;
  healing = 0;
  bonus = 0;
  manaCost = 0;
  staminaCost = 0;
}

Ability::Ability(std::string newName, std::string newType, int newDamage, int newHealing, int newBonus, int newManaCost, int newStaminaCost)
{
  name = newName;
  type = newType;
  damage = newDamage;
  healing = newHealing;
  bonus = newBonus;
  manaCost = newManaCost;
  staminaCost = newManaCost;
}


// Getters
std::string Ability::getName()
{
  return name;
}
std::string Ability::getType()
{
  return type;
}
int Ability::getDamage()
{
  return damage;
}
int Ability::getHealing()
{
  return healing;
}
int Ability::getManaCost()
{
  return manaCost;
}
int Ability::getStaminaCost()
{
  return staminaCost;
}

// use ability
int Ability::rollAbility()
{
  if (type == "healing")
    {
      return ((rand() % healing) + 1) + bonus;
    }
  if (type == "damage")
    {
      return ((rand() % damage) + 1) + bonus;
    }
  // if (type == "healing/damage" future idea)
  return 0;
}
