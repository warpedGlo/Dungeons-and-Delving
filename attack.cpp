#include "Attack.h"

Attack::Attack()
{
  attack_name = "Unarmed Strike";
  damage_type = "Bludgeon";
  damage = 4;
  meleRange = true;
  
}

Attack::Attack(std::string new_attack_name, std::string new_damage_type, int new_damage, bool new_meleRange)
{
  attack_name = new_attack_name;
  damage_type = new_damage_type;
  damage = new_damage;
  meleRange = new_meleRange;
}

// getters
std::string Attack::getName()
{
  return attack_name;
}
std::string Attack::getDamageType()
{
  return damage_type;
}
int Attack::getDamage()
{
  return damage;
}
bool Attack::isMeleRange()
{
  return meleRange;
}
int Attack::rollHit()
{
  int roll = (rand() % 20) + 1;
    return  roll;
}
int Attack::rollDamage()
{
  return rand() % damage + 1;
}

// setters
void Attack::setName(std::string new_name)
{
  attack_name = new_name;
}
void Attack::setDamageType(std::string new_type)
{
  damage_type = new_type;
}
void Attack::setDamage(int new_damage)
{
  damage = new_damage;
}
void Attack::setIsMeleRange(bool true_or_false)
{
  meleRange = true_or_false;
}
