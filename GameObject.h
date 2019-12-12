// include guards 

#ifndef GAMEOBJECT_H 
#define GAMEOBJECT_H 

#include <iostream> 
#include <stdio.h>

#include "Point2D.h" 


// this class is the base class for all objects in the game
// define GameObject 
class GameObject 
{
	protected: 
		Point2D location;  // location of Point2D object 
		int id_num; // this object's ID 	
		char display_code; // how the object is presented in the View		 
		char state; // state of the object
		

	public: 
		GameObject(); 
		GameObject(char in_code);
			/* initializes display_code to in_code, id_num to 1, 
			state to 0. outputs message */ 
		GameObject(Point2D in_loc, int in_id, char in_code);
			/* initializes display_code, id_num, and location. output message */ 
		virtual ~GameObject(); 
		Point2D GetLocation();
			// returns location for this object 
		int GetId(); 
			// returns ID for this object 
		virtual void ShowStatus(); 
			// outputs information contained in this class 
		void DrawSelf(char* drawPtr); 
			// called from Model to be pure virtual 
		char GetState(); 
			// returns state for this object 
		virtual bool Update() = 0; 
			// use update when called, initially false 
		virtual bool ShouldBeVisible() = 0; 

		

}; 

#endif