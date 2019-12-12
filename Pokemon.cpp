// include guards 
#include "Pokemon.h" 
#include "PokemonCenter.h"
#include "PokemonGym.h" 
#include "GameObject.h"
 
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>  
#include <string>

using namespace std; 


Pokemon::Pokemon() : GameObject('P') 
{
	stamina = 20; 
	pokemon_dollars = 0.0;
	speed = 1; // speed changes, everything else default 
	is_in_gym = false; 
	is_in_center = false; 
	experience_points = 0; 
	training_units_to_buy = 0; 
	stamina_points_to_buy = 0; 
	current_center = NULL; 
	current_gym = NULL; 
	this->name = "Pokemon"; 
	this ->speed = 5.0; //adjusted speed
	cout << "Pokemon default constructed" << endl; 

}

Pokemon::Pokemon(char in_code) : GameObject(in_code)  
{
	speed = 5; 
	is_in_gym = false; 
	is_in_center = false; 
	stamina = 20; 
	experience_points = 0; 
	pokemon_dollars = 0.0; 
	training_units_to_buy = 0; 
	stamina_points_to_buy = 0; 
	current_center = NULL; 
	current_gym = NULL; 
	this ->name = name; 
	this ->speed = speed; 
	
	cout << "Pokemon constructed." << endl;
	 
}

Pokemon::Pokemon(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc) : 
	GameObject(in_loc, in_id, in_code)
{
	stamina = 20; 
	pokemon_dollars = 0.0; 
	current_center = NULL; 
	current_gym = NULL; 
	stamina_points_to_buy = 0; 
	training_units_to_buy = 0; 
	this ->speed = speed; 
	this ->name = name; 
	is_in_gym = false; 
	is_in_center = false; 
	experience_points = 0; 
	health = 20; 
	store_health = health; 
	physical_damage = 5; 
	magical_damage = 4; 
	defense = 15; 
	cout << "Pokemon constructed." << endl; 
}

// destructor 
Pokemon:: ~Pokemon()
{
	cout << "Pokemon destructed." << endl; 
}

void Pokemon::SetUpDestination(Point2D dest)
{
	destination = dest; 
	Vector2D vec = destination - location; 
	delta = vec* (speed/GetDistanceBetween(destination, location));  
}


void Pokemon:: StartMoving(Point2D dest) 
{
	if (state == (char) EXHAUSTED) {
		cout << display_code << GetId() <<": I am exhauted. I may move but you cannot see me." << endl; 
	} else if (dest == this ->GetLocation())
	{
		cout << display_code << GetId() << ": I'm already there. See?" << endl; 
	} else {
		state = (char) MOVING; 
		SetUpDestination(dest); 
		cout << display_code << GetId() << ": On my way" << endl; 
	}
}

void Pokemon:: StartMovingToCenter(PokemonCenter* center) 
{
    if (!IsExhausted()) {
        if (location == center->GetLocation()) {
            cout << display_code << GetId() << ": I am already at the Pokemon Center!" << endl;
        } else {
            if (is_in_center) {
                current_center->RemoveOnePokemon(); // handles corner case
                is_in_center = false;
            } else if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
            state = MOVING_TO_CENTER;
            current_center = center;
            SetupDestination(center->GetLocation());
            cout << display_code << GetId() << ": On my way to center " << center->GetId() << endl;
        }
    } else
        cout << display_code << GetId() << ": I am exhausted so I can't move to recover stamina..." << endl;
}

void Pokemon:: StartMovingToGym(PokemonGym* gym) 
{
  if (!IsExhausted()) {
        if (location == gym->GetLocation()) {
            cout << display_code << GetId() << ": I am already at the Pokemon Gym!" << endl;
        } else {
            if (is_in_gym) {
                current_gym->RemoveOnePokemon(); // handles corner case
                is_in_gym = false;
            } else if (is_in_center) {
                current_center->RemoveOnePokemon();
                is_in_center = false;
            }
            state = MOVING_TO_GYM;
            current_gym = gym;
            SetupDestination(gym->GetLocation());
            cout << display_code << GetId() << ": On my way to gym " << gym->GetId() << endl;
        }
    } else
        cout << display_code << GetId() << ": I am exhausted so I shouldn't be going to the gym.." << endl;
}


void Pokemon::StartTraining(unsigned int num_training_units) 
{
	unsigned int training_units_in_gym = 0;
    if (!IsExhausted()) {
        if (state == IN_GYM || state == TRAINING_IN_GYM) {
            if (current_gym->IsAbletoTrain(num_training_units,
                                           pokemon_dollars, stamina)) {
                if (!current_gym->IsBeaten()) {
                    training_units_in_gym = current_gym->GetNumTrainingUnitsRemaining();
                    training_units_to_buy = min(num_training_units, training_units_in_gym);
                    state = TRAINING_IN_GYM;
                    cout << display_code << GetId() << ": Started " << training_units_to_buy
                         << " training unit(s) at Pokemon Gym " << current_gym->GetId() << endl;
                } else
                    cout << display_code << GetId() << ": Cannot train! This Pokemon Gym is already beaten!"
                         << current_gym->GetId() << endl;
            } else
                cout << display_code << GetId() << ": Not enough stamina and/or money for training" << endl;
        } else
            cout << display_code << GetId() << ": I can only train in a Pokemon Gym!" << endl;
    } else
        cout << display_code << GetId() << ": I am exhausted so no more training for me.." << endl;
}

void Pokemon::StartRecoveringStamina(unsigned int num_stamina_points) 
{
  unsigned int stamina_count_in_center = 0;
    if (state == IN_CENTER || state == RECOVERING_STAMINA) {
        if (IsExhausted())
            cout << display_code << GetId() << ": I barely made it to the Pokemon center!" << endl;
        if (current_center->CanAffordStaminaPoints(num_stamina_points, pokemon_dollars)) {
            if (current_center->HasStaminaPoints()) {
                stamina_count_in_center = current_center->GetNumStaminaPointsRemaining();
                state = RECOVERING_STAMINA;
                stamina_points_to_buy = min(num_stamina_points, stamina_count_in_center);
                cout << display_code << GetId() << ": Started recovering " << stamina_points_to_buy
                     << " stamina point(s) at Pokemon Center " << current_center->GetId() << endl;
            } else
                cout << display_code << GetId()
                    << ": Cannot recover! No stamina points available in this Pokemon Center "
                     << current_center->GetId() << endl;
        } else
            cout << display_code << GetId() << ": Not enough money to recover stamina." << endl;
    } else
        cout << display_code << GetId() << ": I can only recover stamina at a Pokemon Center!" << endl;
}

void Pokemon:: Stop() 
{
	state = (char) STOPPED; 
	cout << display_code << GetId() << ": Stopping.." << endl; 

}

bool Pokemon::IsExhausted() 
{
	return stamina == 0; 
}

bool Pokemon:: ShouldBeVisible() 
{
	return !IsExhausted(); 
}

void Pokemon:: ShowStatus() 
{
	cout << name << " status: " << endl; 
	GameObject::ShowStatus(); 
	// prints statements depending on specific states 
	switch (state)
	{
		case (char) STOPPED: 
		{
			cout << "stopped" << endl; 
			break; 
		}
		case (char) MOVING: 
		{
			cout << " moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << endl; 
			break; 
		}
		case (char) IN_GYM: 
		{
			cout << " inside Pokemon Gym " << current_gym->GetId() << endl; 
			break; 
		}
		case (char) IN_CENTER: 
		{
			cout << " inside Pokemon Center " << current_center ->GetId() << endl;
			break; 
		}
		case (char) MOVING_TO_GYM: 
		{
			cout << " heading to Pokemon Gym " << current_gym->GetId()
                 << " at a speed of " << speed << " at each step of " << delta << endl;
			break; 
		}
		case (char) MOVING_TO_CENTER: 
		{
			cout <<" heading to Pokemon Center " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta; 
			break; 
		}
		case (char) TRAINING_IN_GYM: 
		{
			cout << " training in Pokemon Gym " << current_gym->GetId() << endl; 
			break; 
		}
		case (char) RECOVERING_STAMINA: 
		{ 
			//cout << " recovering stamina in Pokemon Center " << current_center- >GetId() << endl; 
			break; 
		}
		default: 
			break; 
	}
	// print stats 
	cout << "\tStamina: " << stamina << endl;
    cout << "\tPokemon Dollars: " << pokemon_dollars << endl;
    cout << "\tExperience Points: " << experience_points << endl;
}

bool Pokemon:: CheckLocation()
// checks if Pokemon is within one step of destination
{
	if ((fabs(destination.x - GetLocation().x) <= fabs(delta.x)) && (fabs(destination.y - GetLocation().y) <= fabs(delta.y)))
	{
		location = destination; 
		cout << display_code << GetId() << " : I'm there!" << endl; 
		return true; 
	} else {
		location = location + delta; 

		// output if Pokemon is moving 
		if (delta.x != 0)
		{
			cout << display_code << GetId() << ": On my way." << endl; 
		}
	}

}

bool Pokemon:: Update()
 // update location is object is moving
// returns true if simulation should be stopped 
{
	// variables before switch added from PA3 solution
	bool arrived = false; 
	unsigned int stamina_received = 0; 
	unsigned int stamina_cost = 0; 
	double dollar_cost = 0; 
	unsigned int num_training_units = 0; 
	unsigned int experience_gain = 0; 

	switch (state) 
	{
		case (char) STOPPED: 
		{
			return false; 
			break; 
		}
		
		case (char) MOVING: 
		{
			if (is_in_center) 
			{
				current_center->RemoveOnePokemon(); 
				is_in_center = false; 
			} else if (is_in_gym) {
				current_gym ->RemoveOnePokemon(); 
				is_in_gym = false;
			}
			if (stamina == 0) 
			{
				cout << name << " is out of stamina and can't move." << endl; 
				state = (char) EXHAUSTED; 
				return true; 
			} else {
				arrived = UpdateLocation(); 
				if (arrived) 
				{
					state = (char) STOPPED; 
					return true; 
				} else {
					pokemon_dollars += GetRandomAmountOfPokemonDollars(); 
					stamina -= 1; 
					return false; 
				}
				break; 
			}

		case (char) MOVING_TO_CENTER: 
		{
			if (is_in_center) 
			{
				current_center ->RemoveOnePokemon(); 
				is_in_center = false;
			} else if (is_in_gym) 
			{
				current_gym ->RemoveOnePokemon(); 
				is_in_gym = false; 
			}
			if (stamina == 0) 
			{
				cout << name << " is out of stamina and can't move." << endl;
				state = (char) EXHAUSTED;
                return true;
            } else {
                arrived = UpdateLocation();
                if (arrived) {
                    state = IN_CENTER;
                    is_in_center = true;
                    current_center->AddOnePokemon();
                    return true;
                } else {
                    pokemon_dollars += GetRandomAmountOfPokemonDollars();
                    stamina -= 1;
                    return false;
                }
            }
            break; 
		}
			 
		case (char) IN_GYM: // nothing required 

		case (char) IN_CENTER: // nothing required 

		case (char) EXHAUSTED: // nothing required 

		case (char) MOVING_TO_GYM:
		{
			if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            } else if (is_in_gym) {
                current_gym->RemoveOnePokemon();
                is_in_gym = false;
            }
            if (stamina == 0) {
                cout << name << " is out of stamina and can't move." << endl;
                state = EXHAUSTED;
                return true;
            } else {
                arrived = UpdateLocation();
                if (arrived) {
                    state = IN_GYM;
                    is_in_gym = true;
                    current_gym->AddOnePokemon();
                    return true;
                } else {
                    pokemon_dollars += GetRandomAmountOfPokemonDollars();
                    stamina -= 1;
                    return false;
                }
            }
        }

        case (char) BATTLE: 
        {
        	// decrease stamina
        	// decrease pokemon dollars
        	Pokemon::StartBattle(); 
        	if (health > 0) // criteria for winning battle
        	{
        		health = 20; // default value 
        		state = (char) IN_ARENA; 
        		target->IsAlive(); //update target state 
        	} else 
        	{
        		state = (char) FAINTED; 
        		target->IsAlive(); // update target state
        	}
        }



        case MOVING_TO_ARENA:
        {
        	if (is_in_arena) {
                current_arena->RemoveOnePokemon();
                is_in_arena = false;
            } else if (is_in_arena) {
                current_arena->RemoveOnePokemon();
                is_in_arena = false;
            }
            if (stamina == 0) {
                cout << name << " is out of stamina and can't move." << endl;
                state = EXHAUSTED;
                return true;
            } else {
                arrived = UpdateLocation();
                if (arrived) {
                    state = IN_ARENA;
                    is_in_arena = true;
                    current_arena->AddOnePokemon();
                    return true;
                } else {
                    pokemon_dollars += GetRandomAmountOfPokemonDollars();
                    stamina -= 1;
                    return false;
                }
            }
        }


		case (char) TRAINING_IN_GYM:   
		{
			stamina_cost = current_gym->GetStaminaCost(training_units_to_buy);
            dollar_cost = current_gym->GetDollarCost(training_units_to_buy);
            experience_gain = current_gym->TrainPokemon(training_units_to_buy);
            stamina -= stamina_cost;
            pokemon_dollars -= dollar_cost;
            experience_points += experience_gain;
            cout << "** " << name << " completed " << training_units_to_buy << " training unit(s)! **" << endl;
            cout << "** " << name << " gained " << experience_gain << " experience points! **" << endl;
            training_units_to_buy = 0;
            state = (char) IN_GYM; 
			return true; 
			break; 
		}
		

		case (char) RECOVERING_STAMINA: 
		{
			dollar_cost = current_center->GetDollarCost(stamina_points_to_buy);
			stamina = stamina + current_center ->DistributeStamina(stamina_points_to_buy); 
			pokemon_dollars -= dollar_cost;  
			// reduce pokemon dollars by total cost of stamina points
			cout << " ** " << name << "recovered " << stamina_points_to_buy << "stamina point(s)!" << endl; 
			stamina_points_to_buy = 0; //reset 
			this -> state = (char) IN_CENTER; 
			return true; 
			break; 
		}

		case (char) FAINTED: 
		{
			this -> state = (char) FAINTED; 
			return true; 
		}

		default: 
		{
			return false; 
		}	
	}
}
// non-member function 
/*double GetRandomAmountofPokemonDollars()
{
	double f_min = 0.0; 
	double f_max = 2.0; 
	double f = (double)rand()/ RAND_MAX;
	return f_min + f*(f_max - f_min); 
}
*/

// getters
/*string Pokemon::GetName()
{
	return name; 
} */

/*bool Pokemon::IsAlive()
{
	if state != (char) FAINTED 
	{
		return true; 
	} else 
	{
		return false; 
	}
	*/

void Pokemon::ReadyBattle(Rival *in_target)
{
	if (state == (char) IN_ARENA) 
	{
		if (current_arena ->IsAbleToFight())
		{
			(if !(current_arena -> IsBeaten()))
			{
				(if in_target ->IsAlive())
				{
					target = in_target; 
					state = (char) BATTLE; 
				} // exit if 
			} // exit if
		}// exit if
	} else {
		state = (char) IN_ARENA; 
	}
}

/*
bool Pokemon::StartBattle() 
	if (state == (char) BATTLE) {

	}
	*/
void Pokemon::TakeHit(double physical_damage, double magical_damage, double defense) 
{
	// select attack type 

	damage = (100.0 - defense)/100 * physical_damage;
	health  -= damage; 
}


}



