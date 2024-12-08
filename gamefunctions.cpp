#include "Gamefunctions.h"
#include <fstream>
#include "CreatureRepository.h"

bool gameLoop()
{
  int dungeon_level = 0;

  Creature paladin = gameLib::paladin;
  
  std::ifstream loadData("player_data.txt");
  std::string strData;
  std::string absorbEqual;
  int intData;
  while (loadData >> strData)
    {
      if (strData == "current_health")
	{
	  loadData >> absorbEqual;
	  loadData >> intData;
	  paladin.set_current_health(intData);
	}
      if (strData == "dungeon_level")
	{
	  loadData >> absorbEqual;
	  loadData >> intData;
	 dungeon_level = intData;
	}
    }
  loadData.close();
      
  while (true)
    {
      if (paladin.get_current_health() <= 0)
	{
	  std::cout << "--------------------------------------------------" << std::endl;
	  std::cout << "You have died! Restarting..." << std::endl;

	  // Reset health and dungeon level
	  paladin.set_current_health(10); // Default health
	  dungeon_level = 0;

	  // Save the reset state
	  std::ofstream saveData("player_data.txt");
	  saveData << "current_health = " << paladin.get_current_health() << std::endl;
	  saveData << "dungeon_level = " << dungeon_level << std::endl;
	  saveData.close();

	  continue; // Restart the game loop
	}

      
      Creature goblin = gameLib::goblin;
      if (dungeon_level == 0)
	{
	  std::cout << "--------------------------------------------------"
		    << std::endl
		    << "You enter the Dungeon and descend the stairs."
		    << std::endl;
	}
      std::cout << "--------------------------------------------------"
		<< std::endl
		<< "You descend the stairs. You have reached level "
		<< dungeon_level << " of the dungeon." << std::endl;
      if (dungeon_level % 5 == 0 && dungeon_level != 0)
	{
	  std::cout << "--------------------------------------------------"
		    << std::endl
		    << "You enter a room lit by a campfire, a merchant sitting in front of it greets you" << std::endl;
	  // code for trading and saving goes here
	  merchant(paladin, dungeon_level);
	}
      if (dungeon_level % 5 != 0 && dungeon_level != 0)
	{
	  // rand() % 4;
	  int monsterCount = rand() % 2;
	  
	  if (monsterCount == 0)
	    {
	      std::cout << "--------------------------------------------------"
			<< std::endl
			<< "You enter a room, no monsters." << std::endl;
	    }
	  if (monsterCount > 0)
	    {
	      std::cout << "--------------------------------------------------"
			<< std::endl
			<< "You enter a room, and there is " << monsterCount
			<< " monsters!" << std::endl;
	      combat(paladin, goblin, dungeon_level);
	    }
	}
      dungeon_level++;
    }
  return true;
}

  

void combat(Creature &creature1, Creature &creature2, int dungeon_level)
{
  bool creature1_goesfirst;
  bool creature2_goesfirst;

  std::cout << "Battle start!" << std::endl;

  // roll for initiative!


  if (creature1.get_speed() == creature2.get_speed())
    {
      int coinflip = (rand() % 2);
      creature1_goesfirst = coinflip;
      creature2_goesfirst = !creature1_goesfirst;
    }
  else
    {
      creature1_goesfirst = creature1.get_speed() > creature2.get_speed();
      creature2_goesfirst = !creature1_goesfirst;
    }

  // combat loop
  if (creature2_goesfirst)
    {
      creature2.take_turn(creature1);
    }
  while(creature1.get_current_health() > 0 && creature2.get_current_health() > 0)
    {
      creature1.take_turn(creature2);
      creature2.take_turn(creature1);

    }
  // combat ends
  if (creature1.get_current_health() <= 0)
    {
      std::cout << "--------------------------------------------------" << std::endl
		<< creature1.get_name() << " was slain!" << std::endl;
    }
  if (creature2.get_current_health() <= 0)
    {
      std::cout << "--------------------------------------------------" << std::endl
		<< creature2.get_name() << " was slain!" << std::endl;
    }


}

void merchant(Creature &player, int &dungeon_level)
{
  int choice = 0;
  
std::cout << "--------------------------------------------------" << std::endl
	  << "Greetings adventurer! Let's do business." << std::endl;
 while (choice != 2)
   {
     std::cout << "--------------------------------------------------" << std::endl
	       << "1) Save" << std::endl 
	       << "2) venture forth" << std::endl
	       << "--------------------------------------------------" << std::endl
	       << ">";

     std::cin >> choice;
     if (choice == 1)
       {
	 std::ofstream savedata("player_data.txt");
	 savedata << "current_health" << " = " << player.get_current_health() << std::endl
		  << "dungeon_level" << " = " << dungeon_level << std::endl; 
	 savedata.close();
     
	 std::cout << "--------------------------------------------------" << std::endl
		   << "Game saved." << std::endl;
       }
   }
 std::cout << "--------------------------------------------------" << std::endl
	   << "Farewell." << std::endl;
}
