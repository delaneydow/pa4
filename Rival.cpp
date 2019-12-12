//include guards

#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "Rival.h"
#include "GameObject.h"

using namespace std; 

// derived from GameObject

Rival::Rival(string name, double speed, double hp, double phys_dmg, double magic_dmg, double def, int in_id, Point2D in_loc) : GameObject(in_loc, in_id, 'R')
{
	health = 20; 
	physical_damage = 5; 
	magical_damage = 4; 
}

void Rival::TakeHit(int physical_damage, int magical_damage, int defense)
{
	// select attack type 

	double damage = (100.0 - defense)/100 * physical_damage; 
	health -= damage; // subtract damage from health

}

// getters

double Rival::get_phys_dmg()
{
	return physical_damage; 
}

double Rival::get_magic_dmg()
{
	return magical_damage; 
}

double Rival::get_defense() 
{
	return defense; 
}

double Rival::get_health()
{
	return health; 
}

bool Rival::Update()
{
	if (state == (char) ALIVE_RIVAL) 
	{
		return false;
	} 
	if (get_health() <= 0) 
	{
	state = char (FAINTED_RIVAL); 
	return true; 
	}	

}
 bool Rival::IsAlive() 
 {
 	if (get_health() >= 0) 
	{
		return true;
	} else {
		return false; 
	}
 }

void Rival::ShowStatus()
{
	cout << "Rival Status: " << endl; 
	GameObject::ShowStatus(); 
	// outputs specific state information 
	// prints statements depending on specific states 
	switch (state)
	{
		case (char) ALIVE_RIVAL: 
		{
			cout << "rival is alive." << endl; 
			break; 
		}
		case (char) FAINTED_RIVAL: 
		{
			cout << "Rival has fainted"  << endl; 
			break; 
		}
		default: 
			break; 
}
} 

