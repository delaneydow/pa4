// include guards
#include <iostream>
#include <cmath>
#include <math.h>


#include "Point2D.h"
#include "Vector2D.h"

using namespace std; 


Point2D::Point2D () // default constructor 
	{
		// sets default values 
			// initialize both x and y to zero
			x = 0.0; 
			y = 0.0; 
	}

Point2D::Point2D (double in_x, double in_y) 
	{ 
		// not default constructor
			// sets x and y to in_x and in_y
			x = in_x; 
			y = in_y; 
	}


// non-member functions
		double GetDistanceBetween(Point2D p1, Point2D p2) 
		{
			// returns cartesian distance between p1 and p2 
				//p1 and p2 both contain x and y values 
			double distance = sqrt(((p1.x - p2.x)*(p1.x-p2.x)) + ((p1.y - p2.y)*(p1.y*p2.y))) ;
			return distance; 
		}
		// added from PA3 solutin 
		bool operator == (Point2D p1, Point2D p2) 
		{
			if (p1.x == p2.x && p1.y == p2.y) 
			{
				return true; 
			} 
			return false; 
		}

		// non-member overloaded operators, not in the class 
		// creates functions for each overloaded operator that has been declared
			// stream output operator 
	
		ostream& operator<<(ostream& out, const Point2D& point) 
		{
			// returns points in x, y format 
				// write object to stream
			out << "(" << point.x << "," << point.y << ")" << endl; 
			return out; // return stream
		}

			// overloaded addition operator
		Point2D operator+(const Point2D& p1, const Vector2D& v1) 
		{
			// adds vector and point together 
			// returns Point2D object 
			Point2D sum; // define type for output 
			sum = Point2D(); // define direction for output 
			sum.x = p1.x + v1.x; 
			sum.y = p1.y + v1.y; 
			return sum;  
		}
			

			// subtraction operator 
		Vector2D operator-(Point2D& p1, Point2D& p2 ) 
		{
			Vector2D res = Vector2D(); 
			res.x = p1.x - p2.x; 
			res.y = p1.y - p2.y; 
			return res; 
		}

	