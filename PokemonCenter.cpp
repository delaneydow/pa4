//include guards 
#include <iostream> 
#include <math.h>

#include "PokemonCenter.h"

using namespace std; 
// inherits from building, which inherits from GameObject 

// constructors
PokemonCenter::PokemonCenter() : Building('C', 0, Point2D(0.0, 0.0)) 
{
	this ->state = STAMINA_POINTS_AVAILABLE; 
	this ->stamina_capacity = 100; 
	this ->num_stamina_points_remaining = stamina_capacity; 
	this->dollar_cost_per_stamina_point = 5; 
	cout << "PokemonCenter default constructed" << endl; 	
}


PokemonCenter::PokemonCenter(int in_id, double stamina_cost, unsigned int stamina_capacity, Point2D in_loc): Building('C', in_id, in_loc)
	{ 
		this->stamina_capacity = stamina_capacity;  
		this->num_stamina_points_remaining = stamina_capacity; 
		this->dollar_cost_per_stamina_point = stamina_cost; 
			// state is STAMINA_POINTS_AVAILABLE 
		this ->state = STAMINA_POINTS_AVAILABLE; // "default" value 
		cout << "PokemonCenter constructed" << endl; 		
	}

bool PokemonCenter::Update() {
	if ((num_stamina_points_remaining == 0) && (state == (char) STAMINA_POINTS_AVAILABLE)){
		state = (char) NO_STAMINA_POINTS_AVAILABLE; 
		display_code = 'c'; 
		cout << "PokemonCenter " << GetId() << " has run out of stamina points." << endl; 			return true; // returns true if stamina is depleted
	} else {
		return false; 
	}
}

PokemonCenter::~PokemonCenter()
{
	cout << "PokemonCenter destructed." << endl; 
}

// public member functions 

unsigned int PokemonCenter::DistributeStamina(unsigned int points_needed) {
	unsigned int stamina_points = 0; 
	// series of if statements 
	if (num_stamina_points_remaining >= points_needed) {
			// subtract points_needed from PokemonCenter amount
		stamina_points = points_needed; 
		num_stamina_points_remaining -= points_needed;  
	} else {
		stamina_points = num_stamina_points_remaining; 
		num_stamina_points_remaining = 0; 
	}
	return stamina_points; 
}

void PokemonCenter::ShowStatus() 
	{
		cout << "Pokemon Center Status: " << endl; 
		Building::ShowStatus(); 
		cout << "Pokemon dollars per stamina point: " << dollar_cost_per_stamina_point <<  endl; 
		cout << " has " << num_stamina_points_remaining << "stamina point(s) remaining. " << endl; 
	}

bool PokemonCenter::CanAffordStaminaPoints(unsigned int stamina_points, double budget)
 {
		// returns true if pokemon can afford to purchase stamina points from budget 
		/* adapted from PA3 solution */
		return budget >= GetDollarCost(stamina_points); 
 } 

bool PokemonCenter::HasStaminaPoints() 
{
	// true if PokemonCenter has at least one stamina point 
	if (num_stamina_points_remaining >= 1)
		return true; 
	else 
		return false; 
}

 // getters
 
unsigned int PokemonCenter::GetNumStaminaPointsRemaining() 
{
	// get number of stamina points remaining 
	return num_stamina_points_remaining > 0; 
}

double PokemonCenter::GetDollarCost(unsigned stamina_points) 
{
	return stamina_points * dollar_cost_per_stamina_point; 
}
	




