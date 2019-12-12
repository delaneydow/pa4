//include guards 

#ifndef BUILDING_H
#define BUILDING_H


// define class building 

	// inherits from GameObject, base class for all buildings 
#include "GameObject.cpp" 

class Building : public GameObject
{ 
private: 
		unsigned int pokemon_count;

public:  
	// constructors 
	Building(); // default constructor 

	Building(char command, int id_num, Point2D in_loc);

	~Building(); // destructor 

	// public member functions 
	void AddOnePokemon();

	void RemoveOnePokemon(); 

	void ShowStatus();

	bool ShouldBeVisible(); 


}; 

#endif