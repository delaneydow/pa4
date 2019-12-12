// include guards 

#ifndef POKEMONCENTER_H
#define POKEMONCENTER_H

#include <stdio.h>

#include "building.h"


enum PokemonCenterStates 
{
	/* allows state in PokemonCenter to only fluctuate between 
		two state, determined by whether or not stamina 
		points are available. Essentially sets state equal 
		to true or false */ 
	STAMINA_POINTS_AVAILABLE = 0,
	NO_STAMINA_POINTS_AVAILABLE = 1
};

/* removed after examining PA3 solution 
class Model; */ 

class PokemonCenter: public Building 
{
	//define characteristics of the function 
private: 
	unsigned int stamina_capacity; 
		// max number of stamina points pokemon center can hold 

	unsigned int num_stamina_points_remaining; 
		// amount of stamina currently in pokemon center 
		// initial value should be set to stamina_capacity 

	double dollar_cost_per_stamina_point; 
		// per stamina point cost in Pokemon Dollars


public: 

// constructors 
	PokemonCenter(); // default constructor
	PokemonCenter(int in_id, double stamina_cost, unsigned int stamina_capacity, Point2D in_loc); 
	PokemonCenter(int in_id, Point2D in_loc); 
	~PokemonCenter(); // destructor

// member functions

	bool HasStaminaPoints(); 
	unsigned int GetNumStaminaPointsRemaining(); 
	bool CanAffordStaminaPoints(unsigned int stamina_points, double budget); 
	double GetDollarCost(unsigned int stamina_points); 
	unsigned int DistributeStamina(unsigned int points_needed); 
	bool Update(); 
	void ShowStatus(); 


};


#endif 