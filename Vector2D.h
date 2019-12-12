// include guards 

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream> 
#include <stdio.h> 
// create class Vector2D

class Vector2D
{
public: 
	// variables
		double x; 
		double y; 

	// constructors
	Vector2D(); // default constructor

	Vector2D(double in_x, double in_y); //non-default constructor

	//friend class Pokemon; // pokemon can access things from Vector2D

}; 

//non-member operators 

	Vector2D& operator*(Vector2D & v1, double d);

	Vector2D& operator/(Vector2D& v1, double d);

	std::ostream& operator<<(std::ostream& out, Vector2D& vector);




#endif

