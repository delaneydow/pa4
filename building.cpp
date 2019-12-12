// include guards
#include <iostream> 

#include "building.h"


using namespace std; 

//inherits from GameObject 

Building:: Building() : GameObject('B') // display code
{
	// sets everything to initial values
		// all else inherited by GameObject 
	pokemon_count = 0; 
	cout << "Building default constructed" << endl; 
	
}

		// constructor 
Building::Building(char in_code, int in_Id, Point2D in_loc) : GameObject(in_loc, in_Id, 'B')
		{		 
			pokemon_count = 0; 
			cout << "Building constructed" << endl; 
		}

		// destructor 
Building::~Building()
{
	cout << "Building destructed." << endl; 
}

	// public member functions 
void Building::AddOnePokemon()
			// increments pokemon_count by one
		{
			pokemon_count++; 
		}

void Building::RemoveOnePokemon() 
			// decrements pokemon_count by one 
		{
			pokemon_count--; 
		}

void Building:: ShowStatus()  
{
			// prints pokemon count
	cout << display_code << GetId() << "located at " << location << endl; 
		{
			if (pokemon_count == 1) 
			{
				cout << "" << pokemon_count << " pokemon is in this building" << endl; 
			} else 
				cout << "" << pokemon_count << " pokemon are in this building" << endl; 	 
		}
}

bool Building:: ShouldBeVisible() 
{
	// returns true because buildings are always visible 
		return true; 
	
}







 			
