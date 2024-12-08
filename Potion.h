#ifndef POTION_H
#define POTION_H

#include <string>

class Potion
{
public:
  Potion(); // default constructor
  Potion(std::string newName,std::string newColor, std::string newShape, int newPotency, int newQuantity, int newBonus); // overloaded constructor
  
  // getter
  std::string getName();
  int getPotency();
  int getQuantity();
  int getBonus();
  int rollDrink();

  // setter
  void setQuantity(int newQuantity);
private:
  std::string name; // healing, mana, poison
  std::string color; // red, blue, green
  std::string shape; // round flask, conical phial, cylindrical vial, rectangular bottle 
  int potency; // max amount of possible healing
  int quantity; // self explanatory i think
  int bonus; // guaranteed potency
};

#endif
