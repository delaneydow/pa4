// include guards 

#ifndef POKEMON_H
#define POKEMON_H 

#include <iostream> 
#include <stdio.h> 
#include <string> 

#include "GameObject.h"
#include "Point2D.h" 
#include "Vector2D.h"
#include "building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h" 
#include "Rival.h" 
#include "BattleArena.h"

enum PokemonStates 
{
	STOPPED = 0,
	MOVING = 1,
	EXHAUSTED = 2,
	IN_GYM = 3,
	IN_CENTER = 4,
	MOVING_TO_GYM = 5,
	MOVING_TO_CENTER = 6,
	TRAINING_IN_GYM = 7,
	RECOVERING_STAMINA = 8,

	//PA4:
	IN_ARENA = 9, 
	MOVING_TO_ARENA = 10, 
	BATTLE = 11, 
	FAINTED = 12
};


class Pokemon : public GameObject
{
protected: 
	bool UpdateLocation(); 
	void SetupDestination(Point2D dest); 

protected: 
	double pokemon_dollars; 
	unsigned int experience_points; 
	bool is_in_gym; 
	bool is_in_center; 
	unsigned int stamina; 
	unsigned int training_units_to_buy; 
	unsigned int stamina_points_to_buy; 
	PokemonCenter* current_center; 
	PokemonGym* current_gym; 
	string name; 

	//PA4:
	double health; 
	double store_health; 
	double physical_damage; 
	double magical_damage; 
	double defense; 
	Rival* target; 
	bool is_in_arena; 
	BattleArena* current_arena; 

	protected: 
	bool CheckLocation(); 
	void SetUpDestination(Point2D dest); 

private: 
	double speed;  
	Point2D destination; // initialized to (0.0, 0.0) by Point2D default constructor
	Vector2D delta; 

	// public members
public: 
	Pokemon(); 
	Pokemon(char in_code); 
	Pokemon(int in_id, Point2D in_loc); 

	~Pokemon(); 

	Pokemon(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc); 
	
	//PA4: 
	Pokemon(string in_name, double speed, double hp, double phys_dmg, double magic_dmg, double def, int in_id, char in_code, Point2D in_loc); 
		// derives from game object 
public: 
	void StartMoving(Point2D dest); 
	void StartMovingToCenter(PokemonCenter* center); 
	void StartMovingToGym(PokemonGym* gym); 
	void StartTraining(unsigned int num_training_units); 
	void StartRecoveringStamina(unsigned int num_stamina_points); 
	void Stop(); 
	void ShowStatus(); 
	bool Update(); // will have new additions from PA4 
	string GetName(); 
	bool IsExhausted(); 
	bool ShouldBeVisible(); 

	// getters
	double GetSpeed(); 
	bool GetGym(); 
	bool GetCenter(); 
	unsigned int GetStamina(); 
	unsigned int GetExperiencePoints(); 
	double GetPokemonDollars(); 
	unsigned int GetTrainingUnitsToBuy(); 
	
public: 
	//PA4: , determine if these should be public or private
	bool IsAlive(); 
	void TakeHit(double physical_damage, double magical_damage, double defense); 
	//void ReadyBattle(Rival* in_target); 
	bool StartBattle(); 
	void Pokemon::ReadyBattle(Rival *in_target)
	void Pokemon::TakeHit(double physical_damage, double magical_damage, double defense) 



	


}; 

// Non-Members (static) 
double GetRandomAmountOfPokemonDollars(); 

#endif 