// include guards
#include <iostream> 
#include "GameObject.h"
#include "Point2D.h" 

using namespace std; 

GameObject::GameObject()  // default constructor 
{
	display_code = ' '; 
	state = 0; 
	id_num = 1; 
	cout << "GameObject constructed.";  
}

GameObject::GameObject(char in_code)
{
	/* initializes display_code to in_code, id_num to 1, 
			state to 0. outputs message */ 
	display_code = in_code; 
	id_num = 1; 
	state = 0; 
	cout << "GameObject constructed" << endl; 
}

GameObject::GameObject(Point2D in_loc, int in_id, char in_code) 
{
	/* initializes display_code, id_num, and location. output message */ 
	display_code = in_code; 
	id_num = in_id; 
	location = in_loc; 
	state = 0; // state remains zero 	
	cout << "GameObject constructed" << endl; 		
}

// destructor 
GameObject::~GameObject()
{
	cout << "GameObject destructed." << endl; 
}

Point2D GameObject::GetLocation() 
{
	// returns location for this object 
	return location; 
}
			
int GameObject::GetId()
{
	// returns ID for this object
	return id_num; 
} 

char GameObject::GetState()
{
	// returns state for this object
	return state; 
} 

void GameObject::ShowStatus()
{
	// outputs information contained in this class 
	cout << display_code << id_num << " at " << location << endl; 

}

void GameObject::DrawSelf(char* drawPtr)
{
	*drawPtr = display_code; 
	*(drawPtr+1) = '0' + id_num; // converts id_num to char, store in ptr 
}

bool GameObject::Update()
{
	return false; 
	// returns false because other functions should be called 
}
			


