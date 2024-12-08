#include "CreatureRepository.h"
#include "PotionRepository.h"
#include "AbilityRepository.h"

const Creature gameLib::paladin = Creature
  (
   "Paladin", // name
   0, // control type: 0 = player and 1 = AI
   10, // new health
   4, // new mana
   0, // new stamina
   10, // new armor clas
   30, // new speed
   {Attack(), gameLib::longsword},
   {gameLib::lesserHealingWord},
   {Potion(), Potion("Potion of Healing","red", "round flask", 6, 3, 2)}
   );

const Creature gameLib::goblin = Creature
  (
   "Goblin", // name
   1, // control type: 0 = player and 1 = AI
   7, // new health
   2, // new mana
   0, // new stamina
   10, // new armor clas
   30, // new speed
   {Attack()},
   {},
   {}
);
