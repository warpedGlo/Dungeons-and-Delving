#include "Potion.h"

Potion::Potion()
{
  name = "Mundane Water";
  color = "clear blue";
  shape = "round flask";
  potency = 4;
  quantity = 1;
  bonus = 0;
}
Potion::Potion(std::string newName,std::string newColor, std::string newShape, int newPotency, int newQuantity, int newBonus)
{
  name = newName;
  color = newColor;
  shape = newShape;
  potency = newPotency;
  quantity = newQuantity;
  bonus = newBonus;
}

// getter
std::string Potion::getName()
{
  return name;
}
int Potion::rollDrink()
{
  if(potency != 0)
    {
      return ((rand() % potency) + 1) + bonus;
    }
  return 0;
}
int Potion::getPotency()
{
  return potency;
} 
int Potion::getQuantity()
{
  return quantity;
}


// setter
void Potion::setQuantity(int newQuantity)
{
  quantity = newQuantity;
}
