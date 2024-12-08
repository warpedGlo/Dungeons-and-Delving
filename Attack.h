#ifndef ATTACK_H
#define ATTACK_H

#include <string>

class Attack
{
 public:
  //constructor
  Attack();
  Attack(std::string new_attackName, std::string new_damage_type, int new_damage, bool new_meleRange);
  // getters
  std::string getName();
  std::string getDamageType();
  int getDamage();
  bool isMeleRange();
  int rollHit();
  int rollDamage();
  
  // setters
  void setName(std::string new_name);
  void setDamageType(std::string new_type);
  void setDamage(int new_damage);
  void setIsMeleRange(bool true_or_false);

  // use attack function
  void useAttack();

  // display stats
  void displayStats();
  
 private:
  std::string attack_name;
  std::string damage_type;
  int damage;
  bool meleRange;
};

#endif
