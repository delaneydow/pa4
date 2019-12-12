// include guards 
#ifndef POKEMONGYM_H
#define POKEMONGYM_H

#include <iostream>
#include <stdio.h>

#include "building.h"
#include "GameObject.h" 


enum PokemonGymStates 
{
	NOT_BEATEN = 0,
	BEATEN = 1 
};

// pokemon gym objects inherit from building 

class PokemonGym : public Building 
{ 

private: 
	unsigned int num_training_units_remaining; 
	unsigned int max_number_of_training_units; 
	unsigned int stamina_cost_per_training_unit; 
	unsigned int dollar_cost_per_training_unit; 
	unsigned int experience_points_per_training_unit; 

public: 
	PokemonGym(); 
	PokemonGym(int in_id, Point2D in_loc); 
	PokemonGym(unsigned int max_training_units, unsigned int stamina_cost, 
		double dollar_cost, unsigned int exp_points_per_unit, int in_id, Point2D in_loc); 

	~PokemonGym(); 

	double GetDollarCost(unsigned int unit_qty); 
	unsigned int GetStaminaCost(unsigned int unit_qty);
	unsigned int GetNumTrainingUnitsRemaining(); 
	unsigned int GetMaxAllowableTrainingUnits(double budget, unsigned int stamina); 
	bool HasEnoughTrainingUnits(unsigned int training_units); 
	bool IsAbletoTrain(unsigned int unit_qty, double budget, unsigned int stamina); 
	unsigned int TrainPokemon(unsigned int training_units) ; 
	bool Update(); 
	bool IsBeaten(); 
	void ShowStatus(); 

};

#endif
