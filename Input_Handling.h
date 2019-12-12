// INCLUDE GUARDS

#ifndef INPUT_HANDLING
#define INPUT_HANDLING

#include <string>
#include <iostream>
#include <stdio.h>

using namespace std; 

class Invalid_Input // error handling class
{
public: 
	// variable ptr set equal to input into constructor
	Invalid_Input(string in_ptr) : msg_ptr (in_ptr) {}
	const string msg_ptr; 

private: 
	Invalid_Input(); 
	// no default construction
}; 

#endif




