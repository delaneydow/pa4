// include guards 
#include <iostream>
#include <math.h> 

#include "GameObject.h"
#include "building.h" 
#include "PokemonGym.h"

using namespace std; 


// constructors 
	// default constructor 
PokemonGym::PokemonGym() : Building('G', 0, Point2D(0.0, 0.0))
{
	state = (char) NOT_BEATEN; 
	max_number_of_training_units = 10; 
	num_training_units_remaining = max_number_of_training_units; 
	stamina_cost_per_training_unit = 1; 
	dollar_cost_per_training_unit = 1.0; 
	experience_points_per_training_unit = 2; 
	cout << "PokemonGym default constructed." << endl; 
}

PokemonGym::PokemonGym(unsigned int max_training_units, unsigned int stamina_cost, double dollar_cost, unsigned int exp_points_per_unit, int in_id, Point2D in_loc): Building('G', in_id, in_loc)
{
	state = (char) NOT_BEATEN;  
	max_number_of_training_units = max_training_units; 
	num_training_units_remaining = max_training_units;  
	stamina_cost_per_training_unit = stamina_cost; 
	dollar_cost_per_training_unit = dollar_cost; 
	experience_points_per_training_unit = exp_points_per_unit;
	
	cout << "PokemonGym constructed." << endl;
} 

PokemonGym::~PokemonGym()
{
	cout << "PokemonGym deconstructed." << endl; 
}

// public member functions 
 
double PokemonGym::GetDollarCost (unsigned int unit_qty) 
{
	// returns cost of purchasing training units
	double cost = unit_qty * dollar_cost_per_training_unit; 
	return cost; 
}

unsigned int PokemonGym::GetStaminaCost(unsigned int unit_qty) 
{
	// returns amount of stamina required
	unsigned int stamina = unit_qty * stamina_cost_per_training_unit; 
	return stamina; 
}

unsigned int PokemonGym::GetNumTrainingUnitsRemaining() 
{
	return num_training_units_remaining;
}

//from PA3 solution, check variable names 
unsigned int PokemonGym:: GetMaxAllowableTrainingUnits(double budget, unsigned int stamina) 
{
	unsigned int cost_by_stamina = stamina / stamina_cost_per_training_unit;
    unsigned int cost_by_budget = (int)(budget / dollar_cost_per_training_unit);
    unsigned int allowable_units = min(cost_by_budget, cost_by_stamina);
    return allowable_units;
}

// from PA3 solution , need to check
bool PokemonGym:: HasEnoughTrainingUnits(unsigned int stamina) 
{
	return num_training_units_remaining >= stamina; 
}

bool PokemonGym::IsAbletoTrain(unsigned int unit_qty, double budget, unsigned int stamina) 
{
	return GetMaxAllowableTrainingUnits(budget, stamina) >= stamina; 
	// returns result of above expression
}

// from PA3 solution, check variable names 
unsigned int PokemonGym::TrainPokemon(unsigned int stamina) 
{
	unsigned int exp_points = 0; 
	if (num_training_units_remaining >= stamina) 
	{
		exp_points = stamina * experience_points_per_training_unit; 
		num_training_units_remaining -= stamina; 
		return exp_points; 
	} 
	else {
		exp_points = num_training_units_remaining * experience_points_per_training_unit; 
		num_training_units_remaining = 0; 
		return exp_points; 
	}
}

bool PokemonGym::Update() 
{
	if (state == (char) NOT_BEATEN && num_training_units_remaining == 0)
	{
		state = (char) BEATEN; 
		display_code = 'g'; 
		cout << display_code << GetId() << " has been beaten" << endl; 
		return true; 
	} else if (num_training_units_remaining > 0) 
	{
		if (state == (char) NOT_BEATEN)
		{
			display_code = 'G'; 
			return false;
		} else {
			return false; 
		}
	}
	return false; 
}


bool PokemonGym::IsBeaten() 
{
	if (num_training_units_remaining == 0) 
	{
		return true; 
	} else {
		return false; 
	} 
}


void PokemonGym::ShowStatus() 
{
	cout << "Pokemon Gym Status: " << endl; 
	Building::ShowStatus();  
	cout << "Max number of training units: " << max_number_of_training_units << endl; 
	cout << "Stamina cost per training unit: " << stamina_cost_per_training_unit << endl; 
	cout << "Pokemon dollar per training unit: " << dollar_cost_per_training_unit << endl; 
	cout << "Expereince points per training unit: " << experience_points_per_training_unit << endl; 
	cout << num_training_units_remaining << " training unit(s) are remaining for this gym" << endl; 
}


