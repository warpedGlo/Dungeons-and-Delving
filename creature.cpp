#include <iostream>
#include <iomanip>
#include "Creature.h"
#include <algorithm>


Creature::Creature()
{
  name = "Unspeakable Horror";
  AIcontrolType = 0;
  max_health = 100;
  max_mana = 100;
  max_stamina = 100;
  armor_class = 10;
  speed = 30;

  attacks = {};
  abilities = {};
  potions = {};
}
Creature::Creature(std::string new_name, int newControlType, int new_health, int new_mana, int new_stamina, int newArmorClass, int new_speed, std::initializer_list<Attack> attackList, std::initializer_list<Ability> abilityList, std::initializer_list<Potion> potionList)
{
  name = new_name;
  AIcontrolType = newControlType;
  max_health = new_health;
  current_health = new_health;
  max_mana = new_mana;
  current_mana = new_mana;
  max_stamina = new_stamina;
  current_stamina = new_stamina;
  armor_class = newArmorClass;
  speed = new_speed;

  attacks = attackList;
  abilities = abilityList;
  potions = potionList;

}

// info
std::string Creature::get_name()
{
  return name;
}

// health
void Creature::take_damage(int damage_taken)
{
  current_health -= damage_taken;
}
int Creature::get_current_health()
{
  return current_health;
}
void Creature::set_current_health(int new_current_health)
{
  current_health = new_current_health;
}
void Creature::set_max_health(int new_health)
{
  max_health = new_health;
}
void Creature::heal(int health_gained)
{
  if(max_health < current_health + health_gained)
    {
      current_health = max_health;
    }
  else
    {
      current_health += health_gained;
    }
}
bool Creature::isAlive()
{
  return current_health > 0;
}

// mana
void Creature::drain_mana(int mana_drained)
{
  current_mana -= mana_drained;
}
int Creature::get_current_mana()
{
  return current_mana;
}
void Creature::set_max_mana(int new_mana)
{
 max_mana = new_mana;
}
void Creature::mana_regen (int mana_gained)
{
  if(max_mana < current_mana + mana_gained)
    {
      current_mana = max_mana;
    }
  else
    {
      current_mana += mana_gained;
    }
}

// stamina
void Creature::drain_stamina(int stamina_drained)
{
  current_stamina -= stamina_drained;
}
int Creature::get_current_stamina()
{
  return current_stamina;
}
void Creature::set_max_stamina(int new_stamina)
{
  max_stamina = new_stamina;
}
void Creature::stamina_regen(int stamina_gained)
{
  if(max_stamina < current_stamina + stamina_gained)
    {
      current_stamina = max_stamina;
    }
  else
    {
      current_stamina += stamina_gained;
    }
}

// armor class
int Creature::getAC()
{
  return armor_class;
}

// speed 
int Creature::get_speed()
{
  return speed;
}
void Creature::set_speed(int new_speed)
{
  speed = new_speed;
}

// player take turn
void Creature::take_turn(Creature &defender)
{
  if (get_current_health() > 0)
    {
      int select_action =  0;
      int select_attack = 0;
      int select_ability = 0;
      int select_item = -1; // default value for no item selected
      Creature* target = nullptr;
      
      if (AIcontrolType == 0) // players turn
	{
	  playerPrintStats();
	  playerPrintInventory();
	  
	  select_action = playerAction(defender);
	  select_attack = playerAttack(select_action); // player selects attack
	  select_ability = playerAbility(select_action);
	  select_item = playerItem(select_action);
	  target = playerTarget(defender); // player selects target
	  
	}
      
      else if (AIcontrolType != 0) // AIs turn
	{
	  select_action = AIaction(); 
	  select_attack = AIattack(select_action);
	  target = AItarget(defender);
	}

      // Perform the attack resolution (using selected attack)
      if (select_action == 1 && target != nullptr)  // If action is to attack
	{
	  attackResolution(target, select_attack);
	}
      if (select_action == 2 && target != nullptr)
	{
	  abilityResolution(target, select_ability);
	}
      // If the player selected an item (healing potion), resolve it
      if (select_item != -1)  // Only if a valid item is selected
	{
	  itemResolution(this, select_item);  // Resolve item usage (e.g., healing potion)
	}
    }
}

bool Creature::isPlayer()
{
  return AIcontrolType == 0;
}

void Creature::playerPrintStats()
{
      std::cout << "--------------------------------------------------" << std::endl
		<< get_name() << std::endl
		<< "HP:" << current_health << "/" << max_health
		<< "   " << "MP:" << current_mana << "/" << max_mana
		<< "   " <<"XP: 1" << std::endl;
      std::cout << "                          Armor: 11 AC" << std::endl
		<< "                           - chainmail (+1 AC)" << std::endl;
	

}
void Creature::playerPrintInventory()
{    
  // inventory headers
  std::cout << std::setw(26) << std::left << "Items: "
	    << std::setw(26) << std::left << "Attacks: " << std::endl;

  int linesNeeded = std::max(attacks.size(), potions.size());
   
  // item and attack list
  for (int i = 0; i <= linesNeeded; i++)
    {
      // items
      std::cout << std::setw(26) << std::left;
      if (i < potions.size())
	{
	  std::cout << " - " + potions[i].getName()
		    << " (1d" << potions[i].getPotency() << ")";
	  
	}
      else
	{
	  std::cout << " ";
	}

      // attacks
      std::cout << std::setw(16) << std::left;
      if (i < attacks.size())
	{
	  std::cout << " - " + attacks[i].getName() << " (1d" << attacks[i].getDamage() << ")" << std::endl;
	}
      else
	{
	  std::cout << std::endl;
	}
    }
}
int Creature::playerAction(Creature &defender)
{
  int select_action = 0;
  while (select_action <= 0 || select_action > 4)
    {
      
      std::cout << "--------------------------------------------------" << std::endl
		<< "You are fighting a " << defender.get_name() << "." << std::endl
		<< "What would you like to do?" << std::endl
		<< "--------------------------------------------------" << std::endl
		<< "1) Attack" << std::endl 
		<< "2) Ability // under construction" << std::endl 
		<< "3) Item" << std::endl 
		<< "4) Run // under construction" << std::endl
		<< "--------------------------------------------------" << std::endl
		<< ">";
      std::cin >> select_action;
    }
   return select_action;
}
int Creature::playerAttack(int selected_action)
{
  int select_attack = 0;
  
      if (selected_action == 1)
	{
	  while (select_attack <= 0 || select_attack > attacks.size())
	    {
	      std::cout << "--------------------------------------------------" << std::endl
			<< "Choose attack: " << std::endl;
		for (int i = 0; i < attacks.size(); i++)
		  {
		  std::cout << i + 1 << ") " << attacks[i].getName()
			    << std::endl;
		  }
		std::cout << "------------------------------------------------" << std::endl
			<< ">";
	  std::cin >> select_attack;
	    }
	}
      return select_attack - 1; // converts to zero-based index
}

int Creature::playerAbility(int selected_action)
{
  int select_ability = 0;

  if (selected_action == 2)
    {
      
      // If there are no abilities, inform the player and return 0
      if (abilities.empty())
	{
	  std::cout << "No abilities available!" << std::endl;
	  return -1;  // Return an invalid index
	}
      while (select_ability <= 0 || select_ability > abilities.size())
	{
	  std::cout << "--------------------------------------------------" << std::endl
		    << "Choose ability: " << std::endl;
	  for (int i = 0; i < abilities.size(); i++)
	    {
	      std::cout << i + 1 << ") " << abilities[i].getName() << std::endl;
	    }
	  std::cout << "--------------------------------------------------" << std::endl
		    << ">";
	  std::cin >> select_ability;
	}
      return select_ability - 1;
    }
  return -1;
}
int Creature::playerItem(int selected_action)
{
  int select_item = 0;
 
  if (selected_action == 3)
    {

      // If there are no potions, inform the player and return 0
      if (potions.empty())
	{
	  std::cout << "No potions available!" << std::endl;
	  return -1;  // Return an invalid index
	}
      // Allow the player to select a potion from their inventory
      while (select_item <= 0 || select_item > potions.size())
	{
	  std::cout << "--------------------------------------------------" << std::endl
		    << "Choose item: " << std::endl;

	  for (int i = 0; i < potions.size(); i++)
	    {
	      std::cout << i + 1 << ") " << potions[i].getName() << std::endl;
	    }

	  std::cout << "--------------------------------------------------" << std::endl
		    << ">";
	  std::cin >> select_item;
	}

      return select_item - 1; // Convert to zero-based index
    }

  return -1;  // If the action is not using an item
}
void Creature::playerRun(int selected_action)
{
  if(selected_action == 4)
    {
      std::cout << "--------------------------------------------------" << std::endl
		<< "You cannot run. Not now, not ever." << std::endl;
    }
}
Creature* Creature::playerTarget(Creature &defender)
{
  int select_target = 0;
  while (select_target <= 0 || select_target > 2)
    {
      std::cout << "--------------------------------------------------" << std::endl
		<< "Choose target: " << std::endl
		<< "1) " << get_name() << std::endl
		<< "2) " << defender.get_name() << std::endl
		<< "--------------------------------------------------" << std::endl
		<< ">";
 
      std::cin >> select_target;
    }
  if(select_target == 1)
    {
      return this;
    }
  
  return &defender;
}

// AI take turn
int Creature::AIaction()
{
  int select_action = 0;

  // AIcontrolType = 1 means it will always attack
  if (AIcontrolType == 1) {
    select_action = 1; // Always attack (1 = Attack)
  }
  // AIcontrolType > 1 can be used for more advanced actions like abilities, items, etc.
  else if (AIcontrolType > 1) {
    // Future expansion: Add logic for abilities, items, or more complex strategies
    select_action = rand() % 4 + 1; // Randomly choose between 1 and 4 (1=Attack, 2=Ability, 3=Item, 4=Run)
  }

  return select_action;
}
int Creature::AIattack(int selected_action)
{
      int select_attack = 0;
      if (selected_action == 1) { // If the action is attack
	if (!attacks.empty()) {
	  select_attack = 0; // Automatically choose the first attack (AI only has one for now)
	}
      }

      return select_attack;
}
Creature* Creature::AItarget(Creature &defender)
{
      // hardcoded to target 1
      int select_target = 1;
      // 1) target 1/ defender, 2) target 2
      // select target = (rand() % 4) + 1
      
      return &defender;

}
int Creature::rolld20()
{
  int roll = (rand() % 20) + 1;
  return  roll;
}
//resolutions
void Creature::attackResolution(Creature *defender, int selected_attack_index)
{
  if(selected_attack_index >= 0 && selected_attack_index < attacks.size())
    {
      if(rolld20() >= defender->getAC()) // check if attack hits
	{
	  int damage = attacks[selected_attack_index].rollDamage(); // roll damage
	  defender->take_damage(damage);
	  std::cout << "--------------------------------------------------" << std::endl
		    << get_name() << " hits " << defender->get_name() << " with the "
		    << attacks[selected_attack_index].getName() << std::endl;
	}
      else
	{
	  std::cout << "--------------------------------------------------" << std::endl
		    << get_name() << " misses " << defender->get_name() << " with the "
		    << attacks[selected_attack_index].getName() << std::endl;
	}
    }
}
void Creature::abilityResolution(Creature *defender, int selected_ability)
{
  // for the future remember to implement stamina cost for utility items
  if (selected_ability >= 0 && selected_ability < abilities.size())
    {
      if (current_mana < abilities[selected_ability].getManaCost())
	{
	  std::cout << "--------------------------------------------------"
		    << std::endl << "Not enough mana!" << std::endl;
	}
      if (current_mana >= abilities[selected_ability].getManaCost())
	{
	  if (abilities[selected_ability].getType() == "healing")
	    {
	      defender->heal(abilities[selected_ability].rollAbility());
	    }
	  // pay mana cost
	  current_mana -= abilities[selected_ability].getManaCost();
	}
    }
}
void Creature::itemResolution(Creature *drinker, int selected_item)
{
  if (selected_item >= 0 && selected_item < potions.size())  // Make sure the item index is valid
    {
      // Get the selected potion's name before any changes
      std::string potion_name = potions[selected_item].getName();
      
      // Use the selected potion (heal the drinker)
      int healAmount = potions[selected_item].rollDrink();
      drinker->heal(healAmount);
      // outputs action and name
      std::cout << "--------------------------------------------------" << std::endl
		<< drinker->get_name() << " drinks the "
		<< potion_name << std::endl;

      // Reduce potion quantity or remove it from inventory
      if (potions[selected_item].getQuantity() > 1)
	{
	  potions[selected_item].setQuantity(potions[selected_item].getQuantity() - 1);  // Decrease quantity
	}
      else
	{
	  potions.erase(potions.begin() + selected_item);  // Remove potion if quantity is 0
	}
    }
  else
    {
      std::cout << "Invalid item selection!" << std::endl;
    }
}


