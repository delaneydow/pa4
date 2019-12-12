// include guards

#include <iostream> 
#include <stdio.h> 
#include <stdlib.h> 

#include "BattleArena.h" 
#include "building.h" 

using namespace std; 

int in_id; 
Point2D in_loc; 
char command; 

BattleArena::BattleArena() : Building('A', 0, Point2D(0.0, 0.0)) 
{
	this ->pokemon_count = 0; 
	max_num_rivals = 3; 
	this->num_rivals_remaining = max_num_rivals; 
	this->dollar_cost_per_fight = 4; 
	this->stamina_cost_per_fight = 3; 
	this -> state = (char) RIVALS_AVAILABLE; 
	cout << "BattleArena default constructed" << endl; 
}

/*BattleArena::BattleArena(unsigned int max_rivals, unsigned int stamina_cost, double dollar cost, 
			int in_id, Point2D in_loc): Building(char command, id_num, in_loc) // see instructions for 
			// what to input into building 
{
	command = 'A'; 
	this -> id_num = in_id; 
	this ->location = in_loc; 
	this->state =(char) RIVALS_AVAILABLE; 
	cout << "BattleArena default constructed" << endl; 
}
*/
//public member functions

bool BattleArena::HasEnoughRivals()
{
	if (GetNumRivalsRemaining() >= 1) 
	{
		return true;
	} else {
		return false; 
	}
} 

bool BattleArena::IsAbleToFight(double budget, unsigned int stamina) 
{
	if (budget && stamina) 
	{
		return true; 
	} else {
		return false; 
	}
}

bool BattleArena::Update() 
{
	if (GetNumRivalsRemaining() == 0) 
	{
		display_code = 'a'; 
		cout << "BattleArena " << GetId() << " has no more rivals remaining." << endl; 
		return true; // returns true if stamina is depleted
	} else {
		return false; 
	}
}
 
bool BattleArena::IsBeaten() 
{
	if (GetNumRivalsRemaining() == 0) 
	{
		return true; 
	} else {
		return false; 
	}
}

void BattleArena::ShowStatus() 
{
	Building::ShowStatus(); 
	cout << "Max number of rivals: " << GetNumRivalsRemaining() << endl; 
	cout << "Stamina cost per fight: " << GetStaminaCost() << endl; 
	cout << "Pokemon dollar per fight" << GetDollarCost() << endl; 
	cout << num_rivals_remaining << " rival(s) are remaining for this arena" << endl; 
}

// getters
unsigned int BattleArena::GetNumRivalsRemaining() 
{
	return num_rivals_remaining; 
}

double BattleArena::GetDollarCost() 
{
	return dollar_cost_per_fight; 
}

unsigned int BattleArena::GetStaminaCost()
{
	return stamina_cost_per_fight; 
}

