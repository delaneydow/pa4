// include guards 

#include <iostream>
#include "View.h" 
#include "Point2D.h"
#include "GameObject.h"
#include "Vector2D.h"

using namespace std; 

// default constructor
View::View() 
{
	size = 11; 
	scale = 2; 
	origin = Point2D(0,0); 
}

bool View::GetSubscripts(int& out_x, int& out_y, Point2D location) 
{
	// follow formula, set out_x and out_y to values accessed by location and origin 
		// serves as subscripts 
	out_x = (location.x - origin.x)/scale; // dot into location
	out_y = (location.y - origin.y) / scale; // dot into location
	if (out_x > view_maxsize || out_y > view_maxsize) // outside bounds of display
	{
		cout << "An object is outside the display" << endl; 
		return false; 
	} else {
		// return x and y subscripts 
			// already stored in out_x and out_y as true statement
		return true; 
	}
}

void View::Clear()
{
	// sets all cells of the grid to the background pattern shown 
	for (int i = 0; i < view_maxsize; i++)
	{
		for (int j = 0; j < view_maxsize; j++) // j loop to iterate through both dimensions of array 
		{
			grid[i][j][0] = '.'; 
			grid [i][j][1] = ' '; 
		} // exit j loop 
	} // exit i loop 
}

void View::Plot(GameObject* ptr)
{
	int out_x = 0;
	int out_y = 0;
	bool valid; 
	valid = GetSubscripts(out_x, out_y, ptr -> GetLocation()); 
	if (valid && grid[out_x][out_y][0] == '.') 
	{
		ptr -> DrawSelf(grid[out_x][out_y]); 
	} else if (valid) {
		grid[out_x][out_y][0] = '*'; 
		grid[out_x][out_y][1] = ' '; 
	}
}

void View::Draw()
{
	for (int j = size-1; j >= -1; j--) { //outerself 
		for (int i = -1; i <= size-1; i++) { // innerself 
            //grid axis
            if (i == -1 && j%2 == 0) {
                cout << j*2;
                if (j/5 == 0) {
                    cout << " ";
                }
            }
            else if (i == -1 && j%2 != 0) {
                cout << "  ";
            }
            else if (j == -1 && i%2 == 0) {
                cout << i*2;
                if (i/5 == 0) {
                    cout << " ";
                }
                cout << "  ";
            }
            //draw objects
            if (i >= 0 && j >=0) {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }

}

// destructor 
View::~View()
{
	cout << "View destructed." << endl; 
}




