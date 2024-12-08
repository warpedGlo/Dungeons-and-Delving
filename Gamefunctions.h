#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <iostream>
#include "Creature.h"
#include "Attack.h"
#include "Potion.h"

// prototypes
bool gameLoop();
void combat(Creature &creature1, Creature &creature2, int dungeon_level);
void merchant(Creature &player, int &dungeon_level);

#endif
