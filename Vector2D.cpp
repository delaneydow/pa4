// include guards
#include <iostream> 
#include "Vector2D.h" 

using namespace std; 

	// constructors
		// default constructor 
Vector2D::Vector2D() 
	{ 
		// initialize x and y to zero
			// represent displacement values 
			x = 0.0; 
			y = 0.0; 
		} 

		// construction to set x values to input values 
	Vector2D::Vector2D(double in_x, double in_y) {
			x = in_x; 
			y = in_y; 

		} 

// non-member overaloaded operators, not a part of the class
			// multiplication operator
	Vector2D& operator*(Vector2D& v1, double d)
	{
			// returns a Vector2D object
			// makes new x and y values  
		Vector2D product; //initialize output
		product = Vector2D(); //assign output to class
		product.x = v1.x * d; 
		product.y = v1.y * d; 
		return product; 
	}

			// division operator 
	Vector2D& operator/(Vector2D& v1, double d)
	{
		if (d == 0) // evaluates to true, non-zero 
		{
				//returns a Vector2D object 
				// makes new x and y values 
			Vector2D quotient; 
			quotient = Vector2D(); 
			quotient.x = v1.x/d; 
			quotient.y = v1.y/d; 
		} else {
			return v1; // returns original vector as default 
		}					
	}

			// stream output operator 
	ostream& operator<<(ostream& out, const Vector2D& vector) 
	{
			//output formatted as <x, y>
		out << "<" << vector.x << ", " << vector.y << ">" << endl; 
		return out; 
	}


		