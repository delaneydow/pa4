// include guards 

#ifndef VIEW_H
#define VIEW_H 

#include <iostream>
#include <stdio.h>

#include "Point2D.h"
#include "GameObject.h"
#include "Pokemon.h" 

using namespace std; 

const int view_maxsize = 20; 

class View
{
private: 
	int size; 
	double scale; 
	Point2D origin; 
	char grid[view_maxsize][view_maxsize][2];
	bool GetSubscripts(int &out_x, int &out_y, Point2D location);

public: 
	View(); // default constructor

	~View(); // destructor 

	void Clear(); 
	void Plot(GameObject* ptr); 
	void Draw(); 

	// removed after examining PA3 solution 
	/*
	friend void GameObject::DrawSelf(char* grid); // share info with DrawSelf in GameObject, made pure virtual. 
	friend class Model; 
	*/ 

}; 


#endif