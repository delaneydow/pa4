// include guards

#include <iostream> 
#include "GameCommand.h" 

using namespace std; 

// function implementations 
int center_id; 
int pokemon_id; 


void DoMoveCommand(Model& model, int pokemon_id, Point2D p1) 
{
	if (model.GetPokemonPtr(pokemon_id))  
	{
		Pokemon* pokePtr = model.GetPokemonPtr(pokemon_id); 
		cout << "Moving " << pokemon_id << " to " << p1 << endl; 
		pokePtr -> StartMoving(p1); 
	} else {
		cout << "Error: Please enter a valid command!" << endl; 
	} // exit if statement 
}

void DoMoveToCenterCommand(Model& model, int pokemon_id, int center_id) 
{
	if (model.GetPokemonPtr(pokemon_id) && model.GetPokemonCenterPtr(center_id)) 
	{
		Pokemon* pokePtr = model.GetPokemonPtr(pokemon_id); 
		PokemonCenter* centerPtr = model.GetPokemonCenterPtr(center_id); 
		cout << "Moving " << pokemon_id << " to center " << center_id << endl; 
		pokePtr ->  StartMovingToCenter(centerPtr); 
	} else {
		cout << "Error: Please print a valid command!" << endl; 
	} // exit if statement 

}

void DoMoveToGymCommand(Model& model, int pokemon_id, int gym_id) 
{
	if (model.GetPokemonPtr(pokemon_id) /*&& model.GetGymId(gym_id)*/) 
	{
		Pokemon* pokePtr = model.GetPokemonPtr(pokemon_id);
		//PokemonGym* gymPtr = &gym_id; 
		cout << "Moving " << pokemon_id << " to gym " << gym_id << endl; 
		//pokePtr -> StartMovingToGym(gymPtr); 
	} else {
		cout << "Error: Please print a valid command!" << endl; 
	}
}

void DoStopCommand(Model& model, int pokemon_id)
{
	if (model.GetPokemonPtr(pokemon_id))
	{
		Pokemon* pokePtr = model.GetPokemonPtr(pokemon_id);
		//cout << "Stopping " << pokemon_id << in_id << id_num << endl; 
		pokePtr -> Stop(); 
	} else {
		cout << "Error: Please enter a valid command!" << endl; 
	}
}

void DoTrainInGymCommand(Model& model, int pokemon_id, unsigned int training_units) 
{
	if (model.GetPokemonPtr(pokemon_id) /*&& model.GetNumTrainingUnitsRemaining(training_units)*/)
	{
		Pokemon* pokePtr = model.GetPokemonPtr(pokemon_id);
		//PokemonGym* trainingPtr = model.GetNumTrainingUnitsRemaining(training_units); 
		cout << "Training " << pokemon_id << endl; 
		//pokePtr -> TrainPokemon(); 
	} else {
		cout << "Error: Please enter a valid command!" << endl; 
	}
}

void DoRecoverInCenterCommand(Model& model, int pokemon_id, unsigned int stamina_points)
{
	if (model.GetPokemonPtr(pokemon_id) /*&& model.GetNumStaminaPointsRemaining(stamina_points)*/) 
	{
		Pokemon* pokePtr = model.GetPokemonPtr(pokemon_id);
		//PokemonCenter* staminaPtr = model.GetNumStaminaPointsRemaining(stamina_points); 
		cout << "Recover " << pokemon_id << "'s stamina" << endl; 
		//pokePtr -> RecoverInCenter(); 
	} else {
		cout << "Error: Please enter a valid command!" << endl; 
	}
}

void DoGoCommand(Model& model, View& view) 
{ 
	cout << "Advancing one tick." << endl;
}

void DoRunCommand(Model& model, View& view)
{
	cout << "Advancing one tick." << endl; 
}






