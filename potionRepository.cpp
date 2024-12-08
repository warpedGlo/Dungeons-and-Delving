#include "PotionRepository.h"
#include "Potion.h"

const Potion gameLib::lesserHealing = Potion
  (
   "Potion of Lesser Healing", // name
   "red", // color
   "round flask", // shape
   4, // potency
   1, // quantity
   0 // bonus
   );

const Potion gameLib::healing = Potion
  (
   "Potion of Healing", // name
   "red", // color
   "round flask", // shape
   6, // potency
   1, // quantity
   2 // bonus
   );
