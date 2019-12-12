// include guards 

#ifndef MODEL
#define MODEL

#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <list>
#include <time.h>

using namespace std; 

#include "GameObject.h" 
#include "Pokemon.h" 
#include "building.h" 
#include "View.h" 
#include "PokemonGym.h" 
#include "PokemonCenter.h" 
#include "Rival.h"
#include "BattleArena.h"
#include "Input_Handling.h"

// implement class
class Model 
{
public: 
	int time; // simulation time 

	int num_objects; 
	
	int num_pokemon; 
	
	int num_centers; 
	
	int num_gyms; 
		
private: 
		// generate lists instead of array 
	list <GameObject*> object_ptrs; 
	list <GameObject*> active_ptrs; // generating active_ptrs list
	list <Pokemon*> pokemon_ptrs; 
	list <PokemonCenter*> center_ptrs; 
	list <PokemonGym*> gym_ptrs; 
	list <Rival*> rival_ptrs; 
	

public: 
	Model(); //default constructor
	Model(const Model &other); // copy constructor, cannot be used 
	~Model(); //destructor 
	Pokemon* GetPokemonPtr(int id_num); 
	PokemonCenter* GetPokemonCenterPtr(int id_num); 
	PokemonGym* GetPokemonGymPtr(int id_num ); 
	Rival* GetRivalPtr(int id_num); 
	bool Update(); 
	void Display(View& view) ; 
	void ShowStatus(); 

	void NewCommand(); // PA4 addition
	
};



#endif
