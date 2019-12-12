// include guards 

#ifndef RIVAL_H
#define RIVAL_H 

#include <iostream> 
#include <stdio.h>

#include "GameObject.h"
#include "Point2D.h"

using namespace std; 

enum RivalStates
{
	ALIVE_RIVAL = 1, 
	FAINTED_RIVAL = 2
}; 

class Rival: public GameObject
{
protected: 
	double health; 
	double physical_damage; 
	double magical_damage; 
	double defense; 
	double stamina_cost_per_fight; 
	bool is_in_arena; 
	//BattleArena* current_arena; 

public: 
	Rival(string name, double speed, double hp, double phys_dmg, double magic_dmg, double def, int it, Point2D in_loc); // derived from GameObject
	void TakeHit(int physical_damage, int magical_damage, int defense); 

	// getters
	double get_phys_dmg(); 
	double get_magic_dmg(); 
	double get_defense(); 
	double get_health(); 
	bool Update(); 
	void ShowStatus(); 
	bool IsAlive(); 


}; 

#endif