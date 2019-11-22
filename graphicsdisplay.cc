#include "graphicsdisplay.h"
#include "window.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

GraphicsDisplay::GraphicsDisplay(){**********************

	//an 18 by 11 grid of black squares, then a column of white squares, then another grid

}

void GraphicsDisplay::update_shape(string name, Coord one, Coord two, Coord three, Coord four) {*************
	//this new shape must be displayed on the board
	

}

void GraphicsDisplay::update_line(vector<Cell*> cells) {******************
	//loop through the cells on that row and set them back to black
	
	int x = 0;
	int y = 0;

	for(int i=0;i<11;i++){
		x = cells[i]->coordinates.x;
		y = cells[i]->coordinates.y;
		this-xw.fillRectangle(
}



