//include guards 

#ifndef POINT2D_H
#define POINT2D_H

#include <iostream> 
#include <stdio.h>

#include "Vector2D.h" 

// create class 

class Point2D // all data and members are public 
{
	public: // declaring public variables
		double x; 
		double y; 

		// constructors and default constructor 

		Point2D(); // default constructor 

		Point2D (double in_x, double in_y); // non-default constructor

		//friend class Pokemon; // ability for Pokemon class to access elements, not vice versa 
}; 

// non-member functions

double GetDistanceBetween(Point2D p1, Point2D p2); 

bool operator == (Point2D, Point2D); 

//non-member overloaded operators included here: 

std::ostream& operator<<(std::ostream& out, const Point2D& p1); 

Point2D operator+(const Point2D& p1, const Vector2D& v1); // output is of type Point2D

Vector2D operator-(const Point2D& p1, const Point2D& p2); // output is of type Vector2D


#endif 