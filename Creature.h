#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>
#include "Attack.h"
#include "Ability.h"
#include "Potion.h"

class Creature
{
 public:
  Creature(); //default constructor
  Creature(std::string new_name, int newControlType, int new_health, int new_mana, int new_stamina, int newArmorClass, int new_speed, std::initializer_list<Attack> attackList, std::initializer_list<Ability> abilityList, std::initializer_list<Potion> potionList); //overloaded constructor

  // info
  std::string get_name();
  void set_name();
  
  // health
  void take_damage(int damage_taken);
  int get_current_health();
  void set_current_health(int new_current_health);
  void set_max_health(int new_health);
  void heal(int health_gained);
  bool isAlive();
  
  // mana
  void drain_mana(int mana_drained);
  int get_current_mana();
  void set_max_mana(int new_mana);
  void mana_regen(int mana_gained);

  // stamina
  void drain_stamina(int stamina_drained);
  int get_current_stamina();
  void set_max_stamina(int new_stamina);
  void stamina_regen(int stamina_gained);

  // armor class
  int getAC();
  
  // speed
  int get_speed();
  void set_speed(int new_speed);
  
  // player take turn
  void take_turn(Creature &defender);
  bool isPlayer();
  void playerPrintStats();
  void playerPrintInventory();
  int playerAction(Creature &defender);
  int playerAttack(int selected_action);
  int playerAbility(int selected_action);
  int playerItem(int selected_action);
  void playerRun(int selected_action);
  Creature* playerTarget(Creature &defender);
  
  // AI take turn
  int AIaction();
  int AIattack(int selected_action);
  Creature* AItarget(Creature &defender);

  // resolutions
  int rolld20();
  void attackResolution(Creature *defender, int selected_action);
  void abilityResolution(Creature *defender, int selected_action);
  void itemResolution(Creature *drinker, int selected_action);
  
  // inventory

  // getters
  // use vector functions  

  // adders
  void addAttack(Attack& attackList);
  void addPotion(Potion& potionList);

  // removers
  void removeAttack();
  void removePotion();
  
 private:
  std::string name;
  int AIcontrolType;
  
  int max_health;
  int current_health;
  int max_mana;
  int current_mana;
  int max_stamina;
  int current_stamina;
  int armor_class;
  int speed;

  // inventory
  std::vector<Attack> attacks;
  std::vector<Ability> abilities;
  std::vector<Potion> potions;
};

#endif
