// include guards 

#include <iostream> 
#include <cstdlib>
#include <string> 
#include <iterator>

#include "Model.h" 
#include "GameObject.h"
#include "Pokemon.h"
#include "PokemonCenter.h"
#include "PokemonGym.h" 
#include "View.h" 
#include "Input_Handling.h" // file exclusive to PA4

using namespace std; 

// constructors 

	//default constructor 
Model::Model()
{
	time = 0; 

	// create pointers to Point2D vectors
	// create array of certain types to assign into array 

// create points 
		Point2D point1 = Point2D(5,1); 
		Point2D point2 = Point2D(10,1); 
		Point2D point3 = Point2D(1,20); 
		Point2D point4 = Point2D(10,20);
		Point2D point5 = Point2D(0,0);
		Point2D point6 = Point2D(5,5);
		Point2D point7 = Point2D(7,5); 

		Pokemon* ptrP1 = new Pokemon("Pikachu", 1, 'P', 2.0, point1); 
		Pokemon* ptrP2 = new Pokemon("Bulbasaur", 2, 'P', 1.0, point2);

		PokemonCenter* ptrC1 = new PokemonCenter(1, 1, 100, point3);
		PokemonCenter* ptrC2 = new PokemonCenter(2, 2, 200, point4); 

		PokemonGym* ptrG1 = new PokemonGym(10, 1.0, 2.0, 3, 1, point5);
		PokemonGym* ptrG2 = new PokemonGym(2, point6);

		//Rival* ptrR1 = new Rival(1, point7);
		//Rival* ptrR2 = new Rival(2, point7);

	// create linked list
		//front to back
	object_ptrs.push_back(ptrP1); 
	object_ptrs.push_back(ptrP2); 
	object_ptrs.push_back(ptrC1); 
	object_ptrs.push_back(ptrC2); 
	object_ptrs.push_back(ptrG1); 
	object_ptrs.push_back(ptrG2); 
	//object_ptrs.push_back(ptrR1); 
	//object_ptrs.push_back(ptrR2); 

		// activating active_ptrs list 
	active_ptrs.push_back(ptrP1); 
	active_ptrs.push_back(ptrP2); 
	active_ptrs.push_back(ptrC1); 
	active_ptrs.push_back(ptrC2); 
	active_ptrs.push_back(ptrG1); 
	active_ptrs.push_back(ptrG2); 
	//active_ptrs.push_back(ptrR1); 
	//active_ptrs.push_back(ptrR2); 

		// original order 
	pokemon_ptrs.push_back(ptrP1); 
	pokemon_ptrs.push_back(ptrP2); 

	center_ptrs.push_back(ptrC1); 
	center_ptrs.push_back(ptrC2); 

	gym_ptrs.push_back(ptrG1); 
	gym_ptrs.push_back(ptrG2); 

	//rival_ptrs.push_back(ptrR1); 
	//rival_ptrs.push_back(ptrR2); 



	cout << "Model default constructed" << endl; 
}

	// destructor
		// must also create destructors for GameObject, Pokemon, PokemonCenter, and PokemonGym
// modified to be conducive to linked list environment
Model::~Model()
{
	for (list <GameObject*>::iterator it = object_ptrs.begin(); it != object_ptrs.end(); ++it) // loop through array to delete pointers
	{
		delete *it; // frees memory from heap to destruct pointer array 
	}
	cout << "Model destructed" << endl; 
}

// member functions 

Pokemon* Model::GetPokemonPtr(int id_num)
{
	for (list <Pokemon*>:: iterator it = pokemon_ptrs.begin(); it != pokemon_ptrs.end(); ++it)
	{
		if ((*it) -> GetId() == id_num)
		{
			return *it; 
		}
	}
	return 0; 
}

PokemonCenter* Model::GetPokemonCenterPtr(int id_num) 
{
	for (list <PokemonCenter*>:: iterator it = center_ptrs.begin(); it != center_ptrs.end(); ++it) 
	{
		if ((*it) -> GetId() == id_num)
		{
			return *it; 
		}
	}
	return 0; 
}

PokemonGym* Model::GetPokemonGymPtr(int id_num) 
{
	for (list <PokemonGym*>:: iterator it = gym_ptrs.begin(); it != gym_ptrs.end(); ++it) 
	{
		if ((*it) -> GetId() == id_num) 
		{
			return *it; 
		}
	}
	return 0; 
}

//PA4 addition
Rival* Model:: GetRivalPtr(int id_num)
{
	for (list <Rival*>:: iterator it = rival_ptrs.begin(); it != rival_ptrs.end(); ++it) 
	{
		if ((*it) -> GetId() == id_num) 
		{
			return *it; 
		}
	}
	return 0;
}

bool Model::Update()
/* provides service to main program: 
	increments time, iterates through object_ptrs array, 
	calls Update() for each object. Must update if game is over, 
	or if game has been won based on specific conditions */ 
// redone via PA3 solution  

{
	time++; 
	int gyms_beaten = 0; 
	int pokemon_exhausted = 0;

// num pokemon gyms beaten
	if (gyms_beaten != num_gyms) 
	{
		for (int i = 0; i < num_gyms; i++) 
		{
			if (gym_ptrs.front() -> GetState() == (char) BEATEN)
			{
				for (list <PokemonGym*>:: iterator it = gym_ptrs.begin(); it != gym_ptrs.end(); ++it)
				{
					gyms_beaten++; 
				}
				
			} // exit nested if 
		} // exit for loop 
	} // exit if statement 

// num pokemon that are tired
	if (pokemon_exhausted != num_pokemon) 
	{
		if (pokemon_ptrs.front() -> IsExhausted()) 
			{
				for (list <PokemonGym*>:: iterator it = gym_ptrs.begin(); it != gym_ptrs.end(); ++it){
					pokemon_exhausted++; 
				}
				
			} // exit nested if
	} // exit if statement 

	bool event = false; 

	// continue to update all 
	if (gyms_beaten == num_gyms) 
	{
        cout << "GAME OVER: You win! All Pokemon Gyms beaten!" << endl;
        exit(EXIT_SUCCESS);
    }
    if (pokemon_exhausted == num_pokemon) 
    {
        cout << "GAME OVER: You lose! All of your Pokemon are exhausted!" << endl;
        exit(EXIT_SUCCESS);
    }
    // update if winning condition is not met
    for (int i = 0; i < num_objects; i++) 
    {
        bool temp = object_ptrs.front()->Update();
        if (temp) 
        {
            event = temp;
        }
    }
    return event;
} // exit update function 




void Model::Display(View& view)
{
	cout << "Time: " << time << endl; 
	view.Clear(); // calls clear function to clear view
		// adapted for loop for linked list
	for (list <GameObject*>:: iterator it = active_ptrs.begin(); it != active_ptrs.end(); ++it) 
	{
		view.Plot((*it)); // calls plot function
			// generates view display for all of the GameObjects
	} // exits for loop
	view.Draw(); // access DrawSelf function from view 

} // exit display function 

void Model::ShowStatus()
{
	cout << "Time: " << time << endl;
	for (list <GameObject*>:: iterator it = object_ptrs.begin(); it != object_ptrs.end(); ++it)
	{
		(*it) ->ShowStatus(); 
	} 
} // exit show status function 
/*
void Model:: NewCommand()
{
	char type; 
	int id; 
	int x, y; 

	cin >> type >> id >> x >> y; 
	if (cin.fail())
	{
		throw Invalid_Input("Enter TYPE (character), ID (integer), x and y coordinates (integer)"); // format from sample output 
		// error propogation	
	}

	Point2D pt = Point2D(x,y); // create appropriate parameters as location 

	switch (type)
	{
		case 'g': // pokemon gym
		{
			for (list <PokemonGym*>:: iterator it = gym_ptrs.begin(); it != gym_ptrs.end(); ++it)
			{
				if ((*it) -> GetId() == id)
				{
					throw Invalid_Input("ID number already exists."); 
				}
			}
			PokemonGym* ptrG = new PokemonGym(pt, id); 
			gym_ptrs.push_back(ptrG1); 
			object_ptrs.push_back(ptrG1); 
			active_ptrs.push_back(ptrG1); 
			break; 
		}

		case 'c': // pokemon center
		{
			for (list <PokemonCenter*>:: iterator it = center_ptrs.begin(); it != center_ptrs.end(); ++ it)
			{
				if ((*it) -> GetId() == id)
				{
					throw Invalid_Input("ID number already exists."); 
				}
			}
			PokemonCenter* ptrC = new Pokemon(id, pt); 
			center_ptrs.push_back(ptrC1); 
			object_ptrs.push_back(ptrC1); 
			active_ptrs.push_back(ptrC1); 
			break;
		}

		case 'p': // pokemon
		{
			for (list <Pokemon*>:: iterator it = pokemon_ptrs.begin(); it != pokemon_ptrs.end(); ++ it)
			{
				if ((*it) -> GetId() == id)
				{
					throw Invalid_Input("ID number already exists."); 
				}
			}
			Pokemon* ptrP = new Pokemon(id, pt); 
			center_ptrs.push_back(ptrP1); 
			object_ptrs.push_back(ptrP1); 
			active_ptrs.push_back(ptrP1); 
			break;
		}

		case 'r': // rival 
		{
			for (list <Rival*>:: iterator it = rival_ptrs.begin(); it != rival_ptrs.end(); ++ it)
			{
				if ((*it) -> GetId() == id)
				{
					throw Invalid_Input("ID number already exists."); 
				}
			}
			Rival* ptrR = new Pokemon(id, pt); 
			rival_ptrs.push_back(ptrR1); 
			object_ptrs.push_back(ptrR1); 
			active_ptrs.push_back(ptrR1); 
			break;

		}
	}
}
*/ 
Model:: Model(const Model &other)
{
	// empty copy constructor 
}
